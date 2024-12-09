# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/27 12:05:04 by prynty            #+#    #+#              #
#    Updated: 2024/12/09 10:43:01 by prynty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET 			= \033[0;39m
ORANGE 			= \e[1m\e[38;5;202m
YELLOW 			= \033[0;93m
YELLOW_BOLD		= \033[1;93m
GREEN			= \033[1;92m
CYAN 			= \033[0;96m
CYAN_BOLD 		= \033[1;96m
BLUE 			= \033[0;94m
BLUE_BOLD 		= \033[1;94m

OBJ_READY		= echo "📥 $(ORANGE)Compiled minishell files!$(RESET)"
COMP_LIBFT		= echo "📝 $(YELLOW)Compiling Libft...$(RESET)"
LIBFT_READY		= echo "📝 $(YELLOW_BOLD)Libft compiled!$(RESET)"
MS_READY		= echo "🤖 $(GREEN)minishell ready!$(RESET)"
CLEANING		= echo "💧 $(CYAN)Cleaning...$(RESET)"
CLEANED			= echo "💧 $(CYAN_BOLD)Successfully cleaned all object files!$(RESET)"
FCLEANING		= echo "🧼 $(BLUE)Deep cleaning...$(RESET)"
FCLEANED		= echo "🧼 $(BLUE_BOLD)Successfully cleaned all executable files!$(RESET)"
REMAKE			= echo "💡 $(GREEN)Successfully cleaned and rebuilt everything!$(RESET)"

NAME			= minishell

SRCDIR			= srcs
OBJDIR			= objs
LIBDIR			= libft
INCLUDE			= includes

CFLAGS			= -Wall -Wextra -Werror \
					-I $(INCLUDE)
LDFLAGS			= -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
LIBFT			= $(LIBDIR)/libft.a

SRCS			= $(SRCDIR)/main.c \
				$(SRCDIR)/builtins/builtins.c \
				$(SRCDIR)/builtins/cd.c \
				$(SRCDIR)/builtins/echo.c \
				$(SRCDIR)/builtins/exit.c \
				$(SRCDIR)/builtins/export.c \
				$(SRCDIR)/builtins/pwd.c \
				$(SRCDIR)/builtins/unset.c \
				$(SRCDIR)/environment/env_utils.c \
				$(SRCDIR)/environment/env.c \
				$(SRCDIR)/execution/exec_utils.c \
				$(SRCDIR)/execution/execute.c \
				$(SRCDIR)/errors/errors.c \
				$(SRCDIR)/signals/signals.c \
				$(SRCDIR)/setup/setup.c \
				$(SRCDIR)/utils/cleanup.c \
				$(SRCDIR)/utils/prompt.c \
				$(SRCDIR)/utils/utils.c \

OBJS			= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(COMP_LIBFT)
	@make -s -C $(LIBDIR) > /dev/null
	@$(LIBFT_READY)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@cc -c $(CFLAGS) $< -o $@

$(NAME): $(OBJS)
	@cc $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@$(OBJ_READY)
	@chmod 777 $(NAME)
	@$(MS_READY)

clean:
	@$(CLEANING)
	@rm -rf $(OBJDIR)
	@make clean -s -C $(LIBDIR)
	@$(CLEANED)

fclean: clean
	@$(FCLEANING)
	@rm -rf $(NAME)
	@make fclean -s -C $(LIBDIR)
	@rm -rf libft.a
	@$(FCLEANED)

re:	fclean all
	@$(REMAKE)

.PHONY: all clean fclean re libft