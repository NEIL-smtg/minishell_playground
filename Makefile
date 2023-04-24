NAME		=	minishell
MAN_FILES	=	main signal/ft_signal_handling utils/utils utils/free \
				parsing/ft_parse_input parsing/ft_dangling parsing/ft_dangling_pipe \
				wildcard/ft_wildcard wildcard/ft_wildcard_utils \
				cmdlst/ft_cmdlst cmdlst/ft_cmdlst_utils exec/ft_exec cmdlst/ft_ms_split\
				redirections/ft_redirections redirections/ft_heredoc \
				redirections/ft_redirlst redirections/ft_redir_exec \
				redirections/ft_shell_output \
				builtins/ft_builtin builtins/ft_cd builtins/ft_echo \
				builtins/ft_env builtins/ft_export builtins/ft_pwd builtins/ft_unset
SRC_DIR		=	srcs/
OBJS_DIR	=	objs/
LIBFT_DIR	=	Libft/
LIBFT		=	libft.a
SRCS		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(MAN_FILES)))
OBJS		=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(MAN_FILES)))
GCC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
INC			=	-I/usr/local/opt/readline/include/
INC			+=	-I include/
RL			=	-L/usr/local/opt/readline/lib/
RL			+=	-lreadline
RM			=	rm -rf
FSAN		=	-fsanitize=address -g3
HEREDOC		=	.heredoc_tmp
DEBUG_FLAG	=	-fdiagnostics-color=always -g ${file} -o debug

all:
	@mkdir -p $(OBJS_DIR)
	@make $(LIBFT_DIR)$(LIBFT)
	@make $(NAME)

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	@$(GCC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(SRCS)
	$(GCC) $(FSAN) $(CFLAGS) $(INC) $(RL) $(SRCS) $(LIBFT_DIR)$(LIBFT) -o $(NAME)

$(LIBFT_DIR)$(LIBFT):
	@make -C $(LIBFT_DIR)

debug: $(SRCS) $(LIBFT_DIR)$(LIBFT)
	$(GCC) -fsanitize=address $(DEBUG_FLAG) $(INC) $(RL) $(SRCS) $(LIBFT_DIR)$(LIBFT)

clean:
	@$(RM) $(OBJS_DIR)

fclean:
	@make clean
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)
	@$(RM) $(HEREDOC)

re:
	@make fclean
	@make all

norm:
	@norminette -R CheckForbiddenSourceHeader $(SRCS) include/

redebug:
	$(RM) debug
	make debug