/*
 *  Linker command file template for run-time configuration app.
 *  Use this file to build Linux apps for the PC with debug libraries.
 */
INPUT(
    /*
     *  Since there is no EDMA3 on the PC use cpu-copy
     *  versions of acpy3 and dman3 libraries.
     */
    ti/sdo/fc/acpy3/lib/debug/acpy3cpu.a86U
    ti/sdo/fc/dman3/lib/debug/dman3cpu.a86U
    ti/sdo/fc/rman/lib/debug/rmanNoYield.a86U
    ti/sdo/fc/utils/lib/debug/rmm.a86U
    ti/sdo/fc/utils/lib/debug/smgr.a86U
    ti/sdo/fc/utils/lib/debug/rmmp.a86U
    ti/sdo/fc/utils/lib/debug/smgrmp.a86U
    ti/sdo/fc/utils/lib/debug/shmMp.a86U
    ti/sdo/fc/utils/osalsupport/lib/debug/osal_support.a86U
    ti/sdo/fc/memutils/lib/debug/memutils_std.a86U

    /*
     *  These libraries may only be needed if RMAN is used. Put them here
     *  so the app doesn't have to add them.
     */
    ti/sdo/fc/ires/nullresource/lib/debug/nullres.a86U

    gnu/targets/rts86U/lib/gnu.targets.rts86U.a86U
    ti/sdo/fc/global/lib/debug/fcsettings.a86U
)

