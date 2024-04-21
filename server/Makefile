BINNAME = ../uchat_server
CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -pthread

OBJDIR = obj
SRCDIR = src
UTILS_DIR = ../utils
SQLITE_DIR = ../SQLite

HEADER_DIRS = $(sort $(dir $(wildcard *.h) $(wildcard */*.h) $(wildcard */*/*.h) $(wildcard */*/*/*.h)))
UTILS_HEADER_DIRS = $(sort $(dir $(wildcard $(UTILS_DIR)/*.h) $(wildcard $(UTILS_DIR)/*/*.h)))
SQLITE_HEADER_DIRS = $(sort $(dir $(wildcard $(SQLITE_DIR)/*.h) $(wildcard $(SQLITE_DIR)/*/*.h)))

SRCS = $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/*/*.c) $(wildcard $(SRCDIR)/*/*/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

UTILS_LIB = $(UTILS_DIR)/libutils.a
SQLITE_LIB = $(SQLITE_DIR)/libsqlite.a 

INCLUDE_HEADER_DIRS = $(addprefix -I, $(HEADER_DIRS))
INCLUDE_UTILS_HEADER_DIRS = $(addprefix -I, $(UTILS_HEADER_DIRS))
INCLUDE_SQLITE_HEADER_DIRS = $(addprefix -I, $(SQLITE_HEADER_DIRS))
INCLUDE_ALL_HEADER_DIRS = $(INCLUDE_HEADER_DIRS) $(INCLUDE_UTILS_HEADER_DIRS) $(INCLUDE_SQLITE_HEADER_DIRS)

INCLUDE_UTILS = -L$(dir $(UTILS_LIB)) -l$(patsubst lib%.a,%,$(notdir $(UTILS_LIB)))
INCLUDE_SQLITE = -L$(dir $(SQLITE_LIB)) -l$(patsubst lib%.a,%,$(notdir $(SQLITE_LIB)))

all: $(BINNAME)

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
   SYSTEMDEPENDENT_LIBS += -lcrypt
endif

$(BINNAME): $(OBJS)
	@$(CC) -o $@ $^  $(SQLITE_LIB) $(UTILS_LIB) -pthread -ldl $(SYSTEMDEPENDENT_LIBS) 
	@printf "\033[32;1m$@ created\033[0m\n"

$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.c Makefile | $(OBJDIR)
	@mkdir -p $(@D)
	@$(CC) $(INCLUDE_ALL_HEADER_DIRS) $(CFLAGS) -c $< -o $@
	@printf "\033[32mcompiled: \033[0m$(notdir $<)\n"

$(OBJDIR):
	@mkdir -p $@
	@printf "\033[32;1mserver/$@ created\033[0m\n"

uninstall: clean
	@rm -rf $(BINNAME)
	@printf "\033[31;37mdeleted: $(BINNAME)\033[0m\n"

clean:
	@rm -rf $(OBJDIR)
	@printf "\033[31;37mdeleted: server/$(OBJDIR)\033[0m\n"

reinstall: uninstall all

.PHONY: all uninstall clean reinstall
