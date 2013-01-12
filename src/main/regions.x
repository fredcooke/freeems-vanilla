/*	FreeEMS - the open source engine management system

	Copyright 2008, 2009 Fred Cooke

	This file is part of the FreeEMS project.

	FreeEMS software is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	FreeEMS software is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/

	We ask that if you make any changes to this file you email them upstream to
	us at admin(at)diyefi(dot)org or, even better, fork the code on github.com!

	Thank you for choosing FreeEMS to run your engine! */


/** @file
 *
 * @brief Region mapping linker script
 *
 * Code section to memory region mapping definition file for inclusion
 * into the linker script. This file provides rules which map pieces of
 * code and data from named sections into specific named memory regions.
 * See memory.x and hc9s12xdp512elfb.x for more information.
 *
 * A description of what some of this means can be found at the following URLs:
 * - http://www.gnu.org/software/m68hc11/m68hc11_binutils.html
 * - http://m68hc11.serveftp.org/wiki/index.php/FAQ:Link
 *
 * @cond regionsscript
 */


SECTIONS
{

/*&&&&&&&&&&&&&& RAM Regions &&&&&&&&&&&&&&*/

/* The main RAM region is called "data" and */
/* can be found in the main linker script   */

/* The RAM page window through which all tunable config is reached. */
  .rpage :
  {
    *(.rpage)
  } > rpage

/* Comms transmission buffer */
  .txbuf :
  {
    *(.txbuf)
  } > txbuf

/* Comms reception buffer */
  .rxbuf :
  {
    *(.rxbuf)
  } > rxbuf


/*&&&&&&&&&&&&&& Linear Flash Regions &&&&&&&&&&&&&&*/

/* Primary linear code and persistent data is called */
/* "text" and can be found in the main linker script */

/* Secondary linear code and persistent data */
  .text1  :
  {
    *(.text1)
  }  > text1

/* This is the flash page window. */
/* We use this as paged blocks not directly so it's commented out. */
/*  .text2  :
  {
    *(.text2)
  }  > text2 */

/* Non live tunable configuration items 1 */
  .fixedconf1  :
  {
    *(.fixedconf1)
  }  > fixedconf1

/* Non live tunable configuration items 1 */
  .fixedconf2  :
  {
    *(.fixedconf2)
  }  > fixedconf2


/*&&&&&&&&&&&&&& Paged Flash Regions &&&&&&&&&&&&&&*/

/* PPAGE FA is used for fuel tables and setup function */
  .dpageFA  :
  {
    *(.dpageFA)
  }  > dpageFA

  .fpageFA  :
  {
    *(.fpageFA)
  }  > fpageFA

/* PPAGE FB is used for smaller tunables and setup function */
  .fpageFB  :
  {
    *(.fpageFB)
  }  > fpageFB

/* Data split up into eight chunks to catch size mistakes better */
  .dpageFB1 :
  {
    *(.dpageFB1)
  }  > dpageFB1

  .dpageFB2  :
  {
    *(.dpageFB2)
  }  > dpageFB2

  .dpageFB3  :
  {
    *(.dpageFB3)
  }  > dpageFB3

  .dpageFB4  :
  {
    *(.dpageFB4)
  }  > dpageFB4

  .dpageFB5  :
  {
    *(.dpageFB5)
  }  > dpageFB5

  .dpageFB6  :
  {
    *(.dpageFB6)
  }  > dpageFB6

  .dpageFB7  :
  {
    *(.dpageFB7)
  }  > dpageFB7

  .dpageFB8  :
  {
    *(.dpageFB8)
  }  > dpageFB8

/* PPAGE FC is used for timing tables and setup function */
  .dpageFC  :
  {
    *(.dpageFC)
  }  > dpageFC

  .fpageFC  :
  {
    *(.fpageFC)
  }  > fpageFC

/* The rest from this 128k flash module for general code */
  .ppageF8  :
  {
    *(.fpageF8)
    *(.dpageF8)
  }  > ppageF8

  .fpageF9  :
  {
    *(.fpageF9)
  }  > fpageF9

  .dpageF9  :
  {
    *(.dpageF9)
  }  > dpageF9

  .ppageFE  :
  {
    *(.ppageFE)
  }  > ppageFE

/* The following two blocks are included just for clarity */
/* and are the same as text1 and text when paged.         */
/*  .ppageFD  : (text1 / 0x4000 - 0x7FFF)
  {
    *(.ppageFD)
  }  > ppageFD

  .ppageFF  : (text / 0xC000 - 0xFFFF)
  {
    *(.ppageFF)
  } > ppageFF */


  .ppageE0X  :
  {
    *(.ppageE0X)
  }  > ppageE0X

  .ppageE0S  :
  {
    *(.ppageE0S)
  }  > ppageE0S

  .ppageE1  :
  {
    *(.ppageE1)
  }  > ppageE1

  .ppageE2  :
  {
    *(.ppageE2)
  }  > ppageE2

  .ppageE3  :
  {
    *(.ppageE3)
  }  > ppageE3

  .ppageE4  :
  {
    *(.ppageE4)
  }  > ppageE4

  .ppageE5  :
  {
    *(.ppageE5)
  }  > ppageE5

  .ppageE6  :
  {
    *(.ppageE6)
  }  > ppageE6

  .ppageE7  :
  {
    *(.ppageE7)
  }  > ppageE7

  .ppageE8  :
  {
    *(.ppageE8)
  }  > ppageE8

  .ppageE9  :
  {
    *(.ppageE9)
  }  > ppageE9

  .ppageEA  :
  {
    *(.ppageEA)
  }  > ppageEA

  .ppageEB  :
  {
    *(.ppageEB)
  }  > ppageEB

  .ppageEC  :
  {
    *(.ppageEC)
  }  > ppageEC

  .ppageED  :
  {
    *(.ppageED)
  }  > ppageED

  .ppageEE  :
  {
    *(.ppageEE)
  }  > ppageEE

  .ppageEF  :
  {
    *(.ppageEF)
  }  > ppageEF

  .ppageF0  :
  {
    *(.ppageF0)
  }  > ppageF0

  .ppageF1  :
  {
    *(.ppageF1)
  }  > ppageF1

  .ppageF2  :
  {
    *(.ppageF2)
  }  > ppageF2

  .ppageF3  :
  {
    *(.ppageF3)
  }  > ppageF3

  .ppageF4  :
  {
    *(.ppageF4)
  }  > ppageF4

  .ppageF5  :
  {
    *(.ppageF5)
  }  > ppageF5

  .ppageF6  :
  {
    *(.ppageF6)
  }  > ppageF6

  .ppageF7  :
  {
    *(.ppageF7)
  }  > ppageF7
}


/** @endcond */
