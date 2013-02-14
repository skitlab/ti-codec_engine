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
 *  ======== SysCBuf.xdc ========
 */
 
/*!
 *  ======== SysCBuf ========
 *
 *  Implementation of `{@link ISystemSupport}` with circular buffer for
 *  output.
 *
 *  This implementation provides a fully functional implementation of
 *  all methods specified by `ISystemSupport`. 
 *  
 *  This module maintains a circular buffer where data is written on
 *  SysCBuf_putch(). When the buffer is full, data is overwritten, and
 *  SysCBuf internally keeps track of the number of characters lost
 *  due to overwrite. The output buffer can be statically configured
 *  or dynamically bound to a buffer using SysCBuf_bind().
 *
 *  When `System_flush()` is called the characters in the internal buffer
 *  are "output" using the user configuratble `{@link #outputFxn}`. There is
 *  also a user configurable "get" function that can be used to copy out a
 *  given amount from the circular buffer.
 *
 *  The difference between SysCBuf and the xdc.runtime.SysMin module, are
 *  the following additional features:
 *     - SysCBuf_bind() for dynamic binding of the circular output buffer.
 *     - SysCBuf_get() for copying a given amount of data from the output
 *       buffer to another buffer.
 *     - Maintaining the number of characters lost due to overrite, and the
 *       number of characters available for reading with SysCBuf_get().
 *
 *  As with all `ISystemSupport` modules, this module is the back-end for the 
 *  `{@link System}` module; application code does not directly call these
 *  functions. 
 */

@Template("./SysCBuf.xdt")
@ModuleStartup
module SysCBuf inherits xdc.runtime.ISystemSupport {
 
    /*!
     *  ======== bufSize ========
     *  Size (in MAUs) of the output.
     *
     *  An internal buffer of this size is allocated. All output is stored 
     *  in this internal buffer. 
     *
     *  If 0 is specified for the size, no buffer is created. 
     */
    config SizeT bufSize = 0;

    /*!
     *  ======== flushAtExit ========
     *  Flush the internal buffer during `{@link #exit}` or `{@link #abort}`.
     *
     *  If the application's target is a TI target, the internal buffer is
     *  flushed via the `HOSTwrite` function in the TI C Run Time Support
     *  (RTS) library.
     *
     *  If the application's target is not a TI target, the internal buffer
     *  is flushed to `stdout` via `fwrite(..., stdout)`.
     *
     *  Setting this parameter to `false` reduces the footprint of the 
     *  application at the expense of not getting output when the application
     *  ends via a `System_exit()`, `System_abort()`, `exit()` or `abort()`.  
     */
    config Bool flushAtExit = true;
 
    /*!
     *  ======== sectionName ========
     *  Section where the internal character output buffer is placed
     *
     *  The default is to have no explicit placement; i.e., the linker is
     *  free to place it anywhere in the memory map.
     */
    metaonly config String sectionName = null;
   
    /*!
     *  ======== OutputFxn ========
     *  Output characters in the specified buffer
     *
     *  The first parameter is a pointer to a buffer of characters to be
     *  output.  The second parameter is the number of characters in the
     *  buffer to output.
     *
     *  This function may be called with 0 as the second parameter.  In this
     *  case, the function should simply return.
     *  
     */
    typedef Void (*OutputFxn)(Char *, UInt);

    /*!
     *  ======== outputFxn ========
     *  User suplied character output function
     *
     *  If this parameter is set to a non-`null` value, the specified
     *  function will be called by to output characters buffered within
     *  `SysCBuf`.
     *
     *  For example, if you define a function named `myOutputFxn`, the
     *  following configuration fragment will cause `SysCBuf` to call
     *  `myOutputFxn` whenever the character buffer is flushed.
     *  @p(code)
     *      var SysCBuf = xdc.useModule("xdc.runtime.SysCBuf");
     *      SysCBuf.outputFxn = "&myOutputFxn";
     *  @p
     *
     *  If this parameter is not set, a default function will be used which
     *  uses the ANSI C Standard Library function `fwrite()` (or `HOSTwrite` 
     *  in the TI C Run Time Support library) to output
     *  accumulated output characters.
     *
     *  @see #OutputFxn
     */
    config OutputFxn outputFxn = null;
    
