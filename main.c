#include "mini.h"

int main()
{
    // 1. variable initializaon.
    char cmd[30], shellname[50], ch;
    int i = 0, flag = 0;

    // 2. creating the while loop
    while(1)
    {
	// 3. printing the directory
	getcwd(shellname,sizeof(shellname));
	printf("%s->",shellname);
	//handling siganal
	signal(SIGINT, signal_handler);
	signal(SIGTSTP, signal_handler);
	// 4. accepting the command
	i = 0;
	memset(cmd,0,sizeof(cmd));
	while(ch = getchar())
	{
	    if(ch == '\n')
	    {
		cmd[i] = '\0';
		break;
	    }
	    if(ch == '|')
	    {
		flag = 1;
	    }
	    cmd[i++] = ch;
	}
	//	printf("the command is %s\n", cmd);
	// 5. process the command
	if(flag == 0)
	    cmd_process(cmd);
	else 
	    pipe_cmd(cmd);
	flag = 0;
    }
}
