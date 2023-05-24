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

#include "main.h"

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

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return -1;
	}

	if (pid == 0)
	{
		char *argv[] = {"/bin/sh", "-c", command, NULL};

		if (execve("/bin/sh", argv, NULL) == -1)
		{
			perror("execve");
			_exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}

	return 0;
}
