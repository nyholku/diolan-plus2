VID		= 0x1D50
PID		= 0x6020
XTEA_KEY	= '0x57,0x4A,0xB5,0x8C,0xD7,0x20,0xF4,0x26,0x91,0x7B,0x77,0xEA,0x8C,0x40,0x16,0x9C'

PROJECT		= bootloader
PROCESSOR	= 18f4550
	
SRCS		= boot.asm boot_asm.asm usb.asm usb_desc.asm vectors.asm xtea.asm
INCS		= boot_if.inc boot.inc io_cfg.inc usb_defs.inc usb_desc.inc usb.inc 
OBJS		= $(foreach f, $(SRCS), $(basename $(f)).o )

COF		= $(PROJECT).cof
HEX		= $(PROJECT).hex
MAP		= $(PROJECT).map

OBJ_DIR		= _output

#ASM		= ~/gputils-1.4.0-1/build/gpasm/gpasm
ASM			= /Applications/microchip/mplabx/mpasmx/mpasmx
#LINK		= ~/gputils-1.4.0-1/build/gplink/gplink
LINK		= /Applications/microchip/mplabx/mpasmx/mplink
MP2HEX		= /Applications/microchip/mplabx/mpasmx/mp2hex
MP2COD		= /Applications/microchip/mplabx/mpasmx/mp2cod 	

LKR		= $(PROJECT).lkr

#ASMFLAGS	= --mpasm-compatible 
ASMFLAGS	= -DPROCESSOR_HEADER="p$(PROCESSOR).inc"

ifneq ($(VID), "")
ASMFLAGS += -DBOOTLOADER_VID=$(VID)
endif

ifneq ($(PID), "")
ASMFLAGS += -DBOOTLOADER_PID=$(PID)
endif

ifneq ($(XTEA_KEY), "")
ASMFLAGS += -DXTEA_KEY=$(XTEA_KEY)
endif

all: $(HEX)

$(HEX): $(COF)

$(COF): $(OBJS)
	$(LINK) $(LKR) -p$(PROCESSOR) $(OBJS) -m$(MAP) -o$@
	$(MP2COD) -p $(PROCESSOR) $(PROJECT).cof

%.o: %.asm $(INCS)
	$(ASM) -q -p$(PROCESSOR) $< -e -y -o$@ $(ASMFLAGS)

clean:
	rm -f *.o *.ERR *.LST *.map *.cod *.cof *.hex
	rm -rf $(OBJ_DIR)

print:
	@echo "SRCS = $(SRCS)"
	@echo "INCS = $(INCS)"
	@echo "OBJS = $(OBJS)"

.PHONY: all clean print
