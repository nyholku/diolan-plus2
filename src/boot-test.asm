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
; BootLoader Main code
;-----------------------------------------------------------------------------
	#include PROCESSOR_HEADER
	#include "boot.inc"
	#include "io_cfg.inc"
	#include "usb_defs.inc"
	#include "usb_desc.inc"
	#include "usb.inc"
	#include "boot_if.inc"
;-----------------------------------------------------------------------------
; Configuration Bits 
;-----------------------------------------------------------------------------
#if CPU_5V_HS
;	CONFIG	PLLDIV = 4			; OSC/4 for 16MHz
	CONFIG	PLLDIV = 1			; OSC/1 for 4 MHz XTAL
	CONFIG  CPUDIV = OSC1_PLL2		; CPU_clk = PLL/2
	CONFIG 	USBDIV = 2			; USB_clk = PLL/2
	CONFIG 	FOSC = HSPLL_HS			; HS osc PLL	
#else
	CONFIG	PLLDIV = 4			; OSC/4 for 16MHz
	CONFIG  CPUDIV = OSC1_PLL2		; CPU_clk = Fosc
	CONFIG 	USBDIV = 2			; USB_clk = PLL/2
	CONFIG 	FOSC = HS			; HS osc
#endif
	CONFIG  FCMEN = ON			; Fail Safe Clock Monitor
	CONFIG  IESO = OFF			; Int/Ext switchover mode
	CONFIG  PWRT = ON			; PowerUp Timer
	CONFIG  BOR = OFF			; Brown Out
	CONFIG  VREGEN = ON			; Int Voltage Regulator
	CONFIG  WDT = OFF			; WatchDog Timer
	CONFIG  MCLRE = ON			; MCLR
	CONFIG  LPT1OSC = OFF			; Low Power OSC
	CONFIG  PBADEN = ON			; PORTB<4:0> A/D
	CONFIG  CCP2MX = ON			; CCP2 Mux RC1
	CONFIG  STVREN = ON			; Stack Overflow Reset
	CONFIG  LVP = OFF			; Low Voltage Programming
	CONFIG  ICPRT = OFF			; ICP
	CONFIG  XINST = OFF			; Ext CPU Instruction Set
	CONFIG	DEBUG = OFF			; Background Debugging
	CONFIG  CP0 = OFF			; Code Protect
	CONFIG  CP1 = OFF
	CONFIG  CP2 = OFF
	CONFIG  CPB = ON   			; Boot Sect Code Protect
	CONFIG  CPD = OFF  			; EEPROM Data Protect
	CONFIG  WRT0 = OFF 			; Table Write Protect
	CONFIG  WRT1 = OFF
	CONFIG  WRT2 = OFF 
	CONFIG  WRTB = ON  			; Boot Table Write Protest
	CONFIG  WRTC = ON  			; CONFIG Write Protect
	CONFIG  WRTD = OFF 			; EEPROM Write Protect
	CONFIG  EBTR0 = OFF			; Ext Table Read Protect
	CONFIG  EBTR1 = OFF
	CONFIG  EBTR2 = OFF
	CONFIG  EBTRB = ON 			; Boot Table Read Protect
;--------------------------------------------------------------------------
; External declarations
	extern	usb_sm_state
	extern	usb_sm_ctrl_state
	extern	ep1Bo
	extern	ep1Bi
	extern	SetupPkt
	extern	SetupPktCopy
	extern	pSrc
	extern	pDst
	extern	Count
	extern	ctrl_trf_session_owner
	extern	ctrl_trf_mem
	extern	eep_mark_set
;--------------------------------------------------------------------------
; Variables
BOOT_DATA	UDATA
	global	boot_cmd; 
	global	boot_rep;
	global	active_protocol
	global	idle_rate
active_protocol	res	1
idle_rate	res	1
boot_cmd	res	BOOT_CMD_SIZE
boot_rep	res	BOOT_REP_SIZE
;--------------------------------------------------------------------------
; HID buffers
USB_HID		UDATA	0x500
	global	hid_report_out
	global	hid_report_in
hid_report_out	res	HID_OUT_EP_SIZE	; OUT packet buffet
hid_report_in	res	HID_IN_EP_SIZE	; IN packed buffer

;--------------------------------------------------------------------------
BOOT_ASM_CODE CODE
	extern	usb_init
	extern	usb_sm_ctrl
	extern	usb_sm_reset
	extern	usb_sm_prepare_next_setup_trf
	extern	copy_boot_rep
	extern	USB_HID_DESC
	extern	USB_HID_RPT
	extern	hid_process_cmd
;--------------------------------------------------------------------------
; main
; DESCR : Boot Loader main routine.
; WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
; WARNING                                                 WARNING
; WARNING     This code is not a routine!!!               WARNING
; WARNING     RESET command is used to "exit" from main   WARNING
; WARNING                                                 WARNING
; WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
; INPUT : no
; OUTPUT: no
;--------------------------------------------------------------------------
count	res	1	;
	global	main
	EXTERN	xtea_decode
CODE_START_OFFS		equ	6
;	extern	boot_rep

main
    movlw   low(testdata)
    movwf   TBLPTRL
    movlw   high(testdata)
    movwf   TBLPTRH
    movlw   upper(testdata)
    movwf   TBLPTRU
;
    movlw   low(boot_cmd+6)
    movwf	FSR1L
    movlw   high(boot_cmd+6)
    movwf	FSR1H
;
	movlw	8
	movwf	count
;
loop
	tblrd	*+
	movf	TABLAT,W
	movwf	POSTINC1

	decfsz	count
	bra	loop

	call	xtea_decode


testdata
	db	"DEADBEEF"
	global	usb_sm_HID_init_EP
	global	usb_sm_HID_request
usb_sm_HID_init_EP
usb_sm_HID_request

;--------------------------------------------------------------------------
	END
