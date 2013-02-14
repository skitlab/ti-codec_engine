@rem User: set this variable to point your XDC installation, trying the
@rem XDC_INSTALL_DIR environment var first...
@if "%XDC_INSTALL_DIR%"=="" set XDC_INSTALL_DIR=c:\xdc_3_10_05_61

@for %%f in (%0) do @set thisDir=%%~dpf

"%XDC_INSTALL_DIR%\xs" --xdcpath="%thisDir%packages" ti.sdo.ce.wizards.genserver %1 %2 %3 %4 %5 %6 %7 %8 %9
