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

//check for '/' character at end of directory, if yes, ex = 126, if not, ex = 1
void	error_cmd(t_mini *shell, char *cmd)
{
	int	exitcode;

	exitcode = errno;
	ft_putstr_fd("minishell: ", 2);
	if (errno == EACCES || errno == ENOENT || errno == EISDIR)
		perror(cmd);
	else
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
	}
	if (exitcode == EACCES || exitcode == EISDIR)
		shell->exit_code = 126;
	else
		shell->exit_code = 127;
	exit(shell->exit_code);
}

void	error_file(t_mini *shell, char *file, char *error_str, int ex)
{
	if (file && file[0] != '\0')
		ft_putstr_fd(file, 2);
	write(2, ": ", 2);
	ft_putendl_fd(error_str, 2);
	shell->exit_code = ex;
}
