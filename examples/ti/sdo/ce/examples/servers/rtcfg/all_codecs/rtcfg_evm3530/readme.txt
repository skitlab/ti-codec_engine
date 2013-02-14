To build this example:

1. Set up the environment variables in paths.mk
2. Build the configuration package by running

       gmake -f makecfg.mk clean
       gmake -f makecfg.mk

    This step needs to be done each time you change rtcfg_all.cfg or
    config.bld.

3. Build the example by running:

       gmake -f makeapp.mk clean
       gmake -f makeapp.mk

   When making changes only to the .c and .h source files, you can just run

       gmake -f makeapp.mk

   and do not need to rebuild the configuration package.