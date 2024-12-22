#include "minishell.h"
// static void	free_tokens(t_token *tokens) 
// {
// 	t_token *temp;
	
// 	while (tokens)
// 	{
// 		temp = tokens;
// 		tokens = tokens->next;
// 		free(temp->value);
// 		free(temp);
// 		temp = NULL;
//     }
// }

// static void	clean_commands(t_command *command) 
// {
// 	t_command	*temp;
	
// 	while (command)
// 	{
// 		free_tokens(command->tokens);
// 		command->tokens = NULL;
// 		command->next = NULL;
// 		temp = command;
// 		command = command->next;
// 		free(temp);
// 		temp = NULL;
//     }
// }

void	cleanup_success(t_mini *shell)
{
	free(shell->pids);
	shell->pids = NULL;
	exit(EXIT_SUCCESS);
}

void	cleanup(t_mini *shell)
{
	ft_free_array(&shell->env);
	// ft_free_array(&shell->command);
	// free(shell->input);
	// shell->input = NULL;
	free(shell->cwd);
	shell->cwd = NULL;
	shell->heredoc = NULL;
	// clean_commands(command);
}
