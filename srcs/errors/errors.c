#include "minishell.h"

//check correct exit codes for builtins
void	error_builtin(char *builtin, char *str, char *error_str)
{
	char	buffer[1024];

	ft_strlcpy(buffer, "minishell: ", sizeof(buffer) - 1);
	ft_strlcat(buffer, builtin, sizeof(buffer) - 1);
	if (str)
	{
		ft_strlcat(buffer, ": ", sizeof(buffer) - 1);
		ft_strlcat(buffer, str, sizeof(buffer) - 1);
	}
	if (!error_str)
		error_str = strerror(errno);
	if (error_str && error_str[0] != '\0')
	{
		ft_strlcat(buffer, ": ", sizeof(buffer) - 1);
		ft_strlcat(buffer, error_str, sizeof(buffer) - 1);
	}
	ft_strlcat(buffer, "\n", sizeof(buffer));
	ft_putstr_fd(buffer, STDERR_FILENO);
}

void	error_cmd(t_mini *shell, t_cmd *head, char *cmd, char *error_str)
{
	char	buffer[1024];

	ft_strlcpy(buffer, "minishell: ", sizeof(buffer) - 1);
	if (cmd)
	{
		ft_strlcat(buffer, cmd, sizeof(buffer) - 1);
		ft_strlcat(buffer, ": ", sizeof(buffer) - 1);
	}
	if (!error_str)
		error_str = strerror(errno);
	if (error_str && error_str[0] != '\0')
		ft_strlcat(buffer, error_str, sizeof(buffer) - 1);
	ft_strlcat(buffer, "\n", sizeof(buffer));
	ft_putstr_fd(buffer, STDERR_FILENO);
	cleanup_failure_child(shell, head, shell->exit_code);
}

void	error_export(char *str)
{
	char	buffer[1024];

	ft_strlcpy(buffer, "minishell: export: `", sizeof(buffer) - 1);
	ft_strlcat(buffer, str, sizeof(buffer) - 1);
	ft_strlcat(buffer, "': not a valid identifier\n", sizeof(buffer) - 1);
	ft_putstr_fd(buffer, STDERR_FILENO);
}

void	error_file(t_mini *shell, char *file, char *error_str, int exit_status)
{
	char	buffer[1024];

	shell->exit_code = exit_status;
	ft_strlcpy(buffer, "minishell: ", sizeof(buffer) - 1);
	if (file && file[0] != '\0')
	{
		ft_strlcat(buffer, file, sizeof(buffer) - 1);
		ft_strlcat(buffer, ": ", sizeof(buffer) - 1);
	}
	if (error_str && error_str[0] != '\0')
		ft_strlcat(buffer, error_str, sizeof(buffer) - 1);
	ft_strlcat(buffer, "\n", sizeof(buffer));
	ft_putstr_fd(buffer, STDERR_FILENO);
}
