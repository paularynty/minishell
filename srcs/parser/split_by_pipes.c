#include "minishell.h"

static int	process_input(const char *input, char **cmd, int *j, int *start)
{
	int	i;

	i = 0;
	while (input && input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			i += quotes_offset(input + i, input[i]);
		else if (input[i] == '|')
		{
			if (*start >= i)
				return (0);
			cmd[*j] = ft_strndup(input + *start, i - *start);
			if (!cmd[*j])
				return (0);
			(*j)++;
			*start = i + 1;
			i++;
		}
		else
			i++;
	}
	return (i);
}

static char	**allocate_cmd_array(int pipes)
{
	int	cmd_count;
	char	**cmd;

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
	int	pipes;

	pipes = count_pipes(input);
	cmd = allocate_cmd_array(pipes);
	if (!cmd)
		return (NULL);
	j = 0;
	start = 0;
	end = process_input(input, cmd, &j, &start);
	if (start < end)
	{
		cmd[j] = ft_strndup(input + start, end - start);
		if (!cmd[j])
		{
			free_2d_array(cmd);
			return (NULL);
		}
		j++;
	}
	cmd[j] = NULL;
	return (cmd);
}
