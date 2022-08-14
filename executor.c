#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "parser.h"

int execute_command(struct command * command) {
  char * cmd = command->args[0];

  if (fork() == 0) {
    int status = execvp(cmd, command->args);

    exit(status);
  }

  int status;
  wait(&status);

  return status;
}

int pipe_execute(struct command_set * set) {
  int input = dup(STDIN_FILENO);
  int output = dup(STDOUT_FILENO);

  int read = dup(input);
  int write = dup(output);

  int j = 0;
  for (j = 0; j < set->num_cmds; j++) {
    dup2(read, STDIN_FILENO);
    close(read);

    if (j != set->num_cmds - 1) {
      int pipe_fd[2];
      pipe(pipe_fd);
      read = pipe_fd[0];
      write = pipe_fd[1];
    } else {
      write = dup(output);
    }

    dup2(write, STDOUT_FILENO);
    close(write);

    int status = execute_command(set->cmds[j]);
    if (status == -1) {
      return status;
    }
  }

  dup2(input, STDIN_FILENO);
  close(input);
  dup2(output, STDOUT_FILENO);
  close(output);

  return 1;
}

int execute_command_set(struct command_set ** main_list, int num_cmds) {
  int i = 0;
  for (i = 0; i < num_cmds; i++) {
    struct command_set * set = main_list[i];
    int status = pipe_execute(set);

    if (status == -1) {
      return status;
    }
  }
}
