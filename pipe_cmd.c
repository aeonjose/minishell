#include"mini.h"

int pipe_cmd(char *cmd)
{
    puts("pipe working");
    int pid1, pid2, status1, status2, i=0, j=0;
    int p[2], argc = 0;					//creating the pipe variabes
    char *argv[5] = {NULL};
    int fd = dup(1);
    if(pipe(p) == -1)				// creating the pipe
    {
	puts("error pipe");
	exit(1);
    }
    argv[j++] = cmd;
    while(cmd[i])
    { 
	if(cmd[i] == ' ')
	{
	    cmd[i] = '\0';
	    argc ++;
	    argv[j] = &cmd[i+1];
	    j++;
	}
	i++;
    }

   
	printf("%s \n",argv[3]);
    printf("%d\n", argc);
    for(i = 0; i <= argc; i++)			// changing | to NULL
    {
	printf("%s \n",argv[i]);
	if (!strcmp(argv[i],"|"))
	{
	    argv[i] = NULL;
	    break;
	}
    }
    pid1 = fork();				// creating the first child

    switch(pid1)
    {
	case 0 : close(p[0]);
		 dup2(p[1], 1);
		 execvp(argv[0], &argv[0]);
		 break;

	default : sleep(2);
		  pid2 = fork();		// creating the second child

		  switch(pid2)
		  {
		      case 0 : close(p[1]);
			       puts("ebnhs");
			       dup2(p[0], 0);
			   //    execvp(argv[2], &argv[2]);
			     system("wc");
			     //exit(0);
			       break;

		      default : sleep(1);
				waitpid(pid1,&status1,0);
				waitpid(pid2,&status2,0);
			       printf("hai\n");
		  }
    }
    return 0;
}
