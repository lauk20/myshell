/*
  struct to hold single command
*/
struct command {
  int num_args;

  char ** args;
};

struct command_set {
  struct command ** cmds;
  int num_cmds;
};

/*
  Args:
    char * command: user-inputted command

  returns:
    struct ** command
*/
struct command * parse_command(char * command);

struct command_set * parse_command_list(char ** command_list, int num_cmds);

int count_commands(char * command);

/*
  Args:
    char * command: string
  returns:
    in-place edit of command to remove all repetitive spaces
*/
void clean(char * command);

void construct_command_list(char * command, char ** cmd_list);
