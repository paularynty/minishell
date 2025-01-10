#include "minishell.h"

// This is the first argument validation check.
// We check whether the prompt is empty/whitespace, contains uneven quotes or other errors we can handle immediately
// without taking into account pipes. Upon occuring, we send correct error message, update add_history and return matching exit code.
// Add exit_code / error message handling later.
int 	valid_input(t_mini *shell, char *input)
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
	if (!shell->input) // if there was a malloc fail
	{
		check_print("\nWE DON'T HAVE AN INPUT\n");
		return (FALSE);
	}
	// printf("after expand_input: |%s|\n", shell->input);
	if (!valid_input(shell, shell->input))
	{
		// free(shell->input);
		return (FALSE);
	}
	shell->input = add_missing_spaces(shell->input);
	// printf("after add missing spaces: |%s|\n", shell->input);
	if (!shell->input) // if there was a malloc fail
	{
		check_print("\nWE DON'T HAVE AN INPUT\n");
		return (FALSE);
	}
	// check_print("expanded and spaced input: %s\n", shell->input);
	return (TRUE);
}
