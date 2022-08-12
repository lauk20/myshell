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
      return -1;
    }
  }
}
