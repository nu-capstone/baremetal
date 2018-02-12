PROJ_NAME = libstm

TOOLS_DIR = /usr/bin

SRCDIR = src
OBJDIR = obj

STMDIR	 := STM32F4xx_StdPeriph_Driver
SRCS     := $(wildcard $(STMDIR)/$(SRCDIR)/*.c)
# INCLUDES := $(STMDIR)/$(wildcard $(INCDIR)/*.h)
OBJS     := $(SRCS:$(STMDIR)/$(SRCDIR)/%.c=$(STMDIR)/$(OBJDIR)/%.o)
# OBJS     := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

CC      = $(TOOLS_DIR)/arm-none-eabi-gcc
OBJCOPY = $(TOOLS_DIR)/arm-none-eabi-objcopy
OBJDUMP = $(TOOLS_DIR)/arm-none-eabi-objdump
AS		= $(TOOLS_DIR)/arm-none-eabi-as
AR		= $(TOOLS_DIR)/arm-none-eabi-ar
RM      = rm -f

CFLAGS  = -Wall -Wextra -DSTM32F40_41xxx -Warray-bounds -ffreestanding -mcpu=cortex-m4 -mthumb --specs=nosys.specs -I./$(STMDIR)/inc -I./CMSIS/Include

all: $(PROJ_NAME)

$(PROJ_NAME): $(PROJ_NAME).a

$(OBJS): $(STMDIR)/$(OBJDIR)/%.o : $(STMDIR)/$(SRCDIR)/%.c
	mkdir -p ./$(STMDIR)/$(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(PROJ_NAME).a: $(OBJS)
	$(AR) rcs $(PROJ_NAME).a $^

.PHONY: clean

clean:
	@echo $(SRCS)
	@echo $(OBJS)
	# $(RM) $(STMDIR)/$(OBJDIR)/* ./$(PROJ_NAME).a

