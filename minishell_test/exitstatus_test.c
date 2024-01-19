#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


int main(int ac, char **av, char **env)
{
    char    *str[3];
    int		stt;
    pid_t   pid_fork;
	int		exit_status;

    str[0] = "/bin/cat";
    str[1] = "non_existing_file.txt";
    str[2] = NULL;
    if ((pid_fork = fork()) == 0)
        execve("/bin/cat", str, env);
    else
        waitpid(pid_fork, &stt, 0);
		if (WIFEXITED(stt))
			exit_status = WEXITSTATUS(stt);
	printf("exit status: %d\n", exit_status);
    return (0);
}

