#include "minishell.h"

/**
 * Validates the initial user input before parsing.
 *
 * @shell: Pointer to the shell structure.
 * @input: The expanded input string (shell->input).
 *
 * - Checks if the input consists only of whitespace.
 * - Validates that all quotes in the input are properly matched.
 * - Ensures there are no improper backslashes in the input.
 * - Verifies the correctness of input redirection syntax.
 * - Confirms that all pipes are closed and valid.
 * 
 * Returns TRUE if the input is valid, FALSE if any validation fails.
 * */
int	valid_input(t_mini *shell, char *input)
{
	if (str_is_whitespace(input))
		return (FALSE);
	if (!matching_quotes(shell, input))
		return (FALSE);
	if (backslash(shell, input))
		return (FALSE);
	if (!valid_redirection(shell, input))
		return (FALSE);
	if (!closed_pipes(shell, input))
		return (FALSE);
	if (!valid_pipes(shell, input))
		return (FALSE);
	return (TRUE);
}

int	lexer(t_mini *shell, char *line)
{
	shell->input = expand_input(shell, line);
	if (!shell->input)
	{
		ft_putstr_fd("malloc\n", STDERR_FILENO);
		shell->abort = 1;
		return (FALSE);
	}
	if (!valid_input(shell, shell->input))
		return (FALSE);
	shell->input = add_missing_spaces(shell->input);
	if (!shell->input)
	{
		ft_putstr_fd("malloc\n", STDERR_FILENO);
		shell->abort = 1;
		return (FALSE);
	}
	return (TRUE);
}
