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
; I/O configuration
;-----------------------------------------------------------------------------
; Constants
;-----------------------------------------------------------------------------
; LED
#define USE_LED			1	; Undef/comment if you not want to use FW LED
#ifdef	USE_LED
#define LED   		LATB
#define LED_TRIS  	TRISB
#define LED_PIN			4
#endif
;-----------------------------------------------------------------------------
; Jumpers
;
; Note! Ensure that the jumper *is* in digital input mode, see vectors.asm/pre_main
;
#define USE_JP_BOOTLOADER_EN	1	; Undef/comment if you not want to use FW Jumper
;
#ifdef	USE_JP_BOOTLOADER_EN
;
#define JP_BOOTLOADER_ANSEL	ANSELC
#define JP_BOOTLOADER_TRIS	TRISC
#define JP_BOOTLOADER_PORT	PORTC
#define JP_BOOTLOADER_PIN	7	
;
; This macro is used to test (and skip) if the jumper is 'set'
; - modify to configure the port/pin as digital input for your PIC
; - modify to suit polarity (jumper 'set' == 1 or 0)
;
JP_BOOTLOADER_SKIP_IF_SET	macro

#ifdef __18F4550
#if JP_BOOTLOADER_PORT==PORTD
	movlw	0x0F		; wholesale PORTD all digital
	movwf	ADCON1
#else
	error	"Bad or unimplemented JP_BOOTLOADER_PORT definition"
#endif 
#endif

#ifdef __18F45K50
	movlb	0xF		
	bcf		JP_BOOTLOADER_ANSEL,JP_BOOTLOADER_PIN	
	movlb	0x0	
;	
	bsf		JP_BOOTLOADER_TRIS, JP_BOOTLOADER_PIN
	btfsc	JP_BOOTLOADER_PORT, JP_BOOTLOADER_PIN
#endif
;
	endm

#endif
;-----------------------------------------------------------------------------
