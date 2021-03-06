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
 * */

var wizardVersion = "3.21.00";
var REQUIRED_GENALG_MAJOR = 2;
var REQUIRED_GENALG_VERS = '[2, 0, 0, 0]';
var COMPATIBLE_XDAIS = 'XDAIS 7.20.00.05'

var INIT_MESSAGE = "Codec Engine GenCodecPkg Wizard v" + wizardVersion
+ "\nTexas Instruments";

var ABOUT_MESSAGE = INIT_MESSAGE;

var FAQ_LINK = 'http://processors.wiki.ti.com/index.php/Codec_Engine_GenCodecPkg_Wizard_FAQ';
var WHAT_TYPE_LINK = 'http://processors.wiki.ti.com/index.php/Codec_Engine_GenCodecPkg_Wizard_FAQ#What_type_of_Codec_package_would_you_like_to_create.3F';
var FROM_GENALG_LINK = 'http://processors.wiki.ti.com/index.php/Codec_Engine_GenCodecPkg_Wizard_FAQ#Create_a_Codec_Package_From_a_.genalg_File';
var FROM_LIB_LINK = 'http://processors.wiki.ti.com/index.php/Codec_Engine_GenCodecPkg_Wizard_FAQ#Create_a_Codec_Package_From_an_XDM_Algorithm_Library';
var ENTER_INFO_LINK = 'http://processors.wiki.ti.com/index.php/Codec_Engine_GenCodecPkg_Wizard_FAQ#Create_an_XDM_Algorithm_and_Codec_Package';

var OPEN_GENALG_HOVER = 'Create a CE package that uses the algorithm package specified in a .genalg file';
var OPEN_LIB_HOVER = 'Create a CE package that uses an algorithm library file';
var ENTER_INFO_HOVER = 'Create a CE package that contains a basic algorithm implemention, including source code';

/* hover text for field labels in .genalg file pane */
var GENALG_MODULE_HOVER = 'The name of the algorithm module';
var GENALG_VENDOR_HOVER = 'The name of the algorithm vendor';
var GENALG_INTERFACE_HOVER = 'The name of the algorithm interface.\nHas the form I<Module>';
var GENALG_XDM_ALG_PKG_HOVER = 'The name of the algorithm package';
var GENALG_CODEC_PKG_HOVER = 'The name of the CE package to create';
var GENALG_TARGET = "The algorithm's build targets";

/* hover text for field labels in library file pane */
var LIB_MODULE_HOVER = GENALG_MODULE_HOVER;
var LIB_VENDOR_HOVER = GENALG_VENDOR_HOVER
var LIB_INTERFACE_HOVER = GENALG_INTERFACE_HOVER;
var LIB_SUFFIX_HOVER = "The suffix that identifies the algorithm's build target";
var LIB_ALGS_CE_PKG = GENALG_CODEC_PKG_HOVER;
var LIB_BASE_INTERFACE = 'The XDM interface that the algorithm implements';

/* hover text for field labels in manual data entry pane */
var ENTER_MODULE_HOVER = GENALG_MODULE_HOVER;
var ENTER_VENDOR_HOVER = GENALG_VENDOR_HOVER
var ENTER_INTERFACE_HOVER = GENALG_INTERFACE_HOVER;
var ENTER_BASE_INTERFACE_HOVER = LIB_BASE_INTERFACE;
var ENTER_PACKAGE_NAME_HOVER = 'The name of the package to create';
var ENTER_TARGET_HOVER = GENALG_TARGET;
var OUTPUT_HOVER = 'Destination directory. The generated package will be in:\n'
+'<Destination Directory>/<Package Name with.dots.turned.into.forward.slashes>';

var ENTER_XDAIS = '<XDAIS installation directory>';
var ENTER_CGTOOLS = '<C6000 TI codegen tools directory>';
var ENTER_M3_CGTOOLS = '<ARM M3 TI codegen tools directory>';
var ENTER_ARM_CGTOOLS = '<ARM GCC Linux codegen tools directory>';
var ENTER_OUTREPO = '<Package destination directory>';

var XDAIS_DESC = 'Your XDAIS installation directory, e.g. "C:/xdais/7_10_00_06" or\n' +
        'Codec Engine cetools directory, e.g. "C:/codec_engine_3_20_00_10/cetools"';
var CGTOOLS_DESC = 'Your TI C6000 codegen tools directory, e.g.\n' +
'"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c6000"';

var M3_CGTOOLS_DESC = 'Your TI ARM M3 codegen tools directory, e.g.\n' +
'"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/tms470"';

var ARM_CGTOOLS_DESC = 'Your ARM GCC Linux codegen tools directory, e.g.\n' +
'"/home/usr/arm/arm-2007q3"';

var targetList = [
    'ti.targets.C64P',
    'ti.targets.elf.C64P',
    'ti.targets.C674',
    'ti.targets.elf.C674',
    'ti.targets.arm.elf.M3',
    'gnu.targets.arm.GCArmv5T',
    'gnu.targets.arm.GCArmv6',
    'gnu.targets.arm.GCArmv7A'
];

var targetDesc = [
    'C64P COFF',
    'C64P ELF',
    'C674 COFF',
    'C674 ELF',
    'M3 ELF',
    'ARM v5T GCC Linux',
    'ARM v6 GCC Linux',
    'ARM v7A GCC Linux'
];

var targetSuffixes = [
    '64P',
    'e64P',
    '674',
    'e674',
    'em3',
    'v5T',
    'v6',
    'v7A'
];

var ccOpts = [
    '-mi10 -mo',
    '',
    '-mi10 -mo',
    '',
    '',
    '',
    '',
    ''
];

var cgTools = [
    'C64P',
    'C64P',
    'C674',
    'C674',
    'M3',
    'v5T',
    'v6',
    'v7A'
];

var IRES_HOVER = 'Check to add a generic implementation of the' 
+' IRES interface to your algorithm.\n'
+'You will have to modify generated source files to request'
+' specific IRES resources.';

var elfTargets = [
    'ti.targets.elf.C64P',
    'ti.targets.elf.C674',
    'ti.targets.elf.C64T',
    'ti.targets.arm.elf.M3',
    'gnu.targets.arm.GCArmv5T',
    'gnu.targets.arm.GCArmv6',
    'gnu.targets.arm.GCArmv7A',
    'gnu.targets.UCArm9',
    'gnu.targets.Linux86',
    'ti.targets.arm.elf.A8F',
];

var elfSuffixes = [
    'e64P',
    'e674',
    'e64T',
    'em3',
    'v5T',
    'v6',
    'v7A',
    '470uC',
    '86U',
    'ea8f',
];

var coffTargets = [
    'ti.targets.C64P',
    'ti.targets.C674',
];

/*
 *  @(#) ti.sdo.ce.wizards.gencodecpkg; 1, 0, 0, 0,1; 2-24-2012 19:32:33; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */

