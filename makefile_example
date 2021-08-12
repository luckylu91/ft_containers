NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra
SUBDIRS = $(shell find src -type d -mindepth 1)
SUBDIRS_OBJ = $(SUBDIRS:src/%=obj/%)
IFLAGS = -Iinclude -Isrc/libft
LFLAGS = -Lsrc/libft -lft -lncurses
DBFLAGS = -g3 -fsanitize=address
SRCS_REL =	$(addprefix ast/add/, add_textitem_totext.c add_textredir_tocmd.c \
	add_cmd_tochain.c addback_none_block_nodup.c addback_space_block.c)
SRCS_REL +=	$(addprefix ast/create_destroy/, create_ast.c create_block.c \
	destroy_block.c dup_block.c destroy_ast.c destroy_binary_ast.c \
	destroy_command_ast.c destroy_redir_ast.c destroy_text_ast.c)
SRCS_REL +=	$(addprefix ast/access/, access_binary.c access_command.c \
	access_redir.c access_text.c)
SRCS_REL +=	$(addprefix ast/parse/, identify_semicol.c parse_cmd.c \
	parse_cmdchain.c parse_cmdseq.c parse_redir.c parse_text.c skip_spaces.c to_str.c)
SRCS_REL +=	$(addprefix execution/ast_exe/, exe_cmd_utils.c exe_cmd_utils2.c \
	exe_cmd_utils3.c ft_builtin.c redir.c exe_cmd.c exe_ast.c error_msg.c error_redir.c pipe_exe.c)
SRCS_REL += $(addprefix block_api/, block_at.c is_chainop.c is_eof.c is_redirop.c \
	is_semicol.c is_space.c is_special.c is_wildcard.c parse_redirop.c is_text.c \
	is_dollar.c is_rawtext.c is_tilde.c block_str_at.c)
SRCS_REL +=	$(addprefix ast/errors/, unexpected_token.c)
SRCS_REL +=	$(addprefix term/, init_termcaps.c init_termios.c termcaps_utils.c \
	bigger_calloc.c linebuffer.c prompt.c)
SRCS_REL +=	$(addprefix searchdir/, dir_contains.c  dir_utils.c search_cmd.c \
	path_utils.c)
SRCS_REL +=	$(addprefix execution/builtin/, cd.c echo.c pwd.c export.c env.c \
	copy_environ.c unset.c export_utils.c exit.c)
SRCS_REL +=	$(addprefix execution/replace_env/, replace_env.c remove_spaces.c \
	remove_spaces_cmdchain.c our_getenv.c our_getcwd.c replace_env_block.c \
	replace_env_cmd.c replace_env_list.c)
SRCS_REL +=	$(addprefix error/, error_message.c ambiguous_redirect_error.c \
	bash_error_errno.c)
SRCS_REL +=	$(addprefix to_block/, to_block_main.c dollar.c dquote.c quote.c \
	separator.c to_block_utils.c redir_tild.c backslash.c dollar_utils.c)
SRCS_REL +=	$(addprefix get_next_line/, get_next_line.c get_next_line_utils.c)
SRCS_REL +=	$(addprefix hist/, add_hist_line.c create_hist.c destroy_hist.c \
	file_utils.c get_hist_line.c move_hist.c parse_file.c read_truncate_histfile.c \
	rewind_hist.c write_histfile.c)
SRCS_REL +=	$(addprefix main/, main.c process_line.c exit_properly.c \
	process_char.c signal_interrupt.c)
SRCS_REL +=	$(addprefix main/redirect_special_keys/, redirect_up_down.c \
	redirect_left_right.c redirect_tab.c redirect_tab_utils1.c redirect_tab_utils2.c)
SRCS = $(addprefix src/, $(SRCS_REL))
OBJS = $(SRCS:src/%.c=obj/%.o)
OBJS_DB = $(SRCS:src/%.c=obj/%.o_db)
LIBFT = src/libft/libft.a

all: $(LIBFT) $(NAME)

db:	$(OBJS_DB)
	$(CC) $(OBJS_DB) -o minishell_db $(IFLAGS) $(LFLAGS) $(CFLAGS) $(DBFLAGS)

$(NAME): $(OBJS)
	$(CC) -o $@ $(OBJS) $(IFLAGS) $(LFLAGS) $(CFLAGS)

$(LIBFT):
	make -C src/libft

libft:
	make -C src/libft

obj/%.o_db:	src/%.c
	$(CC) -o $@  -c $< $(IFLAGS) $(CFLAGS)

obj/%.o:	src/%.c
	$(CC) -o $@  -c $< $(IFLAGS) $(CFLAGS)

$(OBJS):	| $(SUBDIRS_OBJ)
$(OBJS_DB):	| $(SUBDIRS_OBJ)

$(SUBDIRS_OBJ):
	mkdir -p $(SUBDIRS_OBJ)

objdirs: $(SUBDIRS_OBJ)

_%:	_%.c $(OBJS)
	$(CC) $< $(OBJS) -o $@ $(IFLAGS) $(LFLAGS) $(CFLAGS)

_%_db:	_%.c $(OBJS_DB)
	$(CC) $< $(OBJS_DB) -o $@ $(IFLAGS) $(LFLAGS) $(CFLAGS) $(DBFLAGS)

echo:
	echo $(OBJS)


clean:
	make -C src/libft clean
	rm -rf $(SUBDIRS_OBJ)

fclean: clean
	make -C src/libft fclean
	rm -f $(NAME)
	rm -f minishell_db

re: fclean all

.PHONY: all libft clean fclean re
