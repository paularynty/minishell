/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:11:50 by prynty            #+#    #+#             */
/*   Updated: 2024/11/18 16:19:41 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//standard headers
# include <string.h> //for strerror
# include <stdlib.h> //for malloc, free
# include <unistd.h> //write, dup, dup2
# include <fcntl.h> //for O_RDONLY etc.
# include <stdio.h> // for printf
# include <signal.h> //for signal, SIGINT, SIGQUIT
# include <readline/readline.h>
# include <readline/history.h>

//own headers
# include "defines.h"
# include "../libft/libft.h"

typedef struct s_mini
{
	char	**env;
	char	*cwd;
	char	*heredoc;
	int		fd[2];
	int		exit_flag;
}	t_mini;

//builtins/builtins.c
void	builtins(t_mini *shell, char *line);
void	builtin_env(char **env);
void	builtin_exit(t_mini *shell, char *line);
void	builtin_pwd(t_mini *shell);
char	**env_clone(char **env);

//setup/setup.c
int		setup(t_mini *shell, char **env);

//signals/signals.c
void	init_signals(void);

//utils/cleanup.c
void	cleanup(t_mini *shell);

//utils/prompt.c
void	get_prompt(t_mini *shell, char *prompt, size_t size);

#endif