#include "minishell.h"

static void	add_command(t_cmd **head, t_cmd *new_cmd, t_mini *shell)
{
	t_cmd	*temp;

	temp = NULL;
	if (!*head)
		*head = new_cmd;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_cmd;
	}
	shell->cmd_count++;
}

t_cmd	*tokenizer(t_mini *shell, char *input)
{
	char	**cmd_array;
	t_cmd	*cmd;
	t_cmd	*current_cmd;
	int		i;

	i = 0;
	cmd = NULL;
	cmd_array = split_by_pipes(input);
	free(input);
	if (!cmd_array)
		return (NULL);
	while (cmd_array[i] != NULL)
	{
		current_cmd = create_command(cmd_array[i], i);
		if (!current_cmd)
		{
			ft_free_array(&cmd_array);
			clean_commands(cmd);
			return (NULL);
		}
		add_command(&cmd, current_cmd, shell);
		i++;
	}
	ft_free_array(&cmd_array);
	return (cmd);
}
