# === Project Dirs ===
srcdir := main/ash
builddir := ../build
bindir := ../bin

arch := $(shell uname -m)
os := $(shell uname)

# === Compiler Flags and more ===
CC := gcc
CFLAGS := -Wall -Wextra -g -I $(srcdir)/inc

# === Targets ===
TARGET := $(bindir)/ash-$(arch)-$(os)

# === Files to compile and more ===
SRCS := $(shell find $(srcdir) -name '*.c')
OBJS := $(patsubst $(srcdir)/%.c, $(builddir)/%.o, $(SRCS))

# === Build Rules ===
all: setup $(TARGET)

# setup dirs if they do not exist
setup:
	@echo "Setting up directories..."
	@mkdir -p $(builddir)
	@mkdir -p $(bindir)

# Rule to link all objs and compile at the same time
$(TARGET): $(SRCS)
	@echo "Linking ..."
	$(CC) $(CFLAGS) $^ -o $@
	@echo "Build completed!"

clean:
	@echo "Cleaning..."
	@rm -rf $(builddir) $(bindir)
	@echo "Done!"

# Debug rule
debug: CFLAGS += -DDEBUG
debug: all

.PHONY: all clean debug setup
