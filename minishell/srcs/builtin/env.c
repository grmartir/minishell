#include "../../includes/minishell.h"

int	run_env(void)
{
	size_t	i;

	i = 0;
	glob_status(0, 'w');
	while (g_envs[i])
	{
		if (ft_strchr(g_envs[i], '='))
		{
			ft_putstr_fd(g_envs[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	return (1);
}