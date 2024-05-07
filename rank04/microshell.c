#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void		launch_cmd(char ***cmds, int i, char **env, int *fd);

void		ft_fatal_error(void)
{
	write(2, "error: fatal\n", 13);
	exit(EXIT_FAILURE);
}

int			ft_strlen(char *s)
{
	int		len = 0;

	while (s[len])
		len++;
	return (len);
}

int			ft_strlen2(char **s)
{
	int		len = 0;

	while(s[len])
		len++;
	return (len);
}

void		ft_cd(char **cmd)
{
	if (ft_strlen2(cmd) != 2)
		write(2, "error: cd: bad arguments\n", 25);
	else
	{
		if (chdir(cmd[1]) == -1)
		{
			write(2, "error: cd: cannot change directory to ", 38);
			write(2, cmd[1], ft_strlen(cmd[1]));
			write(2, "\n", 1);
		}
	}
}

void		ft_exec(char **cmd, char **env)
{
	pid_t	pid;

	if ((pid = fork()) == -1)
		ft_fatal_error();
	if (!pid)
	{
		if (execve(cmd[0], cmd, env) == -1)
		{
			write(2, "error: cannot execute ", 22);
			write(2, cmd[0], ft_strlen(cmd[0]));
			write(2, "\n", 1);
		}
		exit(EXIT_SUCCESS);
	}
	if (waitpid(pid, 0, 0) == -1)
		ft_fatal_error();
}

void		ft_pipe(char ***cmd, int i, char **env, int *fd)
{
	pid_t	pid;

	if (pipe(fd) == -1)
		ft_fatal_error();
	if ((pid = fork()) == -1)
		ft_fatal_error();
	if (!pid)
	{
		if (close(fd[0]) == -1)
			ft_fatal_error();
		if (dup2(fd[1], 1) == -1)
			ft_fatal_error();
		ft_exec(cmd[i], env);
		if (dup2(1, fd[1]) == -1)
			ft_fatal_error();
		if (close(fd[1]) == -1)
			ft_fatal_error();
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (waitpid(pid, 0, 0) == -1)
			ft_fatal_error();
		if (close(fd[1]) == -1)
			ft_fatal_error();
		if (dup2(fd[0], 0) == -1)
			ft_fatal_error();
		launch_cmd(cmd, i + 2, env, fd);
		if (dup2(0, fd[0]) == -1)
			ft_fatal_error();
	}
}

void		launch_cmd(char ***cmd, int i, char **env, int *fd)
{
	if (cmd[i + 1] != 0 && strcmp(cmd[i + 1][0], "|") == 0)
	{
		close(fd[0]);
		ft_pipe(cmd, i, env, fd);
	}
	else if (strcmp(cmd[i][0], "cd") == 0)
		ft_cd(cmd[i]);
	else
		ft_exec(cmd[i], env);
}

void		launch_cmds(char ***cmd, char **env)
{
	int		i = 0;
	int		fd[2];

	while (cmd[i])
	{
		if (strcmp(cmd[i][0], "|") == 0)
		{
			while (cmd[i] && strcmp(cmd[i][0], "|") == 0)
				i += 2;
			if (!cmd[i])
				break;
		}
		launch_cmd(cmd, i, env, fd);
		i++;
	}
}

void		parsing(int argc, char **argv, char ***cmd)
{
	int		i = 1;
	int		l = 0;
	int		m = 0;

	if ((cmd[0] = malloc(sizeof(char *) * argc + 1)) == 0)
		ft_fatal_error();
	while (i < argc)
	{
		if (i == argc - 1 && (strcmp(argv[i], "|") == 0 || strcmp(argv[i], ";") == 0))
			break;
		else if (m == 0 && (strcmp(argv[i], "|") == 0 || strcmp(argv[i], ";") == 0))
			(void)0;
		else if (strcmp(argv[i], ";") == 0)
		{
			cmd[l][m] = 0;
			l++;
			m = 0;
			if ((cmd[l] = malloc(sizeof(char *) * argc + 1)) == 0)
				ft_fatal_error();
		}
		else if (strcmp(argv[i], "|") == 0)
		{
			cmd[l][m] = 0;
			l++;
			if ((cmd[l] = malloc(sizeof(char *) * argc + 1)) == 0)
				ft_fatal_error();
			cmd[l][0] = argv[i];
			cmd[l][1] = 0;
			l++;
			m = 0;
			if ((cmd[l] = malloc(sizeof(char *) * argc + 1)) == 0)
				ft_fatal_error();
		}
		else
		{
			cmd[l][m] = argv[i];
			m++;
		}
		i++;
	}
	if (m == 0)
		cmd[l] = 0;
	else
	{
		cmd[l][m] = 0;
		cmd[l + 1] = 0;
	}
}

int			main(int argc, char **argv, char **envp)
{
	char	***cmd;

	if (argc == 1)
		return (0);
	if ((cmd = malloc(sizeof(char *) * argc + 1)) == 0)
		ft_fatal_error();
	parsing(argc, argv, cmd);
	launch_cmds(cmd, envp);
	exit(EXIT_SUCCESS);
}
