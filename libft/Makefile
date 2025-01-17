# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/17 18:26:18 by prynty            #+#    #+#              #
#    Updated: 2025/01/16 21:08:44 by prynty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET 		= \033[0;39m
BLACK		= \033[1;30m
DARK_RED	= \033[1;31m
DARK_GREEN	= \033[1;32m
DARK_YELLOW	= \033[1;33m
DARK_BLUE	= \033[1;34m
DARK_MAGENTA	= \033[1;35m
DARK_CYAN	= \033[1;36m
DARK_GRAY	= \033[0;90m
LIGHT_GRAY	= \033[1;37m
RED		= \033[1;91m
ORANGE 		= \e[1m\e[38;5;202m
YELLOW 		= \033[1;93m
GREEN		= \033[1;92m
BLUE 		= \033[1;94m
CYAN 		= \033[1;96m
MAGENTA 	= \033[1;95m
PINK		= \e[1m\e[38;5;212m
WHITE 		= \033[1;97m

COMP_START	= echo "\n🚧 $(ORANGE)Starting the compilation...$(RESET)"
COMP_FOLDERS	= echo "📥 $(ORANGE)Creating folders...$(RESET)"
COMP_LIBFT	= echo "📝 $(YELLOW)Libft compiled!$(RESET)$(DARK_GRAY)"
PS_READY	= echo "\n🧮 $(GREEN)Push_swap ready!$(RESET)"
CLEANED		= echo "\n💧 $(CYAN)Successfully cleaned all object files!\n$(RESET)"
FCLEANED	= echo "\n🧼 $(BLUE)Successfully cleaned all executable files!$(RESET)"
REMAKE		= echo "✅ $(GREEN)Successfully cleaned and rebuilt everything!$(RESET)"

NAME 		= libft.a

SRCS		= ft_atoi.c \
			ft_atol.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_free_array.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_isspace.c \
			ft_itoa.c \
			ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstsize.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_print_char.c \
			ft_print_hex.c \
			ft_print_nbr.c \
			ft_print_nbr_unsigned.c \
			ft_print_ptr.c \
			ft_print_str.c \
			ft_printf.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_strchr.c \
			ft_strcmp.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strndup.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			get_next_line.c \
			get_next_line_utils.c \

CFLAGS 		= -Wall -Wextra -Werror

OBJS		= $(SRCS:.c=.o)
BONUS_OBJS	= $(BONUS_SRCS:.c=.o)

all: 		$(NAME)

$(NAME):	$(OBJS)
		@ar rcs $(NAME) $(OBJS)
		@$(COMP_LIBFT)

%.o: %.c
		@cc $(CFLAGS) -c $< -o $@

clean:
		@rm -f $(OBJS)
		@rm -rf objs/

fclean: clean
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
