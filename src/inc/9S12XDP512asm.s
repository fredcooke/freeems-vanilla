;	9S12XDP512asm.h
;
;	Copyright 2008 Sean Keys
;
;	This file is part of the FreeEMS project.
;
;	FreeEMS software is free software: you can redistribute it and/or modify
;	it under the terms of the GNU General Public License as published by
;	the Free Software Foundation, either version 3 of the License, or
;	(at your option) any later version.
;
;	FreeEMS software is distributed in the hope that it will be useful,
;	but WITHOUT ANY WARRANTY; without even the implied warranty of
;	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;	GNU General Public License for more details.
;
;	You should have received a copy of the GNU General Public License
;	along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/
;
;	We ask that if you make any changes to this file you email them upstream to
;	us at admin(at)diyefi(dot)org or, even better, fork the code on github.com!
;
;	Thank you for choosing FreeEMS to run your engine!

;	Full basic register definitions for the Freescale S912XDP512 processor
;	MC9S12XDP512V2.pdf Appendix G

;* Define the cores of the CPU

.equ PIMcore0,	0x0000	;ports A, B, E, ; inits, test
.equ MMCcore0,   0x000A  ;Module Mapping Control core section 0 modes
.equ PIMcore1,   0x000C  ;PIMcore section 1 TODO add explaination
.equ EBIcore,    0x000E  ;External Bus Interface
.equ MMCcore1,   0x0010  ;MMC core
.equ MISPCcore,  0x0018  ;Miscellaneous Peripheral Core, Device ID Register
.equ PIMcore2,   0x001C  ;memsiz, IRQ, HPRIO-------------------check with c128 to make sure
.equ DBMcore,    0x0020  ;Debug Module S12XDBG
.equ MMCcore2,   0x0030  ;PPAGE
.equ PIMcore3,   0x0032  ;Port K
.equ CRGcore,    0x0034  ;Clock and Reset Generator
.equ SCI0core,   0x00C8  ;Serial Com Interface 0(RS232 on adapt card)
.equ FCRcore,    0x0100  ;Flash Control Registers
.equ EEPROMcore, 0x0110  ;EEPROM Control Registers
;-----------------------------------------------------------

;                  PIMcore0
;*****************************************************************
.equ PORTA,    PIMcore0+0x00  ;I/O port A 8-bit data register
;
.equ PTA0,     0b00000001    ;port A bit 0
.equ PTA1,     0b00000010    ;port A bit 1
.equ PTA2,     0b00000100    ;port A bit 2
.equ PTA3,     0b00001000    ;port A bit 3
.equ PTA4,     0b00010000    ;port A bit 4
.equ PTA5,     0b00100000    ;port A bit 5
.equ PTA6,     0b01000000    ;port A bit 6
.equ PTA7,     0b10000000    ;port A bit 7


.equ PORTB,    PIMcore0+0x01  ;I/O port B 8-bit data register
;
.equ PTB0,     0b00000001    ;port B bit 0
.equ PTB1,     0b00000010    ;port B bit 1
.equ PTB2,     0b00000100    ;port B bit 2
.equ PTB3,     0b00001000    ;port B bit 3
.equ PTB4,     0b00010000    ;port B bit 4
.equ PTB5,     0b00100000    ;port B bit 5
.equ PTB6,     0b01000000    ;port B bit 6
.equ PTB7,     0b10000000    ;port B bit 7

.equ DDRA,     PIMcore0+0x02  ; I/O port A 8-bit data direction register
;
.equ DDRA0,    0b00000001    ;port A bit 0
.equ DDRA1,    0b00000010    ;port A bit 1
.equ DDRA2,    0b00000100    ;port A bit 2
.equ DDRA3,    0b00001000    ;port A bit 3
.equ DDRA4,    0b00010000    ;port A bit 4
.equ DDRA5,    0b00100000    ;port A bit 5
.equ DDRA6,    0b01000000    ;port A bit 6
.equ DDRA7,    0b10000000    ;port A bit 7

.equ DDRB,    PIMcore0+0x03    ;port B 8-bit date direction register
;
.equ DDRB0,    0b00000001    ;port B bit 0
.equ DDRB1,    0b00000010    ;port B bit 1
.equ DDRB2,    0b00000100    ;port B bit 2
.equ DDRB3,    0b00001000    ;port B bit 3
.equ DDRB4,    0b00010000    ;port B bit 4
.equ DDRB5,    0b00100000    ;port B bit 5
.equ DDRB6,    0b01000000    ;port B bit 6
.equ DDRB7,    0b10000000    ;port B bit 7

