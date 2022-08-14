/*
  struct to hold single command
*/
struct command {
  int num_args;
  char ** args;
};

/*
  struct to hold command set, such as "ls -a -l | grep README.md"
*/
struct command_set {
  struct command ** cmds;
  int num_cmds;
};

/*
  Args:
    char * command: string
  returns:
    in-place edit of command to remove all repetitive spaces
*/
void clean(char * command);

/*
  Args:
    char * command: user-inputted command

  returns:
    Number of commands as delimited by ";"
*/
int count_commands(char * command, char * delimiter);

/*
  Args:
    char * command: user-inputted command (single command such as "ls -l -a")

  returns:
    struct ** command
*/
struct command * parse_command(char * command);

/*
  Args:
    char ** command_list: Array of commands delimited by ";",
    int num_cmds: Number of commands delimited by ";";
    struct command_set ** main_list: Array of struct command_set * to be modified

  returns:
    None: modifies main_list so that it is an array of struct command_set *
          each command delimited by a ";" becomes an command_set.
*/
void parse_command_list(char ** command_list, int num_cmds, struct command_set ** main_list);

/*
  Args:
    command: user-inputted command,
    cmd_list: cmd_list to be filled with struct * command,

  return:
    void
*/
void construct_command_list(char * command, char ** cmd_list);
