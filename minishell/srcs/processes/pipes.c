#include "../../includes/minishell.h"

void		status_child(void)
{
	if (WIFEXITED(glob_pid(0, 'c')))
		glob_status(WEXITSTATUS(glob_pid(0, 'c')), 'w');
	if (WIFSIGNALED(glob_pid(0, 'c')))
	{
		glob_status(WTERMSIG(glob_pid(0, 'c')), 'w');
		if (glob_status(0, 'c') != 131)
			glob_status(128, '+');
	}
}

static void	child(t_pipe *pipcell, int fd[2], int *fdd)
{
	close(fd[0]);
	close(0);
	dup(*fdd);
	close(*fdd);
	if (pipcell->next)
	{
		close(1);
		dup(fd[1]);
		close(fd[1]);
	}
}

int			run_pipe(t_pipe *pipcell, t_copy *cmdargs, int fdd, pid_t pp)
{
	int		fd[2];

	fd[0] = -1;
	fd[1] = -1;
	if (pipe(fd))
		return (-1);
	glob_pid(fork(), 'w');
	if (glob_pid(0, 'c') < 0)
	{
		close(fd[0]);
		close(fd[1]);
		close(fdd);
		return (-1);
	}
	else if (!glob_pid(0, 'c'))
	{
		child(pipcell, fd, &fdd);
		execution(cmdargs, 1);
		ft_exit(cmdargs, 0);
	}
	pp = glob_pid(0, 'c');
	wait(&pp);
	status_child();
	close(fdd);
	close(fd[1]);
	return (fd[0]);
}