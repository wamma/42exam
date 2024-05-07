#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int err(char *str, char *arg)
{
	while (*str)
		write(2, str++, 1);
	if (arg != NULL)
		while (*arg)
			write(2, arg++, 1);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void cd(char **argv, int i) 
{
	if (i != 2)
		return err("error: cd: bad arguments", NULL);
	else if (chdir(argv[1]) == -1)
		return err("error: cd: cannot change directory to ", argv[1]);
}

void exec(char **argv, char **envp, int i) 
{
	int fd[2];
	int status;
	int has_pipe = argv[i] && !strcmp(argv[i], "|");

	if (has_pipe && pipe(fd) == -1)
		return err("error: fatal", NULL);

	int pid = fork();
	if (!pid)
	{
		argv[i] = 0;
		if (has_pipe && (dup2(fd[1], 1) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
			return err("error: fatal", NULL);
		execve(*argv, argv, envp);
		return err("error: cannot execute ", *argv);
	}

	waitpid(pid, &status, 0);
	if (has_pipe && (dup2(fd[0], 0) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
		return err("error: fatal", NULL);
	if (!WIFEXITED(status) || WEXITSTATUS(status))
		err("error: fatal", NULL);
}

int main(int argc, char **argv, char **envp) 
{
	int	i = 0;
	int	status = 0;

	if (argc > 1)
	{
		while (argv[i] && argv[++i]) 
		{
			argv += i;
			i = 0;
			while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
				i++;
			if (!strcmp(*argv, "cd"))
				status = cd(argv, i);
			else if (i)
				status = exec(argv, envp, i);
		}
	}
	return status;
}
