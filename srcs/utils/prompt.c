#include "minishell.h"

// static void	set_prompt_dir(t_mini *shell, char *prompt, size_t size)
// {
// 	char	*pwd;
// 	// size_t	home_len;

// 	pwd = env_get_variable(shell->env, "PWD");
// 	// if (home_dir && ft_strncmp(shell->cwd, home_dir, ft_strlen(home_dir)) == 0)
// 	// {
// 	// 	home_len = ft_strlen(home_dir);
// 	// 	if (shell->cwd[home_len] == '\0' || shell->cwd[home_len] == '/')
// 	// 	{
// 	// 		ft_strlcat(prompt, "~", size);
// 	// 		ft_strlcat(prompt, shell->cwd + ft_strlen(home_dir), size);
// 	// 		return ;
// 	// 	}
// 	// }
// 	ft_strlcat(prompt, pwd, size);
// }

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
	ft_strlcat(prompt, "~", size);
	update_pwd(shell);
	// set_prompt_dir(shell, prompt, size);
	ft_strlcat(prompt, shell->cwd, size);
	ft_strlcat(prompt, "$ ", size);
	ft_strlcat(prompt, RESET, size);
}
