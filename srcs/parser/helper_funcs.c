#include "minishell.h"

/********************************
 * 
 * This function is only used to print out the contents of the cmd_lists so we can see whether
 * data is stored as it should.
 * 
 ******************************/
#include <stdio.h>

void print_list(t_command *commands)
{
    t_command *current = commands;

    while (current)
    {
        check_print("Command:\n");
        t_token *token = current->tokens; // Start with the first token
        int i = 0;
        if (token)
        {
            check_print("  Tokens:\n");
            while (token)
            {
                check_print("    [%d]: %s (type: %d)\n", i, token->value, token->type);
                token = token->next; // Move to the next token
                i++;
            }
        }
        else
        {
			check_print("  Tokens: NULL\n");
        }
        check_print("  Input FD: %d\n", current->input_fd);
        check_print("  Output FD: %d\n", current->output_fd);
        current = current->next; // Move to the next command
        if (current)
            check_print("  ---- Next Command ----\n");
    }
}

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

/********************************
 * 
 * The insides of the quotes are their own argument, so we count how long this
 * argument is (including quotes)
 * 
 ******************************/
int	quotes_offset(const char *input, char quote)
{
	int	offset;

	offset = 1; // we already have quotes opened, so we start with 1 instead of 0
	while (input[offset] && input[offset] != quote)
		offset++;
	offset++;
	return (offset);
}

/********************************
 * 
 * we count how many pipes occur
 * 
 ******************************/
int	count_pipes(const char *input)
{
	int	pipes;
	int	i;

	pipes = 0;
	i = 0;
	while (input && input[i])
	{
		// printf("Inspecting input %s in letter %c\n", input, input[i]);
		if (input[i] == '\'' || input[i] == '"')
			i += quotes_offset(input + i, input[i]); // we move index until quotes are closed
		else if (input[i] == '|')
		{
			pipes++;
			i++;
		}
		else
			i++;
	}
	return (pipes);
}

int	char_is_whitespace(char c)
{
	if (c != 32 && (c < 9 || c > 13))
		return (FALSE);
	return (TRUE);
}
