/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:11:50 by prynty            #+#    #+#             */
/*   Updated: 2024/12/11 15:44:01 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//standard headers
# include <errno.h>
# include <string.h> //for strerror
# include <stdlib.h> //for malloc, free
# include <unistd.h> //write, dup, dup2
# include <fcntl.h> //for O_RDONLY etc.
# include <stdio.h> // for printf
# include <signal.h> //for signal, SIGINT, SIGQUIT
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

//own headers
# include "defines.h"
# include "../libft/libft.h"

typedef struct s_mini
{
	char	**env;
	char	**cmd;
	char	*cwd;
	char	*heredoc;
	int		fd[2];
	int		exit_flag; // flag to check if minishell loop should be exited
	int		exit_code; //exit status to exit the entire program with
}	t_mini;

enum e_builtins {
	BUILTIN_NONE,
	BUILTIN_CD,
	BUILTIN_ECHO,
	BUILTIN_ENV,
	BUILTIN_EXIT,
	BUILTIN_EXPORT,
	BUILTIN_PWD,
	BUILTIN_UNSET
};

//builtins/builtins.c
void	handle_builtin(int id, t_mini *shell, char **cmd);
int		builtins(char *line);
void	builtin_exit(t_mini *shell, char **cmd);
void	builtin_pwd(t_mini *shell);

//builtins/cd.c
int		builtin_cd(t_mini *shell, char **cmd);

//builtins/echo.c
void	builtin_echo(char **cmd);

//builtins/env.c
char	*env_get_variable(char **env, char *key);
int		env_set_variable(char *key, char *value);
int		env_update_shell_level(t_mini *shell);
char	**env_clone(char **env);
void	builtin_env(char **env);

//builtins/export.c
int		count_array_elements(char **array);
int		builtin_export(t_mini *shell);

//errors/errors.c
void	error_builtin(char *builtin, char *str, char *error_str);
void	error_cmd(char *cmd, char **cmd_array);

//execution/execute.c
void	prep_command(t_mini *shell, char *line);
void	execute(t_mini *shell);

//setup/setup.c
int		setup(t_mini *shell, char **env);

//signals/signals.c
void	init_signals(void);

//utils/cleanup.c
void	cleanup(t_mini *shell);

//utils/prompt.c
void	get_prompt(t_mini *shell, char *prompt, size_t size);

#endif