# Modify the instalation path if you want to install in another directory
INSTALATION_PATH = /usr/bin/pagetransmuter

CC = gcc
CFLAGS = -Wall -Werror
SRCDIR = src
BUILDDIR = build
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRCS))
DIRS = $(BUILDDIR)

TARGET=$(BUILDDIR)/pagetransmuter

all: $(DIRS) $(TARGET)

clean: 
	rm -fr $(BUILDDIR)

install: $(DIRS) $(TARGET)
	sudo mv $(TARGET) $(INSTALATION_PATH)
	make clean

debug: $(DIRS) $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) -g

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(DIRS):
	mkdir -p $@