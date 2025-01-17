#include "minishell.h"

static void	set_prompt_dir(t_mini *shell, char *prompt, size_t size)
{
	char	*home;
	size_t	len;

	home = env_get_variable(shell->env, "HOME");
	if (home && ft_strncmp(shell->cwd, home, ft_strlen(home)) == 0)
	{
		len = ft_strlen(home);
		if (shell->cwd[len] == '\0' || shell->cwd[len] == '/')
		{
			ft_strlcat(prompt, "~", size);
			ft_strlcat(prompt, shell->cwd + ft_strlen(home), size);
			return ;
		}
	}
	ft_strlcat(prompt, shell->cwd, size);
}

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
	set_prompt_dir(shell, prompt, size);
	ft_strlcat(prompt, "$ ", size);
	ft_strlcat(prompt, RESET, size);
}
