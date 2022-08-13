#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "parser.h"
#include "executor.h"

#define COMMAND_BUFFER 256

int main() {
  int error = 0;

  while (!error) {
    char * command = calloc(COMMAND_BUFFER, sizeof(char));
    fgets(command, COMMAND_BUFFER + 1, stdin);
    if (command[strlen(command) - 1] == '\n') {
      command[strlen(command) - 1] = '\0';
    }

    int num_cmds = count_commands(command);
    char ** cmd_list = calloc(num_cmds, sizeof(char *));
    construct_command_list(command, cmd_list);
    //struct command * cmd = parse_command(command);

    //execute_command(cmd, cmd_list, fd_pipe);
  }
}
