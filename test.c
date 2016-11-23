#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
pid_t p1, p2;
void handler(int s)
{
    kill(p1, SIGUSR1);
    kill(p2, SIGUSR2);        
}

void handler1(int s)
{
		printf("Child Process 1 is Killed by Parent!\n");
		exit(0);
	
}

void handler2(int s)
{
		printf("Child Process 2 is Killed by Parent!\n");
		exit(0);
}

int main()	
{
	//pid_t p1, p2;
	int fildes[2];
	const int BSIZE = 100;
	char buf[BSIZE];
	int status;
	status = pipe(fildes);
	if (status == -1) {
		printf("an error occured!\n");
		//exit();
	}
	int i = 1;
	int p = 0;

	if((p1 = fork())==0) {
		close(fildes[0]);
			while(1) {
				signal(SIGINT, SIG_IGN);
				signal(SIGUSR1, handler1);
				write(fildes[1],&i,4);
				printf("I send you %d times\n",i);
				sleep(1);
				i++;
			}
			close(fildes[1]);
			exit(EXIT_SUCCESS);
			//break;
	}
	else if ((p2 = fork())==0) {
		close(fildes[1]);
		while(1) {
			signal(SIGINT, SIG_IGN);
			signal(SIGUSR2, handler2);
			read(fildes[0],&p,4);
			//sleep(1);	
			printf("I receive you %d times\n",p);
		}
		close(fildes[0]);
		exit(EXIT_SUCCESS);
	}
		else {
			signal(SIGINT, handler);
			wait(0);
			wait(0);
			//while(1);
		}
	return 0;
}


	
	
