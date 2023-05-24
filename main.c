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
	char *command;

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		command = get_command();
		if (command == NULL)
			continue;

		if (strlen(command) == 1 && command[0] == '\n')
		{
			printf("\n");
			free_resources(command);
			break;
		}

		command[strlen(command) - 1] = '\0';

		if (execute_command(command) == -1)
			continue;

		free_resources(command);
	}

	printf("The result is: %d\n", result);

	return (0);
}
