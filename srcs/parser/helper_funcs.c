#include "minishell.h"

/********************************
 * 
 * This function is only used to print out the contents of the cmd_lists so we can see whether
 * data is stored as it should.
 * 
 ******************************/
#include <stdio.h>

void	print_2d_arr(char **arr)
{
	int	i;
	
	i = 0;
	if (!arr || !arr[i])
		return ;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

void print_list(t_command *commands)
{
    t_command *current = commands;

    while (current)
    {
        printf("Command:\n");
        if (current->tokens)
        {
            printf("  Tokens:\n");
            t_token *token = current->tokens;
            int i = 0;
            while (token)
            {
                if (token->value) // Check value before accessing
                    printf("    [%d]: %s (type: %d)\n", i, token->value, token->type);
                else
                    printf("    [%d]: (NULL token value)\n", i);
                token = token->next;
                i++;
            }
        }
        else
        {
            printf("  Tokens: NULL\n");
        }

        printf("  Input FD: %d\n", current->input_fd);
        printf("  Output FD: %d\n", current->output_fd);

        if (current->next)
            printf("  ---- Next Command ----\n");
        current = current->next;
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

int	char_is_whitespace(char c)
{
	if (c != 32 && (c < 9 || c > 13))
		return (FALSE);
	return (TRUE);
}
