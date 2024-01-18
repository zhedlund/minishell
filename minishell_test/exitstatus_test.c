#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() 
{

    pid_t child_pid = fork();
	pid_t rc_pid;
	int   chld_state;
	rc_pid = wait(&chld_state);

    if (rc_pid > 0)
{
  if (WIFEXITED(chld_state)) {
    printf("Child exited with RC=%d\n",WEXITSTATUS(chld_state));
  }
  //if (WISIGNALED(chld_state)) {
    //printf("Child exited via signal %d\n",WTERMSIG(chld_state));

else
/* if no PID returned, then an error */
{
  if (errno == ECHILD) {
     printf("No children exist.\n");
  }
  else {
     printf("Unexpected error.\n");
     //abort();
  }
}

    return 0;
}
}