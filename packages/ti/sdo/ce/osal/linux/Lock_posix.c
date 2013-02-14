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
 *  ======== Lock_posix.c ========
 */
/* we define _XOPEN_SOURCE 500 to get declaration of pthread_mutexattr_settype
 * in the MonteVista headers
 */
#define _XOPEN_SOURCE 500

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_ce_osal_Lock_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Registry.h>

#include <pthread.h>

#include <ti/sdo/ce/global/CESettings.h>
#include <ti/sdo/ce/osal/Global.h>
//#include <ti/sdo/ce/osal/Memory.h>

#include <ti/sdo/ce/osal/Lock.h>


/*
 *  ======== Lock_Obj ========
 */
typedef struct Lock_Obj {
    pthread_mutex_t mutex;
} Lock_Obj;

/* REMINDER: if you add an initialized static var, reinitialize it at cleanup */

Registry_Desc ti_sdo_ce_osal_Lock_desc;

static Int regInit = 0;     /* Registry_addModule() called */
static Bool curInit = FALSE;

/*
 *  ======== Lock_system ========
 */
Lock_Handle Lock_system = NULL;

/*
 *  ======== Lock_ATTRS ========
 */
Lock_Attrs Lock_ATTRS = {
    0
};

static Void cleanup(Void);

/*
 *  ======== Lock_acquire ========
 */
Void Lock_acquire(Lock_Handle lock)
{
    pthread_mutex_lock(&lock->mutex);   /* atomic begin */
}

/*
 *  ======== Lock_create ========
 */
Lock_Handle Lock_create(Lock_Attrs *attrs)
{
    Lock_Handle lock;
    pthread_mutexattr_t mattrs;

    if (attrs == NULL) {
        attrs = &Lock_ATTRS;
    }

    if ((lock = (Lock_Obj *)Memory_alloc(NULL, sizeof(Lock_Obj), 0, NULL))
            == NULL) {
        return (NULL);
    }

    pthread_mutexattr_init(&mattrs);
    pthread_mutexattr_settype(&mattrs, PTHREAD_MUTEX_RECURSIVE_NP);
    pthread_mutex_init(&lock->mutex,  &mattrs);

    return (lock);
}

/*
 *  ======== Lock_delete ========
 */
Void Lock_delete(Lock_Handle lock)
{
    if (lock != NULL) {
        Int status;
        status = pthread_mutex_destroy(&lock->mutex);

        /* destroy fails try to unlock before freeing the object */
        if (status != 0) {
            do {
                status = pthread_mutex_unlock(&lock->mutex);
            } while (status == 0);
            pthread_mutex_destroy(&lock->mutex);
        }

        Memory_free(NULL, lock, sizeof (Lock_Obj));
    }
}

/*
 *  ======== Lock_init ========
 */
Void Lock_init(Void)
{
    Registry_Result   result;

    /*
     *  No need to reference count for Registry_addModule(), since there
     *  is no way to remove the module.
     */
    if (regInit == 0) {
        /* Register this module for logging */
        result = Registry_addModule(&ti_sdo_ce_osal_Lock_desc, Lock_MODNAME);
        Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

        if (result == Registry_SUCCESS) {
            /* Set the diags mask to the CE default */
            CESettings_init();
            CESettings_setDiags(Lock_MODNAME);
        }
        regInit = 1;
    }

    if (curInit == FALSE) {
        curInit = TRUE;
        Lock_system = Lock_create(NULL);
    }

    Global_atexit((Fxn)cleanup);
}

/*
 *  ======== Lock_release ========
 */
Void Lock_release(Lock_Handle lock)
{
    pthread_mutex_unlock(&lock->mutex);
}

/*
 *  ======== cleanup ========
 */
static Void cleanup(Void)
{
    if (curInit != TRUE) {
        curInit = FALSE;
        if (Lock_system != NULL) {
            Lock_delete(Lock_system);
        }
    }
}
/*
 *  @(#) ti.sdo.ce.osal.linux; 2, 0, 1,1; 2-24-2012 19:30:21; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */

