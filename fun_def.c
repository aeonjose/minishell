#include "mini.h"

char *cmd_list[cmd_no] = { "ls", "wc", "pwd", "echo", "exit", "cd","sleep","\0"};

int cmd_process(char * cmd)
{
    int i = 0;
    char temp_cmd[10],pwd[100];
    while((temp_cmd[i] = cmd[i]) != ' ' && cmd[i] != '\0')
	i++;
    temp_cmd[i] = '\0';
//    printf("%s  \n",temp_cmd);
    i=0;
    while(i < cmd_no)
    {
	//compairing the command with the existing commands
	if(!strcmp(temp_cmd, cmd_list[i]))
	{
	//    printf("cmd in list\n");
	    break;
	}
	i++;
    }
    if(i == cmd_no)
    {
	printf("%s : command not found\n", cmd);
	return -1;
    }
    //if cmd is exit
    if(!strcmp(temp_cmd, "exit"))
	exit(0);
    //if command is present working directory
    if(!strcmp(temp_cmd, "pwd"))
	printf(" \n%s\n",getcwd(pwd,sizeof(pwd)));
    //if cmd is change directory
    if(!strcmp(temp_cmd, "cd"))
	cd_cmd(cmd);
    //if cmd is echo
    if(!strcmp(temp_cmd, "echo"))
    {
//	printf("echo found\n");
	echo_fam(cmd);
    }
    //if command is ls, wc
    if((!strcmp(temp_cmd, "wc")) || (!strcmp(temp_cmd, "ls")))
    {
	cmd_exec(cmd);
    }
    //sleep command
    if(!strcmp(temp_cmd, "sleep"))
	sleep_cmd(cmd);
}


void echo_fam(char * cmd)
{
    char * arg;
    int i = 0, status;
    while(cmd[i++] != ' ');
    arg = &cmd[i];
  //  printf("%s  ",arg);

    //puts("echo  is working");
    if(strcmp(arg, "$?") == 0)
    {
	pid_t wpid = wait(&status);
	if(WIFEXITED(status))
	    printf("%d\n", wpid);
    }
    else if(!strcmp(arg,"$$"))
	printf("%d \n",getpid());
    else if(!strcmp(arg, "$SHELL"))
	printf("%s \n", getenv("SHELL"));
    else if(!strcmp(arg, "$PATH"))
	printf("%s \n",getenv("PATH"));
}

void cd_cmd(char * cmd)
{
   // printf("cd is working\n");
    int i = 0; 
    char direc[100], *arg;
    while(cmd[i++] != ' ');
    arg = &cmd[i];
    sprintf(direc,"%s/%s",getcwd(direc,sizeof(direc)),arg);
    if((chdir(direc)) != 0)
	printf("%s : no such file or director\n",cmd);
}

void sleep_cmd( char * cmd)
{
//puts("sleeping\n");
    int i = 0, time; 
    char  *arg;
    while(cmd[i++] != ' ');
    arg = &cmd[i];
    if(arg != NULL)
    {
	time = atoi(arg);
	sleep(time);
    }
}

void cmd_exec(char * cmd)
{
    int i = 0, j = 0;
    char * arg[3]= {NULL};
  //  puts("exec working");
    arg[j++] = cmd;
    while(cmd[i])
    {
	if(cmd[i] == ' ')
	{
	    cmd[i] = '\0';
	    arg[j] = &cmd[i+1];
	    j++;
	}
	i++;
    }
    pid_t pid = fork();
    if(pid == 0)
    {
	execvp(arg[0], arg);
    }
    else 
    {
	int status;
	waitpid(pid, &status, 0);
    }
}


void signal_handler()
{
    char *cmd = "\0", shellname[50];
    getcwd(shellname,sizeof(shellname));
    printf("\n");
    sprintf(shellname,"%s%s",shellname,"->");
    write(1,shellname, strlen(shellname));


}
