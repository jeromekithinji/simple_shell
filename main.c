#include <stdio.h>
#include "main.h"

/**
  * main - entry point
  *
  * Return: 0 on success
  */

int main(void)
{
	int result = add_numbers(5, 10);
	char command[BUFFER_SIZE];
	ssize_t bytes_read;

	while (1)
	{
		printf("$ ");
		fflush(stdout);
		bytesRead = get_command(command);
		
		if (bytesRead == -1)
			continue;
		if (bytesRead == 0)
		{
			printf("\n");
			break;
		}
		command[bytesRead - 1] = '\0';

		if (execute_command(command) == -1)
			continue;
	}
	printf("The result is: %d\n", result);

	return (0);
}
