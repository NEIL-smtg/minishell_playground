NAME		=	minishell
MAN_FILES	=	main ft_signal_handling utils utils2 \
				ft_wildcard ft_wildcard_utils \
				ft_dangling ft_dangling_pipe \
				ft_cmdlst ft_cmdlst_utils ft_cmdexec \
				ft_cmdredir ft_heredoc ft_redirlst ft_redir_exec \
				ft_parse_input
SRC_DIR		=	srcs/
OBJS_DIR	=	objs/
LIBFT_DIR	=	Libft/
LIBFT		=	libft.a
SRCS		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(MAN_FILES)))
OBJS		=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(MAN_FILES)))
GCC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
INC			=	-I/usr/local/opt/readline/include/
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
	@norminette -R CheckForbiddenSourceHeader $(SRCS)
	@make norm $(LIBFT_DIR)

redebug:
	$(RM) debug
	make debug