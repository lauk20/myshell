#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "parser.h"

int execute_command(struct command * command) {
  int input = dup(STDIN_FILENO);
  int output = dup(STDOUT_FILENO);

  int read = dup(input);
  int write = dup(output);




  char * cmd = command->args[0];

  if (fork() == 0) {
    int status = execvp(cmd, command->args);

    if (status == -1) {
      printf("Error\n");
    }

    exit(status);
  }

}

int execute_command_set(struct command_set ** main_list, int num_cmds) {
  int i = 0;
  for (i = 0; i < num_cmds; i++) {
    struct command_set * set = main_list[i];

    int j = 0;
    for (j = 0; j < set->num_cmds; j++) {
      execute_command(set->cmds[j]);
    }
  }
}
