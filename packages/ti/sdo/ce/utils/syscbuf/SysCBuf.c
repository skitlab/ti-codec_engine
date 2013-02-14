/* 
 *  Copyright (c) 2008 Texas Instruments. All rights reserved. 
 *  This program and the accompanying materials are made available under the 
 *  terms of the Eclipse Public License v1.0 and Eclipse Distribution License
 *  v. 1.0 which accompanies this distribution. The Eclipse Public License is
 *  available at http://www.eclipse.org/legal/epl-v10.html and the Eclipse
 *  Distribution License is available at 
 *  http://www.eclipse.org/org/documents/edl-v10.php.
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 * */
/*
 *  ======== SysCBuf.c ========
 */

#include <xdc/runtime/Startup.h>
#include <xdc/runtime/Gate.h>

#include <string.h>

#include "package/internal/SysCBuf.xdc.h"

/*
 *  ======== CBuf_Obj ========
 *  Header that will go at the begining of the buffer to keep track of
 *  buffer.
 */
typedef struct CBuf_Obj {
    UInt32  curw;       /* offset to next character to be written */
    UInt32  size;       /* Size of the buffer for trace output */
    UInt32  avail;      /* number of unread characters */
    Char   *beg;        /* the buffer itself */
    Char   *end;        /* one BEYOND end of buffer */
    UInt32  lost;       /* some data lost due to wraparound */
} CBuf_Obj;


/*
 *  ======== SysCBuf_Module_startup ========
 */
Int SysCBuf_Module_startup(Int phase)
{
    CBuf_Obj   *cbuf;

    if (SysCBuf_bufSize != 0) {
        module->bufSize = SysCBuf_bufSize;
        memset(module->outbuf, 0, SysCBuf_bufSize);

        cbuf = (CBuf_Obj *)module->outbuf;
        cbuf->size = SysCBuf_bufSize - sizeof(CBuf_Obj);
        cbuf->beg = (Char *)cbuf + sizeof(CBuf_Obj);
        cbuf->end = cbuf->beg + cbuf->size;

        cbuf->curw = 0;
        cbuf->avail = 0;
        cbuf->lost = 0;
    }
    else {
        module->bufSize = 0;
        module->outbuf = NULL;
    }

    return (Startup_DONE);
}

/*
 *  ======== SysCBuf_abort ========
 */
Void SysCBuf_abort(String str)
{
    Char ch;    
    
    if (module->bufSize != 0) {
        if (str != NULL) {
            while ((ch = *str++) != '\0') {
                SysCBuf_putch(ch);
            }
        }

        /* Only flush if configured to do so */
        if (SysCBuf_flushAtExit) {
            SysCBuf_flush();
        }
    }
}

/*
 *  ======== SysCBuf_bind ========
 */
Int SysCBuf_bind(Char *buf, UInt32 size)
{
    CBuf_Obj   *cbuf;

    if (size <= sizeof(CBuf_Obj)) {
        return (-1);
    }
    else {
        module->bufSize = size;
        module->outbuf = buf;
        memset(module->outbuf, 0, module->bufSize);

        cbuf = (CBuf_Obj *)module->outbuf;
        cbuf->size = module->bufSize - sizeof(CBuf_Obj);
        cbuf->beg = (Char *)cbuf + sizeof(CBuf_Obj);
        cbuf->end = cbuf->beg + cbuf->size;

        cbuf->curw = 0;
        cbuf->avail = 0;
        cbuf->lost = 0;
    }

    return (0);
}

/*
 *  ======== SysCBuf_exit ========
 */
Void SysCBuf_exit(Int stat)
{
    if ((SysCBuf_flushAtExit) && (module->bufSize != 0)) {
        SysCBuf_flush();
    }
}

/*
 *  ======== SysCBuf_putch ========
 */
