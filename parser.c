#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
/*
  Args:
    char * command: string
  returns:
    in-place edit of command to remove all repetitive spaces
*/
void clean(char * command) {
  int len = strlen(command);
  for (int i = 0; i < len; i++) {
    if ((command[i] == ' ' && command[i + 1] == ' ') || (command[i] == '\n') || (i == 0 && command[i] == ' ')) {
      //shift string left
      int j = i;
      for (j = i; j < len - 1; j++) {
        command[j] = command[j + 1];
      }
      //end string with null byte
      command[j] = '\0';
      len = strlen(command);
      i = i - 1;
    }
  }

  if (command[len - 1] == ' ') {
    command[len - 1] = '\0';
  }
}

/*
  Args:
    char * command: user-inputted command (single command such as "ls -l -a")

  returns:
    struct ** command
*/
struct command * parse_command(char * command) {
  clean(command);

  int num_args = 0;
  char * command_copy = calloc(strlen(command) + 1, sizeof(char));
  strcpy(command_copy, command);

  while (strsep(&command_copy, " ")) {
    num_args = num_args + 1;
  }
  free(command_copy);

  char ** args = calloc(num_args + 1, sizeof(char*));
  char * token;
  int counter = 0;
  while (token = strsep(&command, " ")) {
    args[counter] = token;
    counter = counter + 1;
  }
  args[counter] = NULL;

  struct command * cmd = calloc(1, sizeof(struct command));
  cmd->args = args;
  cmd->num_args = num_args;

  return cmd;
}
