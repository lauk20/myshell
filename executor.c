#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "parser.h"

int execute_command(struct command * command) {
  char * cmd = command->args[0];

  if (fork() == 0) {
    int status = execvp(cmd, command->args);

    if (status == -1) {
      printf("Error\n");
    }

    exit(status);
  }
}

int execute_command_set(struct command_set * cmd_set) {
  struct command ** cmds = cmd_set->cmds;
  for (int i = 0; i < cmd_set->num_cmds; i++) {
    struct command * cmd = cmds[i];
    execute_command(cmd);
  }
}