.equ PORTC,    PIMcore0+0x04   ;port C 8-bit data register
;
.equ PTC0,     0b00000001    ;port C bit 0
.equ PTC1,     0b00000010    ;port C bit 1
.equ PTC2,     0b00000100    ;port C bit 2
.equ PTC3,     0b00001000    ;port C bit 3
.equ PTC4,     0b00010000    ;port C bit 4
.equ PTC5,     0b00100000    ;port C bit 5
.equ PTC6,     0b01000000    ;port C bit 6
.equ PTC7,     0b10000000    ;port C bit 7

.equ PORTD,    PIMcore0+0x05   ;port D 8-bit data regsiter
;
.equ PTD0,     0b00000001    ;port D bit 0
.equ PTD1,     0b00000010    ;port D bit 1
.equ PTD2,     0b00000100    ;port D bit 2
.equ PTD3,     0b00001000    ;port D bit 3
.equ PTD4,     0b00010000    ;port D bit 4
.equ PTD5,     0b00100000    ;port D bit 5
.equ PTD6,     0b01000000    ;port D bit 6
.equ PTD7,     0b10000000    ;port D bit 7

.equ DDRC,    PIMcore0+0x06  ;port C 8-bit data direction register
;
.equ DDRC0,    0b00000001    ;port C bit 0
.equ DDRC1,    0b00000010    ;port C bit 1
.equ DDRC2,    0b00000100    ;port C bit 2
.equ DDRC3,    0b00001000    ;port C bit 3
.equ DDRC4,    0b00010000    ;port C bit 4
.equ DDRC5,    0b00100000    ;port C bit 5
.equ DDRC6,    0b01000000    ;port C bit 6
.equ DDRC7,    0b10000000    ;port C bit 7

.equ DDRD,    PIMcore0+0x07  ;port D 8-bit data direction register
;
.equ DDRD0,    0b00000001    ;port D bit 0
.equ DDRD1,    0b00000010    ;port D bit 1
.equ DDRD2,    0b00000100    ;port D bit 2
.equ DDRD3,    0b00001000    ;port D bit 3
.equ DDRD4,    0b00010000    ;port D bit 4
.equ DDRD5,    0b00100000    ;port D bit 5
.equ DDRD6,    0b01000000    ;port D bit 6
.equ DDRD7,    0b10000000    ;port D bit 7

.equ PORTE,   PIMcore0+0x08  ;port E 8-bit data regsiter
;
.equ PTE0,     0b00000001    ;port E bit 0 ;also see appendix
.equ PTE1,     0b00000010    ;port E bit 1 ;also see appendix
.equ PTE2,     0b00000100    ;port E bit 2
.equ PTE3,     0b00001000    ;port E bit 3
.equ PTE4,     0b00010000    ;port E bit 4
.equ PTE5,     0b00100000    ;port E bit 5
.equ PTE6,     0b01000000    ;port E bit 6
.equ PTE7,     0b10000000    ;port E bit 7


.equ DDRE,   PIMcore0+0x09   ;port E 8-bit data direction register
;
.equ DDRE0,    0b00000001    ;port E bit 0 ;also see appendix
.equ DDRE1,    0b00000010    ;port E bit 1 ;also see appendix
.equ DDRE2,    0b00000100    ;port E bit 2
.equ DDRE3,    0b00001000    ;port E bit 3
.equ DDRE4,    0b00010000    ;port E bit 4
.equ DDRE5,    0b00100000    ;port E bit 5
.equ DDRE6,    0b01000000    ;port E bit 6
.equ DDRE7,    0b10000000    ;port E bit 7

;                     MMCcore0
;****************************************************************
.equ MMCCTLo,MMCcore0+0x00 ;mmctrlo TODO add brief explaination
;
.equ CS0E,     0b00000001    ;mmctlo bit 0
.equ CS1E,     0b00000010    ;mmctlo bit 1
.equ CS2E,     0b00000100    ;mmctlo bit 2
;                            ;reserved
;                            ;reserved
;                            ;reserved
;                            ;reserved
;                            ;reserved

.equ MODE,   MMCcore0+0x01 ;MODE bits
;
;                            ;reserved
;                            ;reserved
;                            ;reserved
;                            ;reserved
;                            ;reserved
.equ MODA,     0b00100000    ;mode bit  A
.equ MODB,     0b01000000    ;mode bit  B
.equ MODC,     0b10000000    ;mode bit  C

;                         PIMcore1
;*************************************************************************
.equ PUCR,   PIMcore1+0x00 ;Pull Up Controll Register
;
.equ PUPAE,    0b00000001    ;pucr A bit enable
.equ PUPBE,    0b00000010    ;pucr B bit enable
.equ PUPCE,    0b00000100    ;pucr C bit enable
.equ PUPDE,    0b00001000    ;pucr D bit enable
.equ PUPEE,    0b00010000    ;pucr E bit enable
;                            ;reserved
.equ BKPUE,    0b01000000    ;pucr bit 6 TODO add exp
.equ PUPKE,    0b10000000    ;pucr bit 7 TODO add exp

