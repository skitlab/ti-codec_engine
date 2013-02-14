/*
 *  Linker command file template for run-time configuration app.
 *  Copy this file to your build directory, and add codec libraries, to
 *  build Linux apps for the evm3530 with debug libraries.
 */
INPUT(
    /*
     *  Since there is no EDMA3 on the EVM3530 ARM, use cpu-copy
     *  versions of acpy3 and dman3 libraries.
     */
    ti/sdo/fc/acpy3/lib/debug/acpy3cpu.av5T
    ti/sdo/fc/dman3/lib/debug/dman3cpu.av5T
    ti/sdo/fc/rman/lib/debug/rmanNoYield.av5T
    ti/sdo/fc/utils/lib/debug/rmm.av5T
    ti/sdo/fc/utils/lib/debug/smgr.av5T
    ti/sdo/fc/utils/lib/debug/rmmp.av5T
    ti/sdo/fc/utils/lib/debug/smgrmp.av5T
    ti/sdo/fc/utils/lib/debug/shmMp.av5T
    ti/sdo/fc/utils/osalsupport/lib/debug/osal_support.av5T
    ti/sdo/fc/memutils/lib/debug/memutils.av5T

    /*
     *  These libraries may only be needed if RMAN is used. Put them here
     *  so the app doesn't have to add them.
     */
    ti/sdo/fc/ires/nullresource/lib/debug/nullres.av5T

    ti/sdo/fc/global/lib/debug/fcsettings.av5T
)

