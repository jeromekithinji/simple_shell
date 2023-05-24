#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int add_numbers(int a, int b);
char *get_path_command(char *command);
void exit_shell();
void print_env();
void execute_command(char *command);
char *get_line(void);

#endif 