.equ RDRIV,  PIMcore1+0x01 ;rdriv TODO add exp
;
.equ RDPA,     0b00000001    ;rdriv A bit
.equ RDPB,     0b00000010    ;rdriv B bit
.equ RDPC,     0b00000100    ;rdriv C bit
.equ RDPD,     0b00001000    ;rdriv D bit
.equ RDPE,     0b00010000    ;rdriv E bit
;                            ;reserved
;                            ;reserved
.equ RDPK,     0b10000000    ;rdriv bit 7 TODO add exp

;                         EBIcore
;*****************************************************************
.equ EBICTRL0, EBIcore+0x00 ;EBI TODO add exp
;
.equ ASIZ0,    0b00000001    ;ebictrl0 bit 0
.equ ASIZ1,    0b00000010    ;ebictrl0 bit 1
.equ ASIZ2,    0b00000100    ;ebictrl0 bit 2
.equ ASIZ3,    0b00001000    ;ebictrl0 bit 3
.equ ASIZ4,    0b00010000    ;ebictrl0 bit 4
.equ HDBE,     0b00100000    ;ebictrl0 bit 5
;                            ;bit 6 reserved
.equ ITHRS,    0b10000000    ;ebictrl0 bit 7

.equ EBICTRL1, EBIcore+0x01  ;ebictrl 1  TODO add brief explaination
;
.equ EXSTR0,   0b00000001    ;ebictrl1 bit 0
.equ EXSTR1,   0b00000010    ;ebictrl1 bit 1
.equ EXSTR2,   0b00000100    ;ebictrl1 bit 2
;                            ;reserved
;                            ;reserved
;                            ;reserved
;                            ;reserved
.equ EWAITE,   0b10000000    ;ebictrl1 bit 7

;                     MMCcore1
;*****************************************************************
.equ GPAGE,  MMCcore1+0x00 ;mmcore1 GPAGE
;
.equ GP0,      0b00000001    ;gpage bit 0
.equ GP1,      0b00000010    ;gpage bit 1
.equ GP2,      0b00000100    ;gpage bit 2
.equ GP3,      0b00001000    ;gpage bit 3
.equ GP4,      0b00010000    ;gpage bit 4
.equ GP5,      0b00100000    ;gpage bit 5
.equ GP6,      0b01000000    ;gpage bit 6
;                            ;reserved

.equ DIRECT, MMCcore1+0x01   ;mmcore1 direct
;
.equ DP8,      0b00000001   ;direct bit 0
.equ DP9,      0b00000010   ;direct bit 1
.equ DP10,     0b00000100   ;direct bit 2
.equ DP11,     0b00001000   ;direct bit 3
.equ DP12,     0b00010000   ;direct bit 4
.equ DP13,     0b00100000   ;direct bit 5
.equ DP14,     0b01000000   ;direct bit 6
.equ DP15,     0b10000000   ;direct bit 7

;             MMCcore1+0x02        ;reserved

.equ MMCCTL1, MMCcore1+0x03 ;MMCTL1 bits TODO add exp
;
.equ ROMON,    0b00000001   ; MMCTL1 bit 0
.equ ROMHM,    0b00000010   ; MMCTL1 bit 1
.equ EROMON,   0b00000100   ; MMCTL1 bit 2
;                           ;reserved
;                           ;reserved
;                           ;reserved
;                           ;reserved
;                           ;reserved
;                           ;reserved

;             MMCcore1+0x04;reserved
;             MMCcore1+0x05;reserved

.equ RPAGE,   MMCcore1+0x06 ; rpage bits
;
.equ RP0,      0b00000001   ;rpage bit 0
.equ RP1,      0b00000010   ;rpage bit 1
.equ RP2,      0b00000100   ;rpage bit 2
.equ RP3,      0b00001000   ;rpage bit 3
.equ RP4,      0b00010000   ;rpage bit 4
.equ RP5,      0b00100000   ;rpage bit 5
.equ RP6,      0b01000000   ;rpage bit 6
.equ RP7,      0b10000000   ;rpage bit 7

.equ EPAGE,   MMCcore1+0x07  ; epage bits
;
.equ EP0,      0b00000001    ;epage bit 0
.equ EP1,      0b00000010    ;epage bit 1
.equ EP2,      0b00000100    ;epage bit 2
.equ EP3,      0b00001000    ;epage bit 3
.equ EP4,      0b00010000    ;epage bit 4
.equ EP5,      0b00100000    ;epage bit 5
.equ EP6,      0b01000000    ;epage bit 6
.equ EP7,      0b10000000    ;epage bit 7

;                        MISPcore
;**********************************************************
;              MISPCcore+0x00;reserved
;              MISPCcore+0x01;reserved


.equ PARTIDH,   MISPCcore+0x02   ;device ID high register
.equ PARTIDL,   MISCPcore+0x03   ;device ID low register

