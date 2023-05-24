#define BUFFER_SIZE 1024

/**
 * get_command - Read a command from input
 *
 * @command: Buffer to store the command
 * Return: Number of characters read, or -1 on failure
 */

ssize_t get_command(char *command)
{
	 ssize_t bytes_read;

	bytes_read = read(STDIN_FILENO, command, BUFFER_SIZE);
	if (bytes_read == -1)
		perror("read");

	return (bytes_read);
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

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}

	if (pid == 0)
	{
		char *argv[] = {command, NULL};

		if (execve(command, argv, NULL) == -1)
		{
			perror("execve");
			_exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
	return (0);
}
