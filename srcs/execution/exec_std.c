#include "minishell.h"

int	save_std(t_mini *shell)
{
	shell->std[0] = dup(STDIN_FILENO);
	shell->std[0] = dup(STDOUT_FILENO);
	if (shell->std[0] == -1 || shell->std[1] == -1)
	{
		shell->abort = 1;
		return (FALSE);
	}
	return (TRUE);
}

int	reset_std(t_mini *shell)
{
	if (dup2(shell->std[0], 0) < 0 || dup2(shell->std[1], 1) < 0)
	{
		shell->abort = 1;
		return (FALSE);
	}
	close(shell->std[0]);
	close(shell->std[1]);
	shell->std[0] = -1;
	shell->std[1] = -1;
	return (TRUE);
}
