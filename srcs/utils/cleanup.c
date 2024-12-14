#include "../../includes/minishell.h"

void	cleanup(t_mini *shell)
{
	ft_free_array(&shell->env);
	// ft_free_array(&shell->cmd);
	// free(shell->input);
	// shell->input = NULL;
	free(shell->cwd);
	shell->cwd = NULL;
	shell->heredoc = NULL;
}
