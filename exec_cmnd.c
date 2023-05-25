#include "main.h"

/**
 * get_command - Read a command from input
 *
 * @command: Buffer to store the command
 * Return: Number of characters read, or -1 on failure
 */

int get_command(char *command)
{
	int bytesRead;

	bytesRead = read(STDIN_FILENO, command, BUFFER_SIZE);
	if (bytesRead == -1)
		perror("read");

	return (bytesRead);
}

/**
 * execute_command - Execute a command given
 *
 * @command: Command to execute
 * Return: 0 on success, -1 on failure
 */

int execute_command(char *command)
{
	pid_t pid;
	int status;
	char **argv = NULL;

	if (strcmp(command, "exit") == 0)
		exit(0);

	if (strcmp(command, "env") == 0)
	{
		char **env = environ;
		
		while (*env)
		{
			printf("%s\n", *env);
			env++;
		}
		return (0);
	}

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}

	if (pid == 0)
	{
		argv = malloc(3 * sizeof(char *));

		if (argv == NULL)
		{
			perror("malloc");
			_exit(EXIT_FAILURE);
		}

		argv[0] = "/bin/sh";
		argv[1] = "-c";
		argv[2] = command;
		argv[3] = NULL;

		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("execve");
			free(argv);
			_exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}

	free(argv);
	return (0);
}
