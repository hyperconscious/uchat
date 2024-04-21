LIBNAME = libsqlite

CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

OBJDIR = obj
SRCDIR = .

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

$(LIBNAME): $(OBJS)
	@ar rcs $@.a $^
	@printf "\033[32;1m$(notdir $@) created\033[0m\n"

$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[32mcompiled: \033[0m$(notdir $<)\n"

$(OBJDIR):
	@mkdir -p $@
	@printf "\033[32;1mSQLite/$@ created\033[0m\n"

uninstall : clean
	@rm -rf $(LIBNAME).a
	@printf "\033[31;37mdeleted: $(LIBNAME).a\033[0m\n"

clean:
	@rm -rf $(OBJDIR)
	@printf "\033[31;37mdeleted: SQLite/$(OBJDIR)\033[0m\n"

reinstall: uninstall $(LIBNAME)

.PHONY: all uninstall clean reinstall
