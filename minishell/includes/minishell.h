#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
# include "../libft/libft.h"

char **g_envs;

typedef struct s_sep
{
    char    *cmd_sep;
    struct s_sep    *next;
    struct s_sep    *prev;
    struct s_pipe   *pipecall;
}               t_sep;

typedef struct s_pipe
{
    char    *cmd_pipe;
    struct s_pipe *next;
    struct s_pipe *prev;
}              t_pipe;

typedef	struct			s_redir
{
	char				*out1;
	char				*out2;
	char				*in;
	int					sstdout;
	int					sstderr;
	int					sstdin;
	int					end;
	int					i;
	char				*name;
	char				*value;
}						t_redir;

typedef struct			s_copy
{
	t_sep				*list;
	char				**cmdssep;
	char				*wc;
	char				**args;
	char				*cmd;
	int					i;
	int					j;
	t_redir				redir;
	char				**tmp;
	char				*arg;
}						t_copy;

int glob_status(int status, char check);
int glob_error(int status, char check);
int glob_pid(int status, char check);
int glob_test(int status, char check);

#endif