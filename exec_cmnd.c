#include "main.h"

/**
 * get_command - Read a command from input
 *
 * @command: Buffer to store the command
 * Return: Number of characters read, or -1 on failure
 */

char *get_command(void)
{
	char *command = NULL;
	size_t bufsize = 0;
	ssize_t bytesRead;

	bytesRead = getline(&command, &bufsize, stdin);
	if (bytesRead == -1)
		perror("getline");
	
	return (command);
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
	int argc = 3; // Number of arguments in argv
	char **argv = NULL;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		free(argv);
		return (-1);
	}

	if (pid == 0)
	{
		argv = malloc((argc + 1) * sizeof(char *));
		if (argv == NULL)
		{
			perror("malloc");
			free(argv);
			_exit(EXIT_FAILURE);
		}

		argv[0] = "/bin/sh";
		argv[1] = "-c";
		argv[2] = command;
		argv[3] = NULL;

		if (execve("/bin/sh", argv, NULL) == -1)
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

/**
 * free_resources - Free allocated resources
 *
 * @command: Command string
 * Return: None
 */

void free_resources(char *command)
{
	free(command);
}