;                        PIMcore2
;**********************************************************
.equ ECLKCTL,  PIMcore2+0x00  ;  todo add exp
;
.equ EDIV0,    0b00000001     ;ECLKCTL bit 0
.equ EDIV1,    0b00000010     ;ECLKCTL bit 1
;                             ;reserved
;                             ;reserved
;                             ;reserved
;                             ;reserved
.equ NCLKX2,   0b01000000     ;ECLKCTL bit 6
.equ NECLK,    0b10000000     ;ECLKCTL bit 7

;              PIMcore2+0x01  ;reserved

.equ IRQCR,    PIMcore2+0x02  ;add explain.
;
.equ IRQN,     0b01000000     ;IRQCR bit 6
.equ IRQE,     0b10000000     ;IRQCR bit 7
;                             ;reserved
;                             ;reserved
;                             ;reserved
;                             ;reserved
;                             ;reserved
;                             ;reserved

;               PIMcore2+0x03 ;reserved

;                             DBMcore
;*********************************************************
;DBGXCTL  represents the contents if the Comparator A or C
;  control register is blended into this address
;DBGXCTL  represents the contents if the comparator B or D
;  control register is blended into this address
;*********************************************************

.equ DBGC1,   DBMcore+0x00    ;Debug control register 1
;
.equ COMRV,    0b00000011     ;
;
.equ DBGBRK,   0b00001100     ;
;
.equ BDM,      0b00010000     ;
.equ XGSBPE,   0b00100000     ;
.equ TRIG,     0b01000000     ;
.equ ARM,      0b10000000     ;

.equ DBGSR,   DBMcore+0x01  ;debug status register
;
.equ SSF0,     0b00000001     ;
.equ SSF1,     0b00000010     ;
.equ SSF2,     0b00000100     ;
;                             ;reserved
;                             ;reserved
;                             ;reserved

.equ EXTF,     0b01000000     ;
.equ TBF,      0b10000000     ;

.equ DBGTCR,  DBMcore+0x02   ;
;
.equ TALIGN,   0b00000011    ;
;
.equ TRCMOD,   0b00001100    ;
;
.equ TRANGE,   0b00110000    ;
;
.equ TSOURCE,  0b11000000    ;
;

.equ DBGC2,   DBMcore+0x03  ;
;
.equ ABCM,     0b00000011    ;
;
.equ CDCM,     0b00001100    ;
;
;                            ;reserved
;                            ;reserved
;                            ;reserved
;                            ;reserved

.equ DBGTBH,   DBMcore+0x04   ;debug trace buffer high register (bits 8-15)

.equ DBGTBL,   DBMcore+0x05   ;debug trace buffer low register (bits 0-7)

.equ DBGCNT,   DBMcore+0x06   ;debug count regsiter bits 0-6  bit 7 reserved
;
.equ CNT,      0b011111111    ;

.equ DBGSCRX,  DBMcore+0x07   ;debug comparator c expansion register
;
.equ SC0,       0b00000001    ;SCO bit
.equ SC1,       0b00000010    ;SC1 bit
.equ SC2,       0b00000100    ;SC2 bit
.equ SC3,       0b00001000    ;SC3 bit
;                             ;reserved
;                             ;reserved
;                             ;reserved
;                             ;reserved

.equ DBGXCTL,  DBMcore+0x08   ;IF COMPARITOR A or C CONTROL REGISTER IS BLENDED INTO THIS ADDRESS(DEFAULT)
;
.equ COMPE,     0b00000001    ;
.equ SRC,       0b00000010    ;
.equ RWE,       0b00000100    ;
.equ RW,        0b00001000    ;
.equ BRK,       0b00010000    ;
.equ TAG,       0b00100000    ;
.equ NDB,       0b01000000    ;
;                             ;reserved

;.equ DBGXCTL,  DBMcore+0x08   ;IF COMPARITOR B or D CONTROL REGISTER IS BLENDED INTO THE ADDRESS
;
;.equ COMPE,     0b00000001    ;
;.equ SRC,       0b00000010    ;
;.equ RWE,       0b00000100    ;
;.equ RW,        0b00001000    ;
;.equ BRK,       0b00010000    ;
;.equ TAG,       0b00100000    ;
;.equ SZ,        0b01000000    ;
;.equ SZE,       0b10000000    ;reserved

.equ DBGXAH,    DBMcore+0x09  ;TODO add exp

.equ DBGXAM,    DBMcore+0x0A  ;TODO add exp

.equ DBGXAL,    DBMcore+0x0B  ;TODO add exp

.equ DBGXDH,    DBMcore+0x0C  ;TODO add exp

.equ DBGXDL,    DBMcore+0x0D  ;TODO add exp

.equ DBGXDHM,   DBMcore+0x0E  ;TODO add exp

