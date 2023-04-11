# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/05 12:01:03 by suchua            #+#    #+#              #
#    Updated: 2023/04/06 19:47:16 by suchua           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# LIB NAME
NAME			=	libft.a
INCLUDES		=	include/	
OBJS_DIR		=	objs/
SRCS_DIR		=	srcs/
CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra
ARCR			=	ar -crs
RM				=	rm -rf

# FILES
ATOITOA_FILES	=	ft_atoi ft_itoa
IS_FILES		=	ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint ft_isspace
LST_FILES		=	ft_lstadd_back ft_lstadd_front ft_lstclear ft_lstdelone \
					ft_lstiter ft_lstlast ft_lstmap ft_lstnew ft_lstsize
MEM_FILES		=	ft_calloc ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset
PRINTF_FILES	=	ft_flags ft_print_nb ft_print_nb_utils ft_print_ch  \
					ft_printf ft_print_p ft_print_p_utils ft_print_usnb \
					ft_print_usnb_utils ft_print_x ft_print_x_utils
PUT_FILES		=	ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd
STR_FILES		=	ft_bzero ft_split ft_strchr ft_strdup ft_striteri ft_strjoin \
					ft_strlcat ft_strlcpy ft_strlen ft_strmapi ft_strncmp \
					ft_strnstr ft_strrchr ft_strtrim ft_substr
TO_FILES		=	ft_tolower ft_toupper
GNL_FILES		=	get_next_line_bonus get_next_line_utils_bonus
MATH_FILES		=	ft_pow ft_sqrt

# addprefix suffix .c
ATOITOA_SRCS	=	$(addprefix $(SRCS_DIR)ft_atoitoa/, $(addsuffix .c, $(ATOITOA_FILES)))
IS_SRCS			=	$(addprefix $(SRCS_DIR)ft_is/, $(addsuffix .c, $(IS_FILES)))
LST_SRCS		=	$(addprefix $(SRCS_DIR)ft_lst/, $(addsuffix .c, $(LST_FILES)))
MEM_SRCS		=	$(addprefix $(SRCS_DIR)ft_mem/, $(addsuffix .c, $(MEM_FILES)))
PRINTF_SRCS		=	$(addprefix $(SRCS_DIR)ft_printf/, $(addsuffix .c, $(PRINTF_FILES)))
PUT_SRCS		=	$(addprefix $(SRCS_DIR)ft_put/, $(addsuffix .c, $(PUT_FILES)))
STR_SRCS		=	$(addprefix $(SRCS_DIR)ft_str/, $(addsuffix .c, $(STR_FILES)))
TO_SRCS			=	$(addprefix $(SRCS_DIR)ft_to/, $(addsuffix .c, $(TO_FILES)))
GNL_SRCS		=	$(addprefix $(SRCS_DIR)gnl/, $(addsuffix .c, $(GNL_FILES)))
MATH_SRCS		=	$(addprefix $(SRCS_DIR)gnl/, $(addsuffix .c, $(MATH_FILES)))

# addprefix suffix .o
ATOITOA_OBJS	=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(ATOITOA_FILES)))
IS_OBJS			=	$(addprefix $(OBJS_DIR),  $(addsuffix .o, $(IS_FILES)))
LST_OBJS		=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(LST_FILES)))
MEM_OBJS		=	$(addprefix $(OBJS_DIR),  $(addsuffix .o, $(MEM_FILES)))
PRINTF_OBJS		=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(PRINTF_FILES)))
PUT_OBJS		=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(PUT_FILES)))
STR_OBJS		=	$(addprefix $(OBJS_DIR),  $(addsuffix .o, $(STR_FILES)))
TO_OBJS			=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(TO_FILES)))
GNL_OBJS		=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(GNL_FILES)))
MATH_SRCS		=	$(addprefix $(SRCS_DIR)gnl/, $(addsuffix .o, $(MATH_FILES)))



#concat all .c files
SRCS		= 	$(ATOITOA_SRCS)
SRCS		+= 	$(IS_SRCS)
SRCS		+=	$(LST_SRCS)
SRCS		+= 	$(MEM_SRCS)
SRCS		+=	$(PRINTF_SRCS)
SRCS		+=	$(PUT_SRCS)
SRCS		+=	$(STR_SRCS)
SRCS		+=	$(TO_SRCS)
SRCS		+=	$(GNL_SRCS)

#concat all .O files
OBJS		= 	$(ATOITOA_OBJS) \
			 	$(IS_OBJS) \
				$(LST_OBJS) \
			 	$(MEM_OBJS) \
				$(PRINTF_OBJS) \
				$(PUT_OBJS) \
				$(STR_OBJS) \
				$(TO_OBJS) \
				$(GNL_OBJS) \

# vpath %.c	$(SRCS_DIR)ft_atoitoa:$(SRCS_DIR)ft_is:$(SRCS_DIR)ft_lst:\
# 			$(SRCS_DIR)ft_mem:$(SRCS_DIR)ft_printf:$(SRCS_DIR)ft_put:\
# 			$(SRCS_DIR)ft_str:$(SRCS_DIR)ft_to:$(SRCS_DIR)gnl

# $(OBJS_DIR)%.o:%.c
# 	@$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

all:
	mkdir -p $(OBJS_DIR)
	make $(NAME)

$(OBJS_DIR)%.o:$(SRCS_DIR)ft_atoitoa/%.c
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c $^ -o $@

$(OBJS_DIR)%.o:$(SRCS_DIR)ft_is/%.c
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c $^ -o $@

$(OBJS_DIR)%.o:$(SRCS_DIR)ft_lst/%.c
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c $^ -o $@

$(OBJS_DIR)%.o:$(SRCS_DIR)ft_mem/%.c
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c $^ -o $@

$(OBJS_DIR)%.o:$(SRCS_DIR)ft_printf/%.c
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c $^ -o $@

$(OBJS_DIR)%.o:$(SRCS_DIR)ft_put/%.c
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c $^ -o $@

$(OBJS_DIR)%.o:$(SRCS_DIR)ft_str/%.c
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c $^ -o $@

$(OBJS_DIR)%.o:$(SRCS_DIR)ft_to/%.c
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c $^ -o $@

$(OBJS_DIR)%.o:$(SRCS_DIR)gnl/%.c
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c $^ -o $@

$(OBJS_DIR)%.o:$(SRCS_DIR)ft_math/%.c
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c $^ -o $@

$(NAME): $(OBJS)
	@$(ARCR) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS_DIR)

fclean:
	make clean
	$(RM) $(NAME)

re: fclean all

norm:
	@norminette -R CheckForbiddenSourceHeader $(INCLUDES) $(SRCS_DIR)
