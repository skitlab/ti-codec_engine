/* 
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
/*
 *  ======== CESettings.c ========
 */

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_ce_settings_desc


#include <xdc/std.h>

#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Registry.h>

#include <string.h>

#include "CESettings.h"

/* Number of Diags mask bits CE uses: EX1234567 */
#define NUMBITS 9

/* Maximum length of control string */
#define MAXCONTROL (NUMBITS + 2)

/* Maximum string length of module name */
#define MAXMODLEN 128

/* Maximum length of string for setting diags mask. */
#define MAXLEN (MAXMODLEN + MAXCONTROL)

/* For logging */
Registry_Desc ti_sdo_ce_settings_desc;

static Int curInit = 0;


/*
 *  ======== CESettings_exit ========
 */
Void CESettings_exit()
{
    /*
     *  Don't decrement reference count since there is no
     *  Registry_removeModule(). We don't want the reference count to go
     *  to zero, and then call Registry_addModule() again.
     */
}

/*
 *  ======== CESettings_getDiags ========
 */
Void CESettings_getDiags(String curControl, Int size)
{
    Int     i = 0;

    /*
     *  The size of the string to copy must be large enough to hold the
     *  null-terminated string "+EX1234567"
     */
    Assert_isTrue(size >= MAXCONTROL, (Assert_Id)NULL);

    /* Create a string for set bits */
    curControl[i++] = '+';
    if (Diags_query(Diags_ENTRY)) {
        curControl[i++] = 'E';
    }
    if (Diags_query(Diags_EXIT)) {
        curControl[i++] = 'X';
    }
    if (Diags_query(Diags_USER1)) {
        curControl[i++] = '1';
    }
    if (Diags_query(Diags_USER2)) {
        curControl[i++] = '2';
    }
    if (Diags_query(Diags_USER3)) {
        curControl[i++] = '3';
    }
    if (Diags_query(Diags_USER4)) {
        curControl[i++] = '4';
    }
    if (Diags_query(Diags_USER5)) {
        curControl[i++] = '5';
    }
    if (Diags_query(Diags_USER6)) {
        curControl[i++] = '6';
    }
    if (Diags_query(Diags_USER7)) {
        curControl[i++] = '7';
    }

    curControl[i] = '\0';
}

/*
 *  ======== CESettings_init ========
 */
Void CESettings_init()
{
    Registry_Result result;

    if (curInit++ == 0) {
        /*
         *  Enable logging. This code needs to be placed in an init function
         *  so the app has a chance to call Diags_setMask() before any other
         *  function in this module is called. Calling Diags_setMask() before
         *  Registry_addModule() has no effect.
         */
        result = Registry_addModule(&ti_sdo_ce_settings_desc,
                CESETTINGS_MODNAME);

        if (result != Registry_SUCCESS) {
            /* Can't do logging */
            Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);
        }
    }
}

/*
 *  ======== CESettings_setDiags ========
 */
Void CESettings_setDiags(String modName)
{
    Char              diags[MAXLEN];
    Char             *curPtr;

    Assert_isTrue(strlen(modName) <= MAXMODLEN, (Assert_Id)NULL);

    if (strlen(modName) > MAXMODLEN) {
        /* Module name is too long, cannot set the Diags bits */
        return;
    }

    strcpy(diags, modName);
    curPtr = diags + strlen(modName);

    CESettings_getDiags(curPtr, MAXLEN - strlen(modName));

    Diags_setMask(diags);
}
/*
 *  @(#) ti.sdo.ce.global; 1, 0, 0,1; 2-24-2012 19:29:48; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */

