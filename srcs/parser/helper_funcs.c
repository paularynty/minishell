#include "../../includes/minishell.h"

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
        printf("Command:\n");
        t_token *token = current->tokens; // Start with the first token
        int i = 0;

        if (token)
        {
            printf("  Tokens:\n");
            while (token)
            {
                printf("    [%d]: %s (type: %d)\n", i, token->value, token->type);
                token = token->next; // Move to the next token
                i++;
            }
        }
        else
        {
            printf("  Tokens: NULL\n");
        }

        printf("  Input FD: %d\n", current->input_fd);
        printf("  Output FD: %d\n", current->output_fd);

        current = current->next; // Move to the next command
        if (current)
            printf("  ---- Next Command ----\n");
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

	offset = 1; // we already have quotes opened, so we start with 1 instead of 1
	while (input[offset] && input[offset] != quote)
		offset++;
	offset++;
	// if (input[offset] == '\0')
	//	return (-1); 	we will handle open quotes later, it's optional
	return (offset); // check logic for open quotes later
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
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			i += quotes_offset(input, input[i]); // we move index until quotes are closed
		else if (input[i] == '|')
			pipes++;
		i++;
	}
	// if (input[i -1] == '|')
	// 		return (-1) 	we handle open pipe later, it's optional
	return (pipes);
}

/********************************
 * 
 * custom strndup which could be added to libft
 *  The strndup() function is similar to strdup, but copies at most n bytes.  If s is
 *  longer than n, only n bytes are copied, and  a  terminating  null  byte	
 *  ('\0') is added.
 *
 * 
 ******************************/
char	*ft_strndup(const char *src, size_t n)
{
	char	*dup;
	size_t	i;

	i = 0;
	dup = (char *)malloc(sizeof(*src) * (n + 1));
	if (!dup)
		return (NULL);
	while (src[i] && i < n)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
