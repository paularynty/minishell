#include "../../includes/minishell.h"

static int	process_input(const char *input, char **cmd, int *j, int *start)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			i += quotes_offset(input + i, input[i]);
		else if (input[i] == '|')
		{
			cmd[*j] = ft_strndup(input + *start, i - *start);
			if (!cmd[*j])
				return (0); // we free in the calling function
			(*j)++;
			*start = i + 1;
		}
		i++;
	}
	return (i);
}

static char	**allocate_cmd_array(const char *input)
{
	int	cmd_count;
	int	pipes;
	char	**cmd;

	pipes = count_pipes(input);
	cmd_count = pipes + 1;
	cmd = (char **)malloc(sizeof(char *)*(cmd_count + 1));
	if (!cmd)
		return (NULL);
	return (cmd);
}

char	**split_by_pipes(const char *input)
{
	char **cmd;
	int	j;
	int	start;
	int	end;

	cmd = allocate_cmd_array(input);
	if (!cmd)
		return (NULL);
	j = 0;
	start = 0;
	end = process_input(input, cmd, &j, &start);
	if (!end || (start < end && !(cmd[j++] = ft_strndup(input + start, end - start))))
	{
		while (j > 0)
			free(cmd[--j]);
		free(cmd);
		return (NULL);
	}
	cmd[j] = NULL;
	return (cmd);
}
