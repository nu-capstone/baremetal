# Good makefile and st-link example
# https://github.com/Malkavian/tuts/tree/master/stm/blinky

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
GDB		= $(TOOLS_DIR)/arm-none-eabi-gdb
RM      = rm -f

DEFINES = -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -DHSEVALUE=8000000
# CFLAGS  = -Wall -Wextra -ffreestanding -nostdlib -Warray-bounds -mcpu=cortex-m4 \
# 		  -mthumb --specs=nano.specs -I./$(INCDIR)
CFLAGS  = -Wall -Wextra -ffreestanding -nostdlib -Warray-bounds -mcpu=cortex-m4 \
		  -mthumb -I./$(INCDIR)
LDFLAGS = -L./lib/ -nostartfiles -nostdlib -l:libstm.a -T$(SRCDIR)/linker.ld \
		  -Wl,--gc-sections

all: $(PROJ_NAME)

$(PROJ_NAME): $(PROJ_NAME).elf

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p ./$(OBJDIR)
	$(CC) $(DEFINES) $(CFLAGS) -c $< -o $@
	$(AS) $(SRCDIR)/startup_stm32f40_41xxx.s -o $(OBJDIR)/startup.o

$(PROJ_NAME).elf: $(OBJS)
	mkdir -p ./$(BINDIR)
	$(CC) $^ $(OBJDIR)/startup.o $(LDFLAGS) -Wl,-Map=$(BINDIR)/$(PROJ_NAME).map -o $(BINDIR)/$@
	$(OBJCOPY) -O ihex $(BINDIR)/$(PROJ_NAME).elf $(BINDIR)/$(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(BINDIR)/$(PROJ_NAME).elf $(BINDIR)/$(PROJ_NAME).bin
	$(OBJDUMP) -D $(BINDIR)/$(PROJ_NAME).elf > $(BINDIR)/$(PROJ_NAME).dump
	size $(BINDIR)/$(PROJ_NAME).elf

.PHONY: clean flash debug

clean:
	$(RM) $(OBJDIR)/* $(BINDIR)/*

flash: $(PROJ_NAME).elf
	st-flash write $(BINDIR)/$(PROJ_NAME).bin 0x8000000

debug: CFLAGS += -DDEBUG -g3
debug: $(PROJ_NAME).elf
	$(GDB) -tui -silent -ex 'target extended-remote localhost:4242' $(BINDIR)/$(PROJ_NAME).elf