.equ DBGXDLM,   DBMcore+0x0F  ;TODO add exp

.equ PPAGE,    MMCcore2+0x00   ;TODO add exp
;
.equ PIX0,       0b00000001   ;PIX bit 0
.equ PIX1,       0b00000010   ;PIX bit 1
.equ PIX2,       0b00000100   ;PIX bit 2
.equ PIX3,       0b00001000   ;PIX bit 3
.equ PIX4,       0b00010000   ;PIX bit 4
.equ PIX5,       0b00100000   ;PIX bit 5
.equ PIX6,       0b01000000   ;PIX bit 6
.equ PIX7,       0b10000000   ;PIX bit 7

;                             ;reserved

.equ PORTK,   PIMcore3+0x00   ; Port K
;
.equ PTK0,       0b00000001   ;port k bit 0
.equ PTK1,       0b00000010   ;port k bit 1
.equ PTK2,       0b00000100   ;port k bit 2
.equ PTK3,       0b00001000   ;port k bit 3
.equ PTK4,       0b00010000   ;port k bit 4
.equ PTK5,       0b00100000   ;port k bit 5
.equ PTK6,       0b01000000   ;port k bit 6
.equ PTK7,       0b10000000   ;port k bit 7

.equ DDRK,    PIMcore3+01     ;port k data direction register
;
.equ DDRK0,      0b00000001   ;port k data direction register bit 0
.equ DDRK1,      0b00000010   ;port k data direction register bit 1
.equ DDRK2,      0b00000100   ;port k data direction register bit 2
.equ DDRK3,      0b00001000   ;port k data direction register bit 3
.equ DDRK4,      0b00010000   ;port k data direction register bit 4
.equ DDRK5,      0b00100000   ;port k data direction register bit 5
.equ DDRK6,      0b01000000   ;port k data direction register bit 6
.equ DDRK7,      0b10000000   ;port k data direction register bit 7

.equ SYNR,    CRGcore+0x00    ;CRG synthesizer register
;
.equ SYN0,       0b00000001   ;CRG synthesizer register 0
.equ SYN1,       0b00000010   ;CRG synthesizer register 1
.equ SYN2,       0b00000100   ;CRG synthesizer register 2
.equ SYN3,       0b00001000   ;CRG synthesizer register 3
.equ SYN4,       0b00010000   ;CRG synthesizer register 4
.equ SYN5,       0b00100000   ;CRG synthesizer register 5
;                             ;reserved
;                             ;reserved

.equ REFDV,   CRGcore+0x01    ;CRG reference divider register
;
.equ REFDV0,     0b00000001   ;CRG reference divider register bit 0
.equ REFDV1,     0b00000010   ;CRG reference divider register bit 2
.equ REFDV2,     0b00000100   ;CRG reference divider register bit 3
.equ REFDV3,     0b00001000   ;CRG reference divider register bit 4
.equ REFDV4,     0b00010000   ;CRG reference divider register bit 5
;                             ;reserved
;                             ;reserved

;.equ CTFLG,  CRGcore+0x02    ;reserved for factory test

.equ CRGFLG,  CRGcore+0x03    ;CRG flags register
;
.equ SCM,        0b00000001   ;CRG SCM bit
.equ SCMIF,      0b00000010   ;CRG SCMIF bit
.equ TRACK,      0b00000100   ;CRG TRACK bit
.equ LOCK,       0b00001000   ;CRG LOCK bit
.equ LOCKIF,     0b00010000   ;CRG LOCKIF bit
.equ LVRF,       0b00100000   ;CRG LVRF bit
.equ PORF,       0b01000000   ;CRG PORF bit
.equ RTIF,       0b10000000   ;CRG RTIF bit

.equ CRGINT,  CRGcore+0x04    ;CRGINT
;
;                             ;reserved
.equ SCMIE,      0b00000010   ;CRGINT SCMIE bit
;                             ;reserved
;                             ;reserved
.equ LOCKIE,     0b00010000   ;CRGINT LOCKIE bit
;                             ;reserved
;                             ;reserved
.equ ILAF,       0b01000000   ;CRGINT ILAF bit
.equ RTIE,       0b10000000   ;CRGINT RTIE bit

.equ CLKSEL,  CRGcore+0x05    ;CRG clock select register
;
.equ COPWAI,     0b00000001   ;CLKSEL COPWAI register
.equ RTIWAI,     0b00000010   ;CLKSEL RTIWAI register
;                             ;reserved
.equ PLLWAI,     0b00000100   ;CLKSEL PLLWAI register
;                             ;reserved
;                             ;reserved
.equ PSTP,       0b01000000   ;CLKSEL PST register
.equ PLLSEL,     0b10000000   ;CLKSEL PLLSEL register