    /*!
     *  ======== abort ========
     *  Backend for `{@link System#abort()}`
     *
     *  This abort function writes the string to the internal
     *  output buffer and then gives all internal output to the 
     *  `{@link #outputFxn}` function if the `{@link #flushAtExit}` 
     *  configuration parameter is true.
     *
     *  @param(str)  message to output just prior to aborting
     *
     *      If non-`NULL`, this string should be output just prior to
     *      terminating. 
     *
     *  @see ISystemSupport#abort
     */
    override Void abort(String str);
    
    /*!
     *  ======== exit ========
     *  Backend for `{@link System#exit()}`
     *
     *  This exit function gives all internal output to the 
     *  `{@link #outputFxn}` function if the `{@link #flushAtExit}` 
     *  configuration parameter is true.
     *
     *  @see ISystemSupport#exit
     */
    override Void exit(Int stat);
    
    /*!
     *  ======== flush ========
     *  Backend for `{@link System#flush()}`
     *
     *  The `flush` writes the contents of the internal character buffer
     *  via the `{@link #outputFxn}` function.
     *
     *  @a(Warning)
     *  The `{@link System}` gate is used for thread safety during the
     *  entire flush operation, so care must be taken when flushing with
     *  this `ISystemSupport` module.  Depending on the nature of the
     *  `System` gate, your application's interrupt latency
     *  may become a function of the `bufSize` parameter!
     *
     *  @see ISystemSupport#flush
     */
    override Void flush();
    
    /*!
     *  ======== putch ========
     *  Backend for `{@link System#printf()}` and `{@link System#putch()}`
     *
     *  Places the character into an internal buffer. The `{@link #flush}` 
     *  sends the internal buffer to the `{@link #outputFxn}` function.
     *  The internal buffer is also sent to the `SysCBuf_outputFxn` 
     *  function by `{@link #exit}` and `{@link #abort}` if the 
     *  `{@link #flushAtExit}` configuration parameter is true.
     *
     *  @see ISystemSupport#putch
     */
    override Void putch(Char ch);
    
    /*!
     *  ======== ready ========
     *  Test if character output can proceed
     *
     *  This function returns true if the internal buffer is non-zero.
     *
     *  @see ISystemSupport#ready
     */
    override Bool ready();

    /*!
     *  ======== bind ========
     *  Bind the buffer 'buf' of size 'size' bytes to the SysCBuf trace buffer.
     *
     *  Return 0 if successful, -1 otherwise.
     */
    Int bind(Char *buf, UInt32 size);

    /*!
     *  ======== get ========
     *  Copy contents of the trace buffer. Return the number of characters
     *  remaining in 'avail'. Return the number of characters lost due to
     *  wrapping in 'lost'.
     *
     *  Return the number of characters copied.
     *
     */
    UInt32 get(Char *buf, UInt32 size, UInt32 *avail, UInt32 *lost);

    /*!
     *  ======== getSize ========
     *  Return the size of the trace buffer.
     */
    UInt32 getSize();

internal:
    
    /*
     * ======== output ======== 
     *  System_output__I is generated based on bufSize.
     *
     *  This function is generated so that the code does not contain a call to
     *  HOSTwrite if bufSize is 0. Otherwise, if bufSize is 0, the compiler
     *  would optimize out the HOSTwrite function, leaving a 0-length symbol.
     *  If the a client later tried to pull in HOSTwrite, there would be a
     *  symbol error.
     *
     *  This generated function is accessed through an internal config so
     *  that it is an indirect call in the ROM case, but optimized to a direct
     *  call in the RAM case.
     */
    Void output(Char *buf, UInt size);
    readonly config OutputFxn outputFunc = '&ti_sdo_ce_utils_syscbuf_SysCBuf_output__I';

    struct Module_State {
        Char outbuf[];  /* the output buffer */
        UInt outidx;    /* index within outbuf to next Char to write */
        Bool wrapped;   /* has the index (outidx) wrapped */
        UInt32 bufSize; /* size of the trace buffer */
    }
}

/*
 *  @(#) ti.sdo.ce.utils.syscbuf; 1, 0, 0,1; 2-24-2012 19:31:42; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */

