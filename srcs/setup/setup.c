#include "../includes/minishell.h"

//initialize and setup program variables.
//env_clone function to clone the env 
//so if unset is called in a nested minishell instance, it doesn't change/corrupt the original env variables
//create env pending list, this can be a 2D array;
int	setup(t_mini *shell, char **env)
{
	shell->cmd = NULL;
	shell->cwd = NULL;
	shell->input = NULL;
	shell->heredoc = NULL;
	shell->exit_flag = FALSE;
	shell->exit_code = 0;
	shell->env = clone_env(env);
	if (!env_update_shlvl(shell))
		return (FALSE);
	return (TRUE);
}
