#include "minishell.h"

void	get_prompt(t_mini *shell, char *prompt, size_t size)
{
	char	*username;

	ft_bzero(prompt, size);
	username = env_get_variable(shell->env, "USER");
	if (!username)
		username = "unknown";
	ft_strlcat(prompt, PINK, size);
	ft_strlcat(prompt, username, size);
	ft_strlcat(prompt, "@", size);
	ft_strlcat(prompt, "minishell:", size);
	update_pwd(shell);
	ft_strlcat(prompt, "~", size);
	ft_strlcat(prompt, shell->cwd, size);
	ft_strlcat(prompt, "$ ", size);
	ft_strlcat(prompt, RESET, size);
}
