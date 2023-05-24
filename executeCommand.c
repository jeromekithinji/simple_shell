#include "main.h"

/**
 * *get_command_path - Get path to command if existing
 *
 * @command: Command to find in the PATH
 * Return: Path to the command or NULL if not found
 */

char *get_path_command(char *command)
{
	char *path_env, *token, *path_command;
	char *delimiters = ":";

	path_env = getenv("PATH");
	if (path_env == NULL)
		return (NULL);

	token = strtok(path_env, delimiters);
	while (token != NULL)
	{
		path_command = malloc(strlen(token) + strlen(command) + 2);
		if (path_command == NULL)
		{
			perror("Malloc failed");
			return (NULL);
		}

		sprintf(path_command, "%s/%s", token, command);
		if (access(path_command, F_OK) == 0)
			return (path_command);

		free(path_command);
		token = strtok(NULL, delimiters);
	}
	return (NULL);
}

/**
 * exit_shell - Exit the shell window
 */

void exit_shell(void)
{
	_exit(0);
}

/**
 * print_env - Print the current working environment
 */

void print_env(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}

/**
 * execute_command - Execute a command
 *
 * @command: Command to execute
 * Return: 0 on success or -1 on failure
 */

void execute_command(char *command)
{
	char *path_command;
	pid_t pid;
	int status;

	if (strcmp(command, "exit") == 0)
	{
		exit_shell();
		return;
	}
	else if (strcmp(command, "env") == 0)
	{
		print_env();
		return;
	}

	path_command = get_path_command(command);
	if (path_command == NULL)
	{
		write(STDERR_FILENO, "Command not found\n", 18);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		free(path_command);
		return;
	}

	if (pid == 0)
	{
		if (execve(path_command, &command, NULL) == -1)
		{
			perror("Exec failed");
			free(path_command);
			_exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
	free(path_command);
}
