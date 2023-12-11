# include "../../includes/minishell.h"

long long ft_exit_atoi(const char *str, int i, int *prob)
{
    int         j;
    long        neg;
    long long   sum;

    neg = 1;
    sum = 0;
    j = 0;
    if (str[i] && (str[i] == '-' || str[i] == '+'))
        if (str[i++] == '-')
            neg *= -1;
    while (str[i] && (ft_isspace(str[i]) || str[i] == '0'))
        i++;
    while (str[i] >= '0' && str[i] <= '9' && ++j)
    {
        sum = (sum * 10) + (str[i] - 48);
        if (((i == 18 && neg == 1) && (str[i] > '7' && str[i] <= '9'))
            || ((i == 19 && neg == -1) && (str[i] == '9')))
            *prob = 1;
        i++;
    }
    while (str[i++])
        j++;
    if ((j > 19 && neg == 1) || (j > 20 && neg == -1))
        *prob = 1;
    return (sum * neg);
}

void		exit_error_numeric(char *arg, t_copy *copy)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	glob_status(2, 'w');
	ft_exit(copy, 1);
}

void		exit_arg(char *arg, t_copy *copy)
{
	int		i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (arg[i] != '\f' && arg[i] != '\t' && arg[i] != '\r'
			&& arg[i] != '\v' && arg[i] != ' ')
		{
			if (arg[i] < 48 || arg[i] > 57)
				exit_error_numeric(arg, copy);
		}
		i++;
	}
}

void		run_exit(char **args, t_copy *copy)
{
	size_t		i;
	int			pbm;
	long long	code2;

	pbm = 0;
	i = 1;
	glob_status(0, 'w');
	if (!args[1])
		ft_exit(copy, 1);
	exit_arg(args[1], copy);
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		glob_status(1, 'w');
	}
	else
	{
		code2 = ft_atoi_exit(args[1], 0, &pbm);
		if (pbm == 1)
			exit_error_numeric(args[1], copy);
		glob_status(code2 % 256, 'w');
	}
	ft_exit(copy, 1);
}