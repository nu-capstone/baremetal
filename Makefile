PROJ_NAME = heart

TOOLS_DIR = /usr/bin

SRCDIR = src
OBJDIR = obj
BINDIR = bin
INCDIR = inc

SRCS     := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJS     := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# TOOLS
CC      = $(TOOLS_DIR)/arm-none-eabi-gcc
OBJCOPY = $(TOOLS_DIR)/arm-none-eabi-objcopy
OBJDUMP = $(TOOLS_DIR)/arm-none-eabi-objdump
AS		= $(TOOLS_DIR)/arm-none-eabi-as
RM      = rm -f

DEFINES = -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER
CFLAGS  = -Wall -Wextra -Warray-bounds -ffreestanding -mcpu=cortex-m4 -mthumb \
		  --specs=nosys.specs -I$(INCDIR)
LDFLAGS = -nostdlib -L./lib/ -lstm -T$(SRCDIR)/linker.ld

all: $(PROJ_NAME)

$(PROJ_NAME): $(PROJ_NAME).elf

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p ./$(OBJDIR)
	$(CC) $(DEFINES) $(CFLAGS) -c $< -o $@
	$(AS) $(SRCDIR)/startup_stm32f40_41xxx.s -o startup.o

$(PROJ_NAME).elf: $(OBJS)
	mkdir -p ./$(BINDIR)
	$(CC) $(LDFLAGS) $^ startup.o -o $(BINDIR)/$@
	$(OBJCOPY) -O ihex $(BINDIR)/$(PROJ_NAME).elf $(BINDIR)/$(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(BINDIR)/$(PROJ_NAME).elf $(BINDIR)/$(PROJ_NAME).bin
	$(OBJDUMP) -D $(BINDIR)/$(PROJ_NAME).elf > $(BINDIR)/$(PROJ_NAME).dump
	size $(BINDIR)/$(PROJ_NAME).elf

.PHONY: clean flash

clean:
	$(RM) $(OBJDIR)/* $(BINDIR)/*

flash: $(PROJ_NAME).elf
	st-flash write $(BINDIR)/$(PROJ_NAME).bin 0x8000000
