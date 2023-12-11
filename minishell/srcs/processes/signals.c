#include "../../includes/minishell.h"

static void process(int sig_number)
{
    if(!kill(glob_pid(0, 'c'), sig_number))
    {
        if (sig_number == SIGQUIT)
        {
            ft_putstr_fd("Quit 3\n", 1);
            glob_status(131, 'w');
        }
        else if (sig_number == SIGINT)
        {
            ft_putstr_fd("\n", 1);
            glob_status(130, 'w');
        }
    }
    else if (sig_number == SIGINT)
    {
        ft_putstr_fd("\n", 1);
        glob_status(1, 'w');
        prompt();
    }
}

void    signal_handler(int sig_number)
{
    if ((sig_number == SIGQUIT || sig_number == SIGINT) && glob_pid(0, 'c') != 0)
        process(sig_number);
    else
        if (sig_number == SIGINT)
        {
            ft_putstr_fd("\n", 1);
            prompt();
        }
        else if (sig_number == SIGQUIT)
        {
            ft_putstr_fd("\b\b \b\b", 1);
        }
}