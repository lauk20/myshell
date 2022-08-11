/*
  Args:
    char * command: user-inputted command

  returns:
    struct ** command
*/
struct command ** parse_command(char * command);

/*
  Args:
    char * command: string
  returns:
    in-place edit of command to remove all repetitive spaces
*/
void clean(char * command);
