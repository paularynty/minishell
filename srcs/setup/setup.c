#include "minishell.h"

//initialize and setup program variables.
//env_clone function to clone the env 
//so if unset is called in a nested minishell instance,
//it doesn't change/corrupt the original env variables
//create env pending list, this can be a 2D array;
int	setup(t_mini *shell, char **env)
{
	if (env == NULL)
		shell->env = NULL;
	else
	{
		shell->env = clone_env(env);
		if (!shell->env)
			return (FALSE);
	}
	sig_init(&sig_handler_sigint);
	shell->cwd = NULL;
	shell->cmd_count = 0;
	shell->input = NULL;
	shell->pipes = NULL;
	shell->pids = NULL;
	shell->exit_code = 0;
	if (!env_update_shlvl(shell))
		return (FALSE);
	if (!env_set_cwd(shell))
		return (FALSE);
	return (TRUE);
}
