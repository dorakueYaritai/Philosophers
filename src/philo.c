#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

#define PHILO_NUM 4

int mails = 0;

void	eat()
{
	struct timeval time;
	struct timezone zone;
	zone.tz_dsttime = 0;
	zone.tz_minuteswest = 0;
	gettimeofday(&time, &zone);
	printf("%d X is eating¥n", time.tv_usec);
}

void	think()
{
	struct timeval time;
	struct timezone zone;
	zone.tz_dsttime = 0;
	zone.tz_minuteswest = 0;
	gettimeofday(&time, &zone);
	printf("%d X is eating¥n", time.tv_usec);
}

void* routine() {
	int	i = 0;
	while (i < 100)
	{
		eat();
		usleep(10000);
		think();
	}
	return NULL;
}



int main(int argc, char* argv[]) {
    pthread_t th[PHILO_NUM];
    int	i;

	i = 0;
	while (i < PHILO_NUM)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) == -1)
			return (-1);
		i++;
	}
	while (i < PHILO_NUM)
	{
		if (pthread_join(th[i], NULL) == -1)
			return (-1);
		i++;
	}
    printf("Number of mails: %d\n", mails);
    return 0;
}