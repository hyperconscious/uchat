BINNAME = ../uchat
CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -pthread

OBJDIR = obj
SRCDIR = src
UTILS_DIR = ../utils
SOUP_DIR = ../libs/libsoup/libsoup

HEADER_DIRS = $(sort $(dir $(wildcard *.h) $(wildcard */*.h) $(wildcard */*/*.h) $(wildcard */*/*/*.h)))
UTILS_HEADER_DIRS = $(sort $(dir $(wildcard $(UTILS_DIR)/*.h) $(wildcard $(UTILS_DIR)/*/*.h)))
SOUP_HEADER_DIRS = $(sort $(dir $(wildcard $(SOUP_DIR)/*.h) $(wildcard $(SOUP_DIR)/*/*.h)))

SRCS = $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/*/*.c) $(wildcard $(SRCDIR)/*/*/*.c) $(wildcard $(SRCDIR)/*/*/*/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

UTILS_LIB = $(UTILS_DIR)/libutils.a
SOUP_LIB = $(SOUP_DIR)/libsoup.a 
GTK_LIBS = -rdynamic `pkg-config --cflags --libs gtk+-3.0`
GTK_INC = `pkg-config --cflags gtk+-3.0`

INCLUDE_HEADER_DIRS = $(addprefix -I, $(HEADER_DIRS))
INCLUDE_UTILS_HEADER_DIRS = $(addprefix -I, $(UTILS_HEADER_DIRS))
INCLUDE_SOUP_HEADER_DIRS = $(addprefix -I, $(SOUP_HEADER_DIRS))
INCLUDE_ALL_HEADER_DIRS = $(INCLUDE_HEADER_DIRS) $(INCLUDE_UTILS_HEADER_DIRS)$(INCLUDE SOUP_HEADER_DIRS)

all: $(BINNAME)

$(BINNAME):
	@$(CC) -o $@ $^ $(UTILS_LIB) $(GTK_LIBS) $(SOUP_LIB)
	@printf "\033[32;1m$@ created\033[0m\n"

$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.c Makefile | $(OBJDIR)
	@mkdir -p $(@D)
	@$(CC) $(INCLUDE_ALL_HEADER_DIRS) $(GTK_INC) $(CFLAGS) -c $< -o $@
	@printf "\033[32mcompiled: \033[0m$(notdir $<)\n"

$(OBJDIR):
	@mkdir -p $@
	@printf "\033[32;1mclient/$@ created\033[0m\n"

uninstall: clean
	@rm -rf $(BINNAME)
	@printf "\033[31;37mdeleted: $(BINNAME)\033[0m\n"

clean:
	@rm -rf $(OBJDIR)
	@printf "\033[31;37mdeleted: client/$(OBJDIR)\033[0m\n"

reinstall: uninstall all

.PHONY: all uninstall clean reinstall
