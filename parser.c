#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct command {
  int num_args;

  char ** args;
};

/*
  Args:
    char * command: user-inputted command

  returns:
    struct ** command
*/
struct command ** parse_command(char * command) {

}

/*
  Args:
    char * command: string
  returns:
    in-place edit of command to remove all repetitive spaces
*/
void clean(char * command) {
  int len = strlen(command);
  for (int i = 0; i < len; i++) {
    if (command[i] == ' ' && command[i + 1] == ' ') {
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
