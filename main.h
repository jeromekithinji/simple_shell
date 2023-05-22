#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int add_numbers(int a, int b);
char *get_command_path(char *command);
int execute_command(char *command);

#endif 
