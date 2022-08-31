#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

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
    char * command: user-inputted command

  returns:
    Number of commands as delimited by ";"
*/
int count_commands(char * command, char * delimiter) {
  clean(command);

  char * command_copy = calloc(strlen(command) + 1, sizeof(char));
  strcpy(command_copy, command);

  int num_commands = 0;
  while (strsep(&command_copy, delimiter)) {
    num_commands = num_commands + 1;
  }
  free(command_copy);

  return num_commands;
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

  char ** new_args = calloc(num_args + 1, sizeof(char*));
  counter = 0;
  char * output_file = calloc(257, sizeof(char));
  char * input_file = calloc(257, sizeof(char));
  for (int i = 0; i < num_args; i++){
    if (strcmp(args[i], ">") == 0) {
      i = i + 1;
      if (i >= num_args) {
        printf("Error\n");
      } else {
        strncpy(output_file, args[i], 256);
        int fd = open(output_file, O_WRONLY | O_CREAT, 0644);
        close(fd);
      }
    } else if (strcmp(args[i], "<" == 0)) {
      i = i + 1;
      if (i >= num_args) {
        printf("Error\n");
      } else {
        strncpy(input_file, args[i], 256);
        int fd = open(input_file, O_RDONLY, 0644);
        close(fd);
      }
    } else {
      new_args[counter] = args[i];
      counter = counter + 1;
    }
  }
  new_args[counter] = NULL;

  struct command * cmd = calloc(1, sizeof(struct command));
  cmd->args = new_args;
  cmd->num_args = counter - 1;;
  cmd->output_file = output_file;
  //add input file to struct command

  return cmd;
}

/*
  Args:
    char ** command_list: Array of commands delimited by ";",
    int num_cmds: Number of commands delimited by ";";
    struct command_set ** main_list: Array of struct command_set * to be modified

  returns:
    None: modifies main_list so that it is an array of struct command_set *
          each command delimited by a ";" becomes an command_set.
*/
void parse_command_list(char ** command_list, int num_cmds, struct command_set ** main_list) {
  char * token;
  int num = 0;
  for (num = 0; num < num_cmds; num++) {
    struct command_set * set = calloc(1, sizeof(struct command_set));
    int command_num = count_commands(command_list[num], "|");
    struct command ** cmds = calloc(command_num, sizeof(struct command *));

    int i = 0;
    while (token = strsep(&command_list[num], "|")) {
      struct command * cmd = parse_command(token);
      cmds[i] = cmd;
      set->output_file = cmd->output_file;
      i = i + 1;
    }

    set->cmds = cmds;
    set->num_cmds = command_num;

    main_list[num] = set;
  }
}

/*
  Args:
    command: user-inputted command,
    cmd_list: cmd_list to be filled with struct * command,

  return:
    void
*/
void construct_command_list(char * command, char ** cmd_list) {
  clean(command);

  int index = 0;
  char * token;
  while (token = strsep(&command, ";")) {
    clean(token);
    cmd_list[index] = token;
    index = index + 1;
  }
}