.equ PLLCTL,  CRGcore+0x06    ;CRG PLL control register
;
.equ SCME,       0b00000001   ;PLLCTL SCME bit
.equ PCE,        0b00000010   ;PLLCTL PCE bit
.equ PRE,        0b00000100   ;PLLCTL PRE bit
.equ FSTWKP,     0b00001000   ;PLLCTL FSTWKP bit
.equ ACQ,        0b00010000   ;PLLCTL ACQ bit
.equ AUTO,       0b00100000   ;PLLCTL AUTO bit
.equ PLLON,      0b01000000   ;PLLCTL PLLON bit
.equ CME,        0b10000000   ;PLLCTL CME bit

.equ RTICTL,  CRGcore+0x07    ;RTICTL
;
.equ RTR0,       0b00000001   ;RTICTL RTR0 bit
.equ RTR1,       0b00000010   ;RTICTL RTR1 bit
.equ RTR2,       0b00000100   ;RTICTL RTR2 bit
.equ RTR3,       0b00001000   ;RTICTL RTR3 bit
.equ RTR4,       0b00010000   ;RTICTL RTR4 bit
.equ RTR5,       0b00100000   ;RTICTL RTR5 bit
.equ RTR6,       0b01000000   ;RTICTL RTR6 bit
.equ RTDEC,      0b10000000   ;RTICTL RTDEC bit

.equ COPCTL,  CRGcore+0x08    ;COP control register
;
.equ CR0,        0b00000001   ;COP watchdog timer rate select
.equ CR1,        0b00000010   ;COP watchdog timer rate select
.equ CR2,        0b00000100   ;COP watchdog timer rate select
;                             ;reserved
;                             ;reserved
;                             ;reserved
.equ RSBCK,      0b01000000   ;COP and RTI stop in active BDM mode bit
.equ WCOP,       0b10000000   ;TODO add def

;.equ FORBYP, CRGcore+0x09    ;reserved for factory test

;.equ CTCL,   CRGcore+0x0A    ;reserved for factory test

.equ ARMCOP,  CRGcore+0x0B    ;CRG COP arm/timer reset register

;                       SCI0
;************************************************************************
;SCI0BDH/SCI0BDL/SCI0BDL registers are accessable if the AMAP bit in the
;	SCI0SR2 register is set to ZERO
;SCI0ASR1/SCIACR1/SCI0ACR2 registers are accessible if the AMAP bit in
;	the SCI0SR2 register is set to ONE
;
;************************************************************************
.equ SCI0BDH, SCI0core+0x00  ;SCI0 baud rate registers (8-12 bits)
; f (as in first) added as prefix so names dont conflict with other SCIs
.equ fSBR8,      0b00000001   ;
.equ fSBR9,      0b00000010   ;
.equ fSBR10,     0b00000100   ;
.equ fSBR11,     0b00001000   ;
.equ fSBR12,     0b00010000   ;
.equ fTNP0,      0b00100000   ;
.equ fTNP1,      0b01000000   ;
.equ fIREN,      0b10000000   ;

.equ SCI0BDL, SCI0core0+0x01 ;SCI baud rate registers (0-7 bits)
; f (as in first) added as prefix so names dont conflict with other SCIs
.equ fSBR0,      0b00000001   ;
.equ fSBR1,      0b00000010   ;
.equ fSBR2,      0b00000100   ;
.equ fSBR3,      0b00001000   ;
.equ fSBR4,      0b00010000   ;
.equ fSBR5,      0b00100000   ;
.equ fSBR6,      0b01000000   ;
.equ fSBR7,      0b10000000   ;

.equ SCI0CR1,  SCI0core+0x02  ;SCI0 control register 1
; f (as in first) added as prefix so names dont conflict with other SCIs
.equ fPT,        0b00000001   ;
.equ fPE,        0b00000010   ;
.equ fILT,       0b00000100   ;
.equ fWAKE,      0b00001000   ;
.equ fM,         0b00010000   ;
.equ fRSRC,      0b00100000   ;
.equ fSCSIWAI,   0b01000000   ;
.equ fLOOPS,     0b10000000   ;

.equ SCI0ASR1,  SCI0core+0x03  ;SCI0 status register
; f (as in first) added as prefix so names dont conflict with other SCIs
.equ fBKDIF,     0b00000001   ;
.equ fBERRIF,    0b00000011   ;
.equ fBERRV,     0b00000100   ;
;                             ;reserved
;                             ;reserved
;                             ;reserved
;                             ;reserved
.equ fRXEDGIF,   0b10000000   ;

.equ SCI0ACR1,  SCI0core+0x04  ;
; f (as in first) added as prefix so names dont conflict with other SCIs
.equ fBKDIE,     0b00000001   ;
.equ fBERRIE,    0b00000010   ;
;                             ;reserved
;                             ;reserved
;                             ;reserved
;                             ;reserved
;                             ;reserved
.equ RXEDGIE,    0b10000000   ;

