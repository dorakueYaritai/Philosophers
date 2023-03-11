#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <readline/readline.h>

#define IN_CMD 0
#define OUT_CMD 1

volatile sig_atomic_t g_status;

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		kill(0, SIGINT);
		printf("SIG INT!\n");
	}
}



int	main()
{
	int	status;
	struct sigaction sa;
	pid_t	pid;
	char	*line;

	g_status = OUT_CMD;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = signal_handler;
	sigaction(SIGINT, &sa, NULL);

	while (1)
	{
		line = readline("mini; ");
		if (line == NULL)
			break;
		pid = fork();
		if (pid == -1)
			return 0;
		else if (pid == 0)
		{
			// signal(SIGINT, SIG_DFL);
			// pause();
			execlp(line, line, NULL);
			exit(EXIT_SUCCESS);
		}
		else
		{
			// signal(SIGINT, SIG_IGN);
			wait(&status);
			// sigaction(SIGINT, &sa, NULL);
		}
	}
	return (0);
}

// vpath %c $(SRCSDIR) $(SR)