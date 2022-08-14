/*
  Args:
    struct command_set ** main_list: Array of struct command_set * to be executed,
      taken from command delimited by ";"
    num_cmds: Number of commands delimited by ";"

  return:
    1 or -1 depending on success of execution. Executes each item in the Array
    through pipe_execute.
*/
int execute_command_set(struct command_set ** main_list, int num_cmds);
