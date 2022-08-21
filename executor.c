#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

#include "parser.h"

/*
  Args:
    struct command * command: Simple command to be executed

  return:
    status of execvp() execution
*/
int execute_command(struct command * command) {
  char * cmd = command->args[0];

  int f = fork();
  if (f == 0) {
    int status = execvp(cmd, command->args);
    exit(errno);
  } else {
    int status = 0;
    waitpid(f, &status, 0);

    return WEXITSTATUS(status);
  }
}

/*
  Args:
    struct command_set * set: struct of set of commands delimited by "|" (pipes)

  return:
    1 or -1 depending on success of execution. Executes piped commands
    using execute_command. This is the main pipe handler.
*/
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
    if (status) {
      dup2(input, STDIN_FILENO);
      close(input);
      dup2(output, STDOUT_FILENO);
      close(output);
      return status;
    }
  }

  dup2(input, STDIN_FILENO);
  close(input);
  dup2(output, STDOUT_FILENO);
  close(output);

  return 0;
}

/*
  Args:
    struct command_set ** main_list: Array of struct command_set * to be executed,
      taken from command delimited by ";"
    num_cmds: Number of commands delimited by ";"

  return:
    1 or -1 depending on success of execution. Executes each item in the Array
    through pipe_execute.
*/
int execute_command_set(struct command_set ** main_list, int num_cmds) {
  int i = 0;
  for (i = 0; i < num_cmds; i++) {
    struct command_set * set = main_list[i];
    int status = pipe_execute(set);

    if (status) {
      printf("%s\n", strerror((status)));
      return status;
    }
  }

  return 1;
}
