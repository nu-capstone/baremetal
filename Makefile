PROJ_NAME = heart

TOOLS_DIR = /usr/bin

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SRCS     := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJS     := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

CC      = $(TOOLS_DIR)/arm-none-eabi-gcc
OBJCOPY = $(TOOLS_DIR)/arm-none-eabi-objcopy
OBJDUMP = $(TOOLS_DIR)/arm-none-eabi-objdump
AS		= $(TOOLS_DIR)/arm-none-eabi-as
RM      = rm -f

CFLAGS  = -Wall -Wextra -Warray-bounds -ffreestanding -mcpu=cortex-m4 -mthumb --specs=nosys.specs
LDFLAGS = -nostdlib -T$(SRCDIR)/linker.ld

all: $(PROJ_NAME)

$(PROJ_NAME): $(PROJ_NAME).elf

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p ./$(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
	$(AS) -o $(OBJDIR)/startup.o $(SRCDIR)/startup.S

$(PROJ_NAME).elf: $(OBJS)
	mkdir -p ./$(BINDIR)
	$(CC) $(INCLUDE) $(DEFS) $(CFLAGS) $(LDFLAGS) $^ -o $(BINDIR)/$@
	$(OBJCOPY) -O ihex $(BINDIR)/$(PROJ_NAME).elf $(BINDIR)/$(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(BINDIR)/$(PROJ_NAME).elf $(BINDIR)/$(PROJ_NAME).bin
	$(OBJDUMP) -D $(BINDIR)/$(PROJ_NAME).elf > $(BINDIR)/$(PROJ_NAME).dump
	size $(BINDIR)/$(PROJ_NAME).elf

.PHONY: clean flash

clean:
	$(RM) $(OBJDIR)/* $(BINDIR)/*

flash: $(PROJ_NAME).elf
	st-flash write $(BINDIR)/$(PROJ_NAME).bin 0x8000000
