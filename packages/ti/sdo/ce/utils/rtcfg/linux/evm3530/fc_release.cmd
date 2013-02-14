/*
 *  Linker command file template for run-time configuration app.
 *  Copy this file to your build directory, and add codec libraries, to
 *  build Linux apps for the evm3530 with release libraries.
 */
INPUT(
    /*
     *  Since there is no EDMA3 on the EVM3530 ARM, use cpu-copy
     *  versions of acpy3 and dman3 libraries.
     */
    ti/sdo/fc/acpy3/lib/release/acpy3cpu.av5T
    ti/sdo/fc/dman3/lib/release/dman3cpu.av5T
    ti/sdo/fc/rman/lib/release/rmanNoYield.av5T
    ti/sdo/fc/utils/lib/release/rmm.av5T
    ti/sdo/fc/utils/lib/release/smgr.av5T
    ti/sdo/fc/utils/lib/release/rmmp.av5T
    ti/sdo/fc/utils/lib/release/smgrmp.av5T
    ti/sdo/fc/utils/lib/release/shmMp.av5T
    ti/sdo/fc/utils/osalsupport/lib/release/osal_support.av5T
    ti/sdo/fc/memutils/lib/release/memutils.av5T

    /*
     *  These libraries may only be needed if RMAN is used. Put them here
     *  so the app doesn't have to add them.
     */
    ti/sdo/fc/ires/nullresource/lib/release/nullres.av5T

    ti/sdo/fc/global/lib/release/fcsettings.av5T
)

