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

	free(command);
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
	char *path;
	int argc = 4;
	char **argv = NULL;
	
	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return -1;
	}

	if (pid == 0)
	{
		path = getenv("PATH");
		char *token;
		char cmd_path[BUFFER_SIZE];
		int found = 0;
		
		argv = malloc((argc + 1) * sizeof(char *));
		if (argv == NULL)
		{
			perror("malloc");
			_exit(EXIT_FAILURE);
		}

		argv[0] = command;
		argv[1] = NULL;
		
		if (strchr(command, '/') == NULL)
		{
			token = strtok(path, ":");
			while (token != NULL)
			{
				snprintf(cmd_path, sizeof(cmd_path), "%s/%s", token, command);
				if (access(cmd_path, X_OK) == 0)
				{
					argv[0] = cmd_path;
					found = 1;
					break;
				}
				token = strtok(NULL, ":");
			}
		}
		else
		{
			if (access(command, X_OK) == 0)
				found = 1;
		}
		
		if (!found)
		{
			fprintf(stderr, "%s: command not found\n", command);
			free(argv);
			_exit(EXIT_FAILURE);
		}

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
	return 0;
}
