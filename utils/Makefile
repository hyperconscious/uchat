LIBNAME = libutils
CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
OBJDIR = obj
SRCDIR = src

HEADER_DIRS =  $(sort $(dir $(wildcard *.h) $(wildcard */*.h) $(wildcard */*/*.h) $(wildcard */*/*/*.h)))

SRCS = $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/*/*.c) $(wildcard $(SRCDIR)/*/*/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

INCLUDE_HEADER_DIRS = $(addprefix -I, $(HEADER_DIRS))

all: $(LIBNAME)

$(LIBNAME): $(OBJS)
	@ar rcs $@.a $^
	@printf "\033[32;1m$(notdir $@) created\033[0m\n"

$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) $(INCLUDE_HEADER_DIRS) -c $< -o $@
	@printf "\033[32mcompiled: \033[0m$(notdir $<)\n"

$(OBJDIR):
	@mkdir -p $@
	@printf "\033[32;1mutils/$@ created\033[0m\n"

uninstall : clean
	@rm -rf $(LIBNAME).a
	@printf "\033[31;37mdeleted: $(LIBNAME).a\033[0m\n"

clean:
	@rm -rf $(OBJDIR)
	@printf "\033[31;37mdeleted: utils/$(OBJDIR)\033[0m\n"

reinstall: uninstall all

.PHONY: all uninstall clean reinstall