.equ SCI0ACR2,  SCI0core+0x05  ;
; f (as in first) added as prefix so names dont conflict with other SCIs
.equ fBKDFE,     0b00000001   ;
.equ fBERRMO,    0b00000010   ;
.equ fBERMM1,    0b00000100   ;
;                             ;reserved
;                             ;reserved
;                             ;reserved
;                             ;reserved
;                             ;reserved

.equ SCI0CR2,   SCI0core+0x06  ;
; f (as in first) added as prefix so names dont conflict with other SCIs
.equ fSBK,       0b00000001   ;
.equ fRWU,       0b00000010   ;
.equ fRE,        0b00000100   ;
.equ fTE,        0b00001000   ;
.equ fILIE,      0b00010000   ;
.equ fRIE,       0b00100000   ;
.equ fTCIE,      0b01000000   ;
.equ fTIE,       0b10000000   ;

.equ SCI0SR1,   SCI0core+0x07  ;
; f (as in first) added as prefix so names dont conflict with other SCIs
.equ fPF,        0b00000001   ;
.equ fFE,        0b00000010   ;
.equ fNF,        0b00000100   ;
.equ fOR,        0b00001000   ;
.equ fIDLE,      0b00010000   ;
.equ fRDRF,      0b00100000   ;
.equ fTC,        0b01000000   ;
.equ fTDRE,      0b10000000   ;

.equ SCI0SR2,  SCI0core+0x08   ;
; f (as in first) added as prefix so names dont conflict with other SCIs
.equ fRAF,       0b00000001   ;
.equ fTXDIR,     0b00000010   ;
.equ fBRK13,     0b00000100   ;
.equ fRXPOL,     0b00001000   ;
.equ fTXPOL,     0b00010000   ;
;                             ;reserved
;                             ;reserved
.equ fAMAP,      0b10000000   ;

.equ SCI0DRH,  SCI0core+0x09   ;
; f (as in first) added as prefix so names dont conflict with other SCIs
;                             ;reserved
;                             ;reserved
;                             ;reserved
;                             ;reserved
;                             ;reserved
;                             ;reserved
.equ fT8,        0b01000000   ;
.equ fR8,        0b10000000   ;

.equ SCI0DRL,  SCI0core+0x0A  ;
; f (as in first) added as prefix so names dont conflict with other SCIs
.equ fR0,	 0b00000001   ;
.equ fR1,	 0b00000010   ;
.equ fR2,	 0b00000100   ;
.equ fR3,        0b00001000   ;
.equ fR4,        0b00010000   ;
.equ fR5,        0b00100000   ;
.equ fR6,        0b01000000   ;
.equ fR7,        0b10000000   ;
;
.equ fT0,	 0b00000001   ;
.equ fT1,	 0b00000010   ;
.equ fT2,	 0b00000100   ;
.equ fT3,        0b00001000   ;
.equ fT4,        0b00010000   ;
.equ fT5,        0b00100000   ;
.equ fT6,        0b01000000   ;
.equ fT7,        0b10000000   ;

;                         FCRcore
;**********************************************************

.equ FCLKDIV,  FCRcore+0x00   ;Flash clock divide register
;
.equ FDIV0,      0b00000001   ;
.equ FDIV1,      0b00000010   ;
.equ FDIV2,      0b00000100   ;
.equ FDIV3,      0b00001000   ;
.equ FDIV4,      0b00010000   ;
.equ FDIV5,      0b00100000   ;
.equ PRDIV,      0b01000000   ;
.equ FDIVLD,     0b10000000   ;

.equ FSEC,    FCRcore+0x01    ;Flash Security Revister
;
.equ SEC0,       0b00000001   ;
.equ SEC1,       0b00000010   ;
.equ RNV2,       0b00000100   ;
.equ RNV3,       0b00001000   ;
.equ RNV4,       0b00010000   ;
.equ RNV5,       0b00100000   ;
.equ KEYEN0,     0b01000000   ;
.equ KEYEN1,     0b10000000   ;

.equ FTSTMOD, FCRcore+0x02    ;
;
;                             ;reserved
;                             ;reserved
;                             ;reserved
;                             ;reserved
.equ WRALL,      0b00010000   ;
.equ MRDS,       0b01100000   ;
;                             ;reserved

.equ FCNFG,   FCRcore+0x03    ;
;
;                             ;reserved
;                             ;reserved
;                             ;reserved
;                             ;reserved
;                             ;reserved
.equ KEYACC,     0b00100000   ;
.equ CCIE,       0b01000000   ;
.equ CBEIE,      0b10000000   ;

