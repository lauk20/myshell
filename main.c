#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

#include "parser.h"
#include "executor.h"

#define COMMAND_BUFFER 256
#define COLOR_RED "\x1B[31m"
#define COLOR_WHITE "\x1B[37m"

int main() {
  int error = 0;

  while (!error) {
    //CURRENT WORKING DIRECTORY
    char current_working_directory[PATH_MAX + 1];
    getcwd(current_working_directory, sizeof(current_working_directory));
    printf("%s%s%s$ ", COLOR_RED, current_working_directory, COLOR_WHITE);


    //USER INPUT
    char * command = calloc(COMMAND_BUFFER, sizeof(char));
    fgets(command, COMMAND_BUFFER + 1, stdin);
    if (command[strlen(command) - 1] == '\n') {
      command[strlen(command) - 1] = '\0';
    }

    //PARSING
    int num_cmds = count_commands(command, ";");
    char ** cmd_list = calloc(num_cmds, sizeof(char *));
    construct_command_list(command, cmd_list);
    struct command_set ** main_list = calloc(num_cmds, sizeof(struct command *));
    parse_command_list(cmd_list, num_cmds, main_list);

    //EXECUTING
    execute_command_set(main_list, num_cmds);
    int status;
    wait(&status);
  }
}
