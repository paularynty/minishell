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
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>

//own headers
# include "defines.h"
# include "parser.h"
# include "../libft/libft.h"

# define DEBUG
#ifdef DEBUG 
# define debug_print(...) fprintf(stderr, __VA_ARGS__)
#else
# define debug_print(...) ((void)0)
#endif

//# define CHECK
#ifdef CHECK
# define check_print(...) printf( __VA_ARGS__)
#else
# define check_print(...) ((void)0)
#endif

//global variable to carry the exit status. mrworldwide for now
//sig_atomic_t = atomic relative to signal handling
//(we can also just pass around the exit code in the struct, 
//let's decide on that later)
extern int	g_mrworldwide;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				flag;
	struct s_env	*next;
}	t_env;

typedef struct s_mini
{
	char	**env;
	char	**cmd;
	int		cmd_count;
	char	*cwd;
	char	*input;
	char	*heredoc;
	int		**pipes;
	int		*pids;
	int		exit_flag; // flag to check if minishell loop should be exited
	int		exit_code; //exit status to exit the entire program with
	int		abort;
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
void	handle_builtin(int id, t_mini *shell);
int		builtins(char *line);

//builtins/cd.c
int		update_pwd(t_mini *shell);
int		builtin_cd(t_mini *shell);

//builtins/echo.c
int		builtin_echo(char **cmd);

//builtins/exit.c
int		builtin_exit(t_mini *shell);

//builtins/export.c
int		count_array_elements(char **array);
int		builtin_export(t_mini *shell);

//builtins/pwd.c
int		builtin_pwd(t_mini *shell);

//builtins/unset.c
void	env_unset_variable(char **env, char *variable);
int		builtin_unset(t_mini *shell);

//environment/create_env.c
char	*env_get_variable(char **env, char *key);
int		env_set_variable(t_mini *shell, char *key, char *value);
int		env_update_shlvl(t_mini *shell);
char	**clone_env(char **env);

//environment/env.c
int		builtin_env(t_mini *shell);

//errors/errors.c
void	error_builtin(char *builtin, char *str, char *error_str);
int		error_cmd(t_mini *shell, char *cmd);

//execution/execute.c
void	execute(t_mini *shell, t_command *commands);

//execution/exec_dup_close.c
int		dup_input(t_mini *shell, t_command *command, int i);
int		dup_output(t_mini *shell, t_command *command, int i);
int		dup2_and_close(int old_fd, int new_fd);

//execution/exec_utils.c
int 	count_cmd_args_for_exec(t_token *tokens);
int		check_access(t_mini *shell, char *cmd);
void	wait_for_children(t_mini *shell, pid_t *pids);

//execution/exec_path.c
char	**get_env_path(char **env);
char	*get_full_path(char **env_path, char *cmd);
char	*get_cmd_path(t_mini *shell, char *cmd);

//execution/exec_pipeline.c
int		exec_child(t_mini *shell, t_command *command);

//execution/exec_redirect.c
// int		handle_heredoc(t_mini *shell, t_command *command);
// int		handle_input(t_command *cmd, int *error);
// int		handle_output(t_command *cmd, int *error);

//setup/setup.c
int		setup(t_mini *shell, char **env);

//signals/signals.cvoid	signal_heredoc(int signal)
void	signal_heredoc(int signal);
void	signal_ctrl_c(int signal);
void	signal_child(void);
void	signal_reset(void);
void	signal_init(void);

//utils/cleanup.c
void	cleanup(t_mini *shell);

//utils/prompt.c
void	get_prompt(t_mini *shell, char *prompt, size_t size);

#endif