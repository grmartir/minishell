int glob_status(int status, char check)
{
    static int x;
    int y;

    y = 0;
    if(check == 'w'){
        x = status;
        return (x);
    }
    else if(check == 'c'){
        return(x);
    }
    else if (check == '+'){
        return (x + status);
    }
    else if(check == 'e'){
        y = x;
        free(x);
        return(y);
    }
}

int glob_error(int status, char check)
{
    static int x;
    int y;

    y = 0;
    if(check == 'w'){
        x = status;
        return (x);
    }
    else if(check == 'c'){
        return(x);
    }
    else if(check == 'e'){
        y = x;
        free(x);
        return(y);
    }
}

int glob_test(int status, char check)
{
    static int x;
    int y;

    y = 0;
    if(check == 'w'){
        x = status;
        return (x);
    }
    else if(check == 'c'){
        return(x);
    }
    else if(check == 'e'){
        y = x;
        free(x);
        return(y);
    }
}

int glob_pid(int status, char check)
{
    static int x;
    int y;

    y = 0;
    if(check == 'w'){
        x = status;
        return (x);
    }
    else if(check == 'c'){
        return(x);
    }
    else if(check == 'e'){
        y = x;
        free(x);
        return(y);
    }
}

// char **glob_enviroment(char **env)
// {
//     static char **envs;

//     envs = env;
//     return (**envs);
// }