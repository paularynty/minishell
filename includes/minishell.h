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
# include <termios.h> //for tcgetattr, tcsetattr

//own headers
# include "defines.h"
# include "parser.h"
# include "structs.h"
# include "../libft/libft.h"

// # define DEBUG
#ifdef DEBUG 
# define debug_print(...) fprintf(stderr, __VA_ARGS__)
#else
# define debug_print(...) ((void)0)
#endif

// # define CHECK
#ifdef CHECK
# define check_print(...) printf( __VA_ARGS__)
#else
# define check_print(...) ((void)0)
#endif

//builtins/builtins.c
int		handle_builtin(int id, t_mini *shell, t_cmd *cmd);
int		builtins(char *line);

//builtins/cd.c
int		update_pwd(t_mini *shell);
int		builtin_cd(t_mini *shell, t_cmd *cmd);

//builtins/echo.c
int		builtin_echo(char **cmd);

//builtins/exit.c
int		builtin_exit(t_mini *shell, t_cmd *cmd, char **args);

//builtins/export.c
int		count_array_elements(char **array);
int		builtin_export(t_mini *shell, t_cmd *cmd);

//builtins/pwd.c
int		builtin_pwd(t_mini *shell);

//builtins/unset.c
void	env_unset_variable(char **env, char *variable);
int		builtin_unset(t_mini *shell, t_cmd *cmd);

//environment/env_utils.c
void	remove_eq(t_mini *shell, char *arg);
char	*env_get_variable(char **env, char *key);
int		env_update_shlvl(t_mini *shell);
char	**clone_env(char **env);

//environment/env.c
int		env_set_variable(t_mini *shell, char *key, char *value);
int		env_find_index(char **env, char *key);
int		builtin_env(t_mini *shell);

//errors/errors_syntax.c
void	error_quotes(t_mini *shell, char *str);
void	error_syntax(t_mini *shell, char *str);

//errors/errors.c
void	error_builtin(char *builtin, char *str, char *error_str);
void	error_cmd(t_mini *shell, t_cmd *cmds, char *cmd, char *error_str, int ex);
void	error_export(char *str);
void	error_file(t_mini *shell, char *file, char *error_str, int ex);

//execution/execute.c
int		execute(t_mini *shell, t_cmd *cmd);

//execution/exec_dup_close.c
int		resolve_fds(t_mini *shell, t_cmd *cmd);
int		dup_input(t_mini *shell, t_cmd *cmd, int i);
int		dup_output(t_mini *shell, t_cmd *cmd, int i);
int		dup2_close(int old_fd, int new_fd);

//execution/exec_std.c
int		save_std(t_mini *shell, t_cmd *cmd);
int		reset_std(t_mini *shell, t_cmd *cmd);

//execution/exec_utils.c
void	free_pids(pid_t *pids);
bool	is_dir(char *path);
void	check_access(t_mini *shell, t_cmd *cmds, char *cmd);
int		wait_for_children(t_mini *shell);

//execution/exec_path.c
char	**get_env_path(char **env);
char	*get_full_path(char **env_path, char *cmd);
char	*get_cmd_path(t_mini *shell, t_cmd *cmds, char *cmd);

//execution/pipes.c
void	close_unused_fds(t_mini *shell, int i);
void	close_fds_and_pipes(t_mini *shell, int i);
int		fork_and_execute(t_mini *shell, t_cmd *cmd);
int		init_pipeline(t_mini *shell);

//redirect/file_handler.c
int		open_infile(t_mini *shell, char *infile);
int		open_outfile(t_mini *shell, char *outfile);
int		open_append_file(t_mini *shell, char *outfile);
int		handle_heredoc(t_mini *shell, char *delimiter);

//redirect/redirect.c
int		redirect_fd(int src_fd, int dest_fd);
int		process_redir(t_mini *shell, t_cmd *cmd);
int		resolve_input_fd(t_mini *shell, t_cmd *cmd, t_token *token);
int		resolve_output_fd(t_mini *shell, t_cmd *cmd, t_token *token);

//setup/setup.c
int		setup(t_mini *shell, char **env);

//signals/signal_handlers.c
void	signal_handler_heredoc(int signal);
void	signal_handler_sigint(int signal);
void	signal_handler_child(int signal);

//signals/signals.c
void	signal_heredoc(void);
void	signal_child(void);
void	signal_reset(void);
void	signal_init(void);

//utils/cleanup.c
void	cleanup_failure(t_mini *shell, t_cmd *cmd, int ex);
void	cleanup_success(t_mini *shell);
void	cleanup(t_mini *shell, t_cmd *cmd);

//utils/cleanup_utils.c
void	free_null(char **ptr);
void	close_all_pipes(t_mini *shell);
void	free_pipes(t_mini *shell, int i);
void	clean_commands(t_cmd *cmd);

//utils/prompt.c
void	get_prompt(t_mini *shell, char *prompt, size_t size);

#endif