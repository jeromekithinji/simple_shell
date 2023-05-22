#include "main.h"

/**
 * get_line - Read input from the user
 *
 * Return: A pointer to the input line, or NULL on failure or EOF
 */

char *get_line(void)
{
	static char buffer[BUFFER_SIZE];
	static ssize_t bytes_read;
	char *line = NULL;
	size_t line_size = 0;
	ssize_t i;

	while (1)
	{
		if (bytes_read == 0)
		{
			bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);

			if (bytes_read == -1 || bytes_read == 0)
				return (NULL);
		}

		for (i = 0; i < bytes_read; i++)
		{
			if (buffer[i] == '\n')
			{
				i++;
				bytes_read -= i;
				memmove(buffer, buffer + i, bytes_read);
				line = realloc(line, line_size + i);

				if (line == NULL)
				{
					perror("Malloc failed");
					return (NULL);
				}

				memcpy(line + line_size, buffer, i);
				line_size += i;
				line[line_size] = '\0';

				return (line);
			}
		}

		line = realloc(line, line_size + bytes_read);
		if (line == NULL)
		{
			perror("Malloc failed");
			return (NULL);
		}

		memcpy(line + line_size, buffer, bytes_read);
		line_size += bytes_read;
		bytes_read = 0;
	}
}
