#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

#define COMMAND_BUFFER 256

int main() {
  int error = 0;

  while (!error) {
    char * command = calloc(COMMAND_BUFFER, sizeof(char));
    fgets(command, COMMAND_BUFFER + 1, stdin);

    clean(command);
    printf("%s \n", command);
  }
}