Void SysCBuf_putch(Char c)
{
    CBuf_Obj    *cbuf = (CBuf_Obj *)module->outbuf;
    IArg         key;
    
    if (module->bufSize != 0) {

        key = Gate_enterSystem();

        cbuf->beg[cbuf->curw] = c;

        if (cbuf->curw < cbuf->size - 1) {
            cbuf->curw++;
        }
        else {
            cbuf->curw = 0;
        }

        /* cbuf->avail never exceeds the size of the trace buffer */
        if (cbuf->avail < cbuf->size) {
            cbuf->avail++;
        }
        else {
            cbuf->lost++;
        }
        Gate_leaveSystem(key);
    }    
}

/*
 *  ======== SysCBuf_ready ========
 */
Bool SysCBuf_ready()
{
    /* 
     * Return bufsize here so that when called by System
     * this function gets inlined and helps eliminate code;
     * module->bufSize == 0 => SysCBuf_ready() == FALSE => functions
     * called only when SysCBuf_ready() is TRUE can be eliminated(!).
     */
    return (module->bufSize);
}

/*
 *  ======== SysCBuf_flush ========
 *  Called during SysCBuf_exit, System_exit or System_flush.
 */
Void SysCBuf_flush()
{
    CBuf_Obj    *cbuf = (CBuf_Obj *)module->outbuf;
    Char        *buf;
    UInt32       nbytes;
    IArg         key;

    // TODO: Do we want to use the system gate for this?
    key = Gate_enterSystem();
    
    if (module->bufSize != 0) {
        /* Output the buffer starting with the oldest */
        if (cbuf->curw < cbuf->avail) {
            /* Output the part at the end */
            nbytes = cbuf->avail - cbuf->curw;
            buf = cbuf->beg + (cbuf->size - cbuf->avail) + cbuf->curw;
            SysCBuf_output(buf, nbytes);

            cbuf->avail -= nbytes;
        }

        /* cbuf->curw >= cbuf->avail */
        nbytes = cbuf->avail;
        buf = cbuf->beg + cbuf->curw - nbytes;
        SysCBuf_output(buf, nbytes);

        /* Reset everything */
        cbuf->curw = 0;
        cbuf->avail = 0;
        cbuf->lost = 0;
    }
    
    Gate_leaveSystem(key);
}

/*
 *  ======== SysCBuf_get ========
 *  Copy a maximum of 'size' bytes from SysCBuf buffer into buf, starting
 *  with the oldest data.
 */
UInt32 SysCBuf_get(Char *buf, UInt32 size, UInt32 *avail, UInt32 *lost)
{
    CBuf_Obj   *cbuf = (CBuf_Obj *)module->outbuf;
    Char       *start;
    UInt32      nbytes;
    UInt32      total = 0;
    UInt32      max;
    IArg        key;


    // TODO: Do we want to use the system gate for this?
    key = Gate_enterSystem();

    *lost = cbuf->lost;

    /* Maximum number that can be copied */
    max = (size > cbuf->avail) ? cbuf->avail : size;

    /*
     *  If the buffer wraps, output up to the end first.
     */
    while ((cbuf->curw < cbuf->avail) && (total < max)) {
        /* Find the oldest data */
        start = cbuf->beg + cbuf->size - cbuf->avail + cbuf->curw;
        nbytes = cbuf->avail - cbuf->curw;
        nbytes = (nbytes > max) ? max : nbytes;
        memcpy(buf, start, nbytes);
        cbuf->avail -= nbytes;
        total += nbytes;
    }

    while ((cbuf->avail > 0) && (total < max)) {
        start = cbuf->beg + cbuf->curw - cbuf->avail;
        nbytes = (cbuf->avail > max) ? max : cbuf->avail;
        memcpy(buf, start, nbytes);
        cbuf->avail -= nbytes;
        total += nbytes;
    }

    /* Since we've made space in the buffer, reset 'lost' */
    cbuf->lost = 0;

    *avail = cbuf->avail;

    Gate_leaveSystem(key);

    return (max);
}

/*
 *  ======== SysCBuf_getSize ========
 */
UInt32 SysCBuf_getSize()
{
    CBuf_Obj   *cbuf = (CBuf_Obj *)module->outbuf;

    return ((cbuf == NULL) ? 0 : cbuf->size);
}
/*
 *  @(#) ti.sdo.ce.utils.syscbuf; 1, 0, 0,1; 2-24-2012 19:31:42; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */

