;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;  BootLoader.                                                             ;;
;;  Copyright (C) 2007 Diolan ( http://www.diolan.com )                     ;;
;;                                                                          ;;
;;  This program is free software: you can redistribute it and/or modify    ;;
;;  it under the terms of the GNU General Public License as published by    ;;
;;  the Free Software Foundation, either version 3 of the License, or       ;;
;;  (at your option) any later version.                                     ;;
;;                                                                          ;;
;;  This program is distributed in the hope that it will be useful,         ;;
;;  but WITHOUT ANY WARRANTY; without even the implied warranty of          ;;
;;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           ;;
;;  GNU General Public License for more details.                            ;;
;;                                                                          ;;
;;  You should have received a copy of the GNU General Public License       ;;
;;  along with this program.  If not, see <http://www.gnu.org/licenses/>    ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Copyright (c) 2015 Kustaa Nyholm / SpareTimeLabs
; - modified NOT to use Extended Instruction Set (for compatibility with SDCC)
; - ported to PIC18F4550
; - ported to PIC18F45K50
; - extensively optimized to still fit in the 2 kB boot block
;
;-----------------------------------------------------------------------------
; Device Reset Vectors
;-----------------------------------------------------------------------------
	#include PROCESSOR_HEADER
	#include "boot.inc"
	#include "io_cfg.inc"
;-----------------------------------------------------------------------------
; Externals
;-----------------------------------------------------------------------------
	extern	main  
	extern	bootloader_soft_reset
;-----------------------------------------------------------------------------
; START
;-----------------------------------------------------------------------------
VECTORS		CODE	0x0000
	;--- RESET Vector
	org	0x0000
	clrf	TBLPTRU
	clrf	TBLPTRH
	bra		pre_main
;-----------------------------------------------------------------------------
;--- HIGH Interrupt Vector
	org	0x0008
	goto	APP_HIGH_INTERRUPT_VECTOR
;-----------------------------------------------------------------------------
pre_main
	; JP_BOOTLOADER_PIN to digital mode
;
; Here is four words free if processors is ot 18F45K50
;
#ifdef __18F45K50
	movlw	0x80	; 3X PLL ratio mode
	movwf	OSCTUNE
;
	movlw	0x70	; Switch to 16MHz HFINTOSC
	movwf	OSCCON
#endif
;
	bra		main
;-----------------------------------------------------------------------------
;--- BOOTLOADER External Entry Point                         
	org	0x0016
 if USE_EEPROM_MARK 
	bra	bootloader_soft_reset
 endif        
        
        ;--- HIGH Interrupt Vector
	org	0x0018
	goto	APP_LOW_INTERRUPT_VECTOR
;-----------------------------------------------------------------------------
; APPLICATION STUB
;-----------------------------------------------------------------------------
APPSTRT CODE APP_RESET_VECTOR
	bra	$
;-----------------------------------------------------------------------------
	END