.equ FPROT,   FCRcore+0x04    ;
;
.equ FPLS0,      0b00000001   ;
.equ FPLS1,      0b00000010   ;
.equ FPLDIS,     0b00000100   ;
.equ FPHS0,      0b00001000   ;
.equ FPHS1,      0b00010000   ;
.equ FPHSDIS,    0b00100000   ;
.equ RNV6,       0b01000000   ;
.equ FPOPEN,     0b10000000   ;

.equ FSTAT,   FCRcore+0x05    ;
;
;                             ;reserved
;                             ;reserved
.equ BLANK,      0b00000100   ;
;                             ;reserved
.equ ACCERR,     0b00010000   ;flash access error
.equ PVIOL,      0b00100000   ;protection violation
.equ CCIF,       0b01000000   ;command complete interrypt flag
.equ CBEIF,      0b10000000   ;command buffer empty mode commands

.equ FCMD,   FCRcore+0x06     ;flash command register
;
.equ CMDB0,      0b00000001   ;
.equ CMDB1,      0b00000010   ;
.equ CMDB2,      0b00000100   ;
.equ CMDB3,      0b00001000   ;
.equ CMDB4,      0b00010000   ;
.equ CMDB5,      0b00100000   ;
.equ CMDB6,      0b01000000   ;
;                             ;reserved

.equ ClearMass,     CMDB6+CMDB0  ;
.equ ClearSection,  CMDB6        ;
.equ WriteWord,     CMDB5        ;

.equ FCTL,   FCRcore+0x07    ;
;
.equ NV0,        0b00000001   ;
.equ NV1,        0b00000010   ;
.equ NV2,        0b00000100   ;
.equ NV3,        0b00001000   ;
.equ NV4,        0b00010000   ;
.equ NV5,        0b00100000   ;
.equ NV6,        0b01000000   ;
.equ NV7,        0b10000000   ;

.equ FADDRHI, FCRcore+0x08    ; bits 0-7

.equ FADDRLO, FCRcore+0x09    ;bits 0-7

.equ FDATAHI, FCRcore+0x0A    ;bits 0-7

.equ FDATALO, FCRcore+0x0B    ;bits 0-7

; FCRcore+0x0C-0x0F reserved

;                 EEPROM
;*******************************************************

.equ ECLKDIV,  EEPROMcore+0x00  ;EEPROM clock divide register
;
.equ EDIV0,      0b00000001     ;
.equ EDIV1,      0b00000010     ;
.equ EDIV2,      0b00000100     ;
.equ EDIV3,      0b00001000     ;
.equ EDIV4,      0b00010000     ;
.equ EDIV5,      0b00100000     ;
.equ PRDIV8,     0b01000000     ;
.equ EDIVLD,     0b10000000     ;

;     EEPROMcore+0x01 reserved

;     EEPROMcore+0x02 reserved

.equ ECNFG,  EEPROMcore+0x03     ;EEPROM configuration register
;
;                                ;reserved
;                                ;reserved
;                                ;reserved
;                                ;reserved
;                                ;reserved
;                                ;reserved
.equ CCIER,      0b01000000      ;
.equ CBEIER,     0b10000000      ;

.equ EPROT,  EEPROMcore+0x04     ;
;
.equ EPS0,       0b00000001      ;
.equ EPS1,       0b00000010      ;
.equ EPS2,       0b00000100      ;
.equ EPDIS,      0b00001000      ;
.equ RNV4,       0b00010000      ;
.equ RNV5,       0b00100000      ;
.equ RNV6,       0b01000000      ;
.equ EPOPEN,     0b10000000      ;

.equ ESTAT,  EEPROMcore+0x05     ;EEPROM status register
;
;                                ;reserved
;                                ;reserved
.equ BLANKR,      0b00000100     ;
;                                ;reserved
.equ ACCERRR,     0b00010000     ;
.equ PVIOLR,      0b00100000     ;
.equ CCIFR,       0b01000000     ;
.equ CBEIFR,      0b10000000     ;

.equ ECMD,   EEPROMcore+0x06     ;EEPROM command buffer and register
;
.equ CMDB0R,      0b00000001     ;
.equ CMDB1R,      0b00000010     ;
.equ CMDB2R,      0b00000100     ;
.equ CMDB3R,      0b00001000     ;
.equ CMDB4R,      0b00010000     ;
.equ CMDB5R,      0b00100000     ;
.equ CMDB6R,      0b01000000     ;
;                                ;reserved

;            EEPROMcore+0x07  reserved

.equ EADDRHI, EEPROMcore+0x08    ;
;
.equ EABHI,       0b00000111     ;
;                                ;bits 3-7 reserved

.equ EADDRLO, EEPROMcore+0x09    ;
;
.equ EABLO,       0b11111111     ;

.equ EDATAHI, EEPROMcore+0x0A    ;
;
.equ EDHI,        0b11111111     ;

.equ EDATALO, EEPROMcore+0x0B    ;
;
.equ EDLO,        0b11111111     ;
