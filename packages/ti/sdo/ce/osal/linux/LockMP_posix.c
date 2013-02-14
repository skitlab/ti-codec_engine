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
 *  ======== LockMP_posix.c ========
 */

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_ce_osal_LockMP_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Registry.h>

#include <pthread.h>

#include <sys/types.h>
#include <unistd.h>

#include <ti/sdo/ce/global/CESettings.h>
//#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/osal/Global.h>
#include <ti/sdo/ce/osal/SemMP.h>

#include <ti/sdo/ce/osal/LockMP.h>


/*
 *  ======== LockMP_Obj ========
 */
typedef struct LockMP_Obj {
    SemMP_Handle  sem;    /*  IPC semaphore */
    Int           value;  /*  Number of times Lock has been acquired */
    pthread_t     owner;  /*  ID of owning thread */
    pid_t         pid;    /*  ID of owning process (in case thread id is not
                           *  unique across processes.
                           */
} LockMP_Obj;

/*
 *  REMINDER: If you add an initialized static variable, reinitialize it at
 *  cleanup
 */

Registry_Desc ti_sdo_ce_osal_LockMP_desc;

static Int regInit = 0;     /* Registry_addModule() called */
static Bool curInit = FALSE;

static Void    cleanup(Void);

/*
 *  ======== LockMP_acquire ========
 */
Void LockMP_acquire(LockMP_Handle lock)
{
    pthread_t       self;
    pid_t           pid;
    Int             status = SemMP_EOK;

    Log_print1(Diags_ENTRY, "[+E] Entered LockMP_acquire> lock[0x%x]",
            (IArg)lock);

    self = pthread_self();
    pid = getpid();

    if ((lock->owner != self) || (lock->pid != pid)) {
        /* This thread does not currently own the lock */
        status = SemMP_pend(lock->sem, SemMP_FOREVER);
        Assert_isTrue(status == SemMP_EOK, (Assert_Id)NULL);
    }

    if (status == SemMP_EOK) {
        lock->pid = pid;
        lock->owner = self;
        lock->value++;
    }

    Log_print1(Diags_EXIT, "[+X] Leaving LockMP_acquire> lock[0x%x]",
            (IArg)lock);
}

/*
 *  ======== LockMP_create ========
 */
LockMP_Handle LockMP_create(Int key)
{
    LockMP_Obj *lock;

    Log_print1(Diags_ENTRY,
            "[+E] LockMP_create> key: 0x%x count: %d attrs: 0x%x", (IArg)key);

    lock = (LockMP_Obj *)Memory_alloc(NULL, sizeof(LockMP_Obj), 0, NULL);
    if (lock == NULL) {
        Log_print0(Diags_USER7, "[+7] LockMP_create> Memory_alloc failed");
        return (NULL);
    }

    /* Create IPC semaphore with count 1 */
    lock->sem = SemMP_create(key, 1);
    if (lock->sem == NULL) {
        Log_print0(Diags_USER7, "[+7] LockMP_create> SemMP_create failed");
        LockMP_delete(lock);
        return (NULL);
    }

    lock->value = 0;
    lock->owner = (pthread_t)NULL;
    lock->pid = (pid_t)NULL;

    Log_print1(Diags_EXIT, "[+X] Leaving LockMP_create> lock[0x%x]",
            (IArg)lock);

    return (lock);
}

/*
 *  ======== LockMP_delete ========
 */
Void LockMP_delete(LockMP_Handle lock)
{
    Log_print1(Diags_ENTRY, "[+E] Entered LockMP_delete> lock[0x%x]",
            (IArg)lock);

    if (lock != NULL) {
        if (lock->sem != NULL) {
            SemMP_delete(lock->sem);
        }

        Memory_free(NULL, lock, sizeof(LockMP_Obj));
    }

    Log_print0(Diags_EXIT, "[+X] Leaving LockMP_delete>");
}

/*
 *  ======== LockMP_getCount ========
 */
Int LockMP_getCount(LockMP_Handle lock)
{
    return (lock->value);
}

/*
 *  ======== LockMP_getRefCount ========
 */
Int LockMP_getRefCount(LockMP_Handle lock)
{
    return (SemMP_getRefCount(lock->sem));
}

/*
 *  ======== LockMP_init ========
 */
Void LockMP_init(Void)
{
    Registry_Result   result;

    /*
     *  No need to reference count for Registry_addModule(), since there
     *  is no way to remove the module.
     */
    if (regInit == 0) {
        /* Register this module for logging */
        result = Registry_addModule(&ti_sdo_ce_osal_LockMP_desc,
                LockMP_MODNAME);
        Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

        if (result == Registry_SUCCESS) {
            /* Set the diags mask to the CE default */
            CESettings_init();
            CESettings_setDiags(LockMP_MODNAME);
        }
        regInit = 1;
    }

    if (curInit++ == 0) {
        Global_atexit((Fxn)cleanup);
    }
}

/*
 *  ======== LockMP_release ========
 */
Void LockMP_release(LockMP_Handle lock)
{
    Log_print1(Diags_ENTRY, "[+E] Entered LockMP_release>lock[0x%x]",
            (IArg)lock);

    Assert_isTrue(lock->owner == pthread_self(), (Assert_Id)NULL);
    Assert_isTrue(lock->pid == getpid(), (Assert_Id)NULL);
    Assert_isTrue(lock->value > 0, (Assert_Id)NULL);

    lock->value--;

    if (lock->value == 0) {
        lock->owner = (pthread_t)NULL;
        lock->pid = (pid_t)NULL;
        SemMP_post(lock->sem);
    }

    Log_print1(Diags_EXIT, "[+X] Leaving LockMP_release>lock[0x%x]",
            (IArg)lock);
}

/*
 *  ======== cleanup ========
 */
static Void cleanup(Void)
{
    Assert_isTrue(curInit > 0, (Assert_Id)NULL);

    if (--curInit == 0) {
        /* Nothing to do */
    }
}
/*
 *  @(#) ti.sdo.ce.osal.linux; 2, 0, 1,1; 2-24-2012 19:30:20; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */

