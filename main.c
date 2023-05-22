#include <stdio.h>
#include "main.h"

/**
  * main - entry point.
  *
  * Return: 0 on success.
  */

int main()
{
	int result = add_numbers(5, 10);
	char command[1024];

	while (1)
	{
		printf("$ ");
		fgets(command, sizeof(command), stdin);
		command[strcspn(command, "\n")] = '\0';

		if (strcmp(command, "exit") == 0)
			exit(0);
			break;

		execute_command(command);
	}
	printf("The result is: %d\n", result);

	return (0);
}
