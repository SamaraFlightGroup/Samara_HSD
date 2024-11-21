/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright (c) 2008-2013 Code Red Technologies Ltd,
 * Copyright 2015, 2018-2019 NXP
 * (c) NXP Semiconductors 2013-2022
 * Generated linker script file for MIMXRT1062xxxxA
 * Created from library.ldt by FMCreateLinkLibraries
 * Using Freemarker v2.3.30
 * MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13] on Oct 11, 2022, 9:04:16 PM
 */

GROUP (
  "libgcc.a" /* holds gcc math functions, weird shit without it*/

  "libc_nano.a" /*holds things like new() free() and such*/
  "libstdc++_nano.a" /*Probs C++ std:: and stuff*/
  /*"libstdc++.a"
  "libc.a"/**/

  "libm.a" /*holds C math functions like acosf*/
  "libcr_newlib_nohost.a" /*Holds malloc I think*/

  "crti.o" /*C runtime objects*/
  "crtn.o"
  "crtbegin.o"
  "crtend.o"
)
