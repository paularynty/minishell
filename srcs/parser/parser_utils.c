#include "minishell.h"

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

int	count_token_type(t_token *tokens, enum e_token_type type)
{
	int	count;

	count = 0;
    while (tokens)
	{
        if (tokens->type == type)
            count++;
        tokens = tokens->next;
    }
    return (count);
}

/********************************
 * 
 * This function is only used to print out the contents of the cmd_lists so we can see whether
 * data is stored as it should.
 * 
 ******************************/
void print_list(t_cmd *cmds)
{
    t_cmd 	*curr;
	t_token	*token;
	int		i;

	curr = cmds;
    while (curr)
    {
        check_print("Command:\n");
        token = curr->tokens; // Start with the first token
        i = 0;
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
        check_print("  Input FD: %d\n", curr->input_fd);
        check_print("  Output FD: %d\n", curr->output_fd);
        curr = curr->next; // Move to the next cmd
        if (curr)
            check_print("  ---- Next Command ----\n");
    }
}

/********************************
 * 
 * The insides of the quotes are their own argument, so we count how long this
 * argument is (including quotes). 
 * We already have quotes opened, so offset is first initialized to 1.
 * 
 ******************************/
int	quotes_offset(const char *input, char quote)
{
	int	offset;

	offset = 1; // 
	while (input[offset] && input[offset] != quote)
		offset++;
	offset++;
	return (offset);
}

/********************************
 * 
 * we count how many pipes occur. index is moved until quotes are closed.
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
		if (input[i] == '\'' || input[i] == '"')
			i += quotes_offset(input + i, input[i]);
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
