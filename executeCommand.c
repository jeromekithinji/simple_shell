#include "main.h"

/**
 * get_command_path - Get path to command if existing
 *
 * @command: Command to find in the PATH
 * Return: Path to the command or NULL if not found
 */

char *get_command_path(char *command)
{
	char *path_env, *token, *command_path;
	char *delimiters = ":";

	path_env = getenv("PATH");
	if (path_env == NULL)
		return (NULL);

	token = strtok(path_env, delimiters);
	while (token != NULL)
	{
		command_path = malloc(strlen(token) + strlen(command) + 2);
		if (command_path == NULL)
		{
			perror("Malloc failed");
			return (NULL);
		}

		sprintf(command_path, "%s/%s", token, command);
		if (access(command_path, F_OK) == 0)
			return (command_path);

		free(command_path);
		token = strtok(NULL, delimiters);
	}
	return (NULL);
}

/**
 * execute_command - Execute a command
 *
 * @command: Command to execute
 * Return: 0 on success or -1 on failure
 */

int execute_command(char *command)
{
	char *command_path;
	pid_t pid;
	int status;

	command_path = get_command_path(command);
	if (command_path == NULL)
	{
		write(STDERR_FILENO, "Command not found\n", 18);
		return (-1);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		free(command_path);
		return (-1);
	}

	if (pid == 0)
	{
		if (execve(command_path, &command, NULL) == -1)
		{
			perror("Exec failed");
			free(command_path);
			_exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}

	free(command_path);
	return (0);
}
