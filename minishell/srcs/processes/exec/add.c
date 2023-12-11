#include "../../../includes/minishell.h"

int			run(char **args, char *bin, int pipe, pid_t pp)
{
	if (!pipe)
		glob_pid(fork(), 'w');
	if (!pipe && glob_pid(0, 'c') < 0)
	{
		free(bin);
		ft_putstr_fd("minishell: execve: failed to create a new process.\n", 2);
		glob_status(1, 'w');
		return (-1);
	}
	else if (!glob_pid(0, 'c'))
		execve(bin, args, g_envs);
	free(bin);
	if (pipe)
		return (1);
	if (ft_strequ(args[0], "./minishell"))
		signal(SIGINT, SIG_IGN);
    pp = glob_pid(0, 'c');
	wait(&pp);
	status_child();
	glob_pid(0, 'w');
	return (1);
}

int			has_perm(char **args, char *bin, struct stat statbuf, int pipe)
{
	if (statbuf.st_mode & S_IFREG)
	{
		if (statbuf.st_mode & S_IXUSR)
			return (run(args, bin, pipe, 0));
		else
		{
			ft_putstr_fd("minishell: execve: permission denied: ", 2);
			ft_putstr_fd(bin, 2);
			ft_putchar_fd('\n', 2);
			glob_status(1, 'w');
		}
		free(bin);
		return (1);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		g_status(1, 'w');
	}
	free(bin);
	return (1);
}

int			check_bins(char **args, int pipe)
{
	struct stat statbuf;
	char		**path;
	char		*bin;
	char		*tmp;
	size_t		i;

	if (!(path = get_path()))
		return (-1);
	i = -1;
	while (path[++i])
	{
		bin = ft_strjoin(path[i], "/");
		tmp = bin;
		bin = ft_strjoin(bin, args[0]);
		free(tmp);
		if (!lstat(bin, &statbuf))
		{
			ft_free_array(path);
			return (has_perm(args, bin, statbuf, pipe));
		}
		free(bin);
	}
	ft_free_array(path);
	return (0);
}

int			check_builtin(char **args, t_copy *copy)
{
	char	*pwd;

	if (ft_strequ(args[0], "echo"))
		return (run_echo(args));
	else if (ft_strequ(args[0], "cd"))
		return (run_cd(args));
	else if (ft_strequ(args[0], "unset"))
		return (run_unset(args));
	else if (ft_strequ(args[0], "export"))
		return (run_export(args));
	else if (ft_strequ(args[0], "exit"))
		run_exit(args, copy);
	else if (ft_strequ(args[0], "pwd"))
	{
		pwd = getcwd(NULL, 0);
		ft_putstr_fd(pwd, 1);
		free(pwd);
		ft_putchar_fd('\n', 1);
		return (1);
	}
	else if (ft_strequ(args[0], "env"))
		return (run_env());
	return (0);
}