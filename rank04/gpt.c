#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

char **g_envp;

// Error handler
void fatal_error(void)
{
    write(2, "error: fatal\n", strlen("error: fatal\n"));
    exit(1);
}

// cd command
void cd(char **args)
{
    if (!args[1] || args[2])
    {
        write(2, "error: cd: bad arguments\n", strlen("error: cd: bad arguments\n"));
        return;
    }
    if (chdir(args[1]) == -1)
    {
        write(2, "error: cd: cannot change directory to ", strlen("error: cd: cannot change directory to "));
        write(2, args[1], strlen(args[1]));
        write(2, "\n", 1);
    }
}

// Execute command
void exec_cmd(char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        if(execve(args[0], args, g_envp) == -1)
        {
            write(2, "error: cannot execute ", strlen("error: cannot execute "));
            write(2, args[0], strlen(args[0]));
            write(2, "\n", 1);
        }
    }
    else if (pid < 0)
        fatal_error();
    else
        waitpid(pid, &status, 0);
}

// Parse command
char **parse_cmd(char *cmd)
{
    char **args;
    int i;

    args = malloc(sizeof(char *) * 4);
    if (!args)
        fatal_error();
    i = 0;
    while ((args[i] = strsep(&cmd, " ")))
    {
        i++;
        if (i > 2)
            break;
    }
    args[i] = NULL;
    return args;
}

// Main function
int main(int argc, char **argv, char **envp)
{
    int i;
    char **args;

    g_envp = envp;
    i = 1;
    while (i < argc)
    {
        args = parse_cmd(argv[i]);
        if (strcmp("cd", args[0]) == 0)
            cd(args);
        else
            exec_cmd(args);
        free(args);
        i++;
    }
    return 0;
}
