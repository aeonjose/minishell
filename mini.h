#ifndef MINI_H
#define MINI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define cmd_no 8
int  cmd_process(char * cmd);
void echo_fam(char *cmd);
void cd_cmd(char * cmd);
void sleep_cmd(char * cmd);
void cmd_exec(char * cmd);
void signal_handler();
int pipe_cmd(char *cmd);

#endif
