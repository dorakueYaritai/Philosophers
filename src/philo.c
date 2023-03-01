#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <philosophers.h>

#define PHILO_NUM 4

int mails = 0;

void	print_time(t_philo *philo, char *doing)
{
	printf("%ld:%d X is %s	", philo->time.tv_sec, philo->time.tv_usec, doing);
	printf("%ld:%d X is pre eating	", philo->pre_eat_start.tv_sec, philo->pre_eat_start.tv_usec);
	printf("%ld differences\n", philo->time.tv_sec - philo->pre_eat_start.tv_sec);
	printf("-----\n");
}

void	update_eat_time(t_philo *philo)
{
	philo->pre_eat_start.tv_sec = philo->time.tv_sec;
	philo->pre_eat_start.tv_usec = philo->time.tv_usec;
	gettimeofday(&philo->time, &philo->zone);
}

void	philo_eat(t_philo *philo)
{
	update_eat_time(philo);
	print_time(philo, "eating");
	sleep(1);
}

void	update_sleep_time(t_philo *philo)
{
	gettimeofday(&philo->time, &philo->zone);
}

void	philo_sleep(t_philo *philo)
{
	update_sleep_time(philo);
	print_time(philo, "sleeping");
	sleep(2);
}

void	think()
{
	struct timeval time;
	struct timezone zone;
	zone.tz_dsttime = 0;
	zone.tz_minuteswest = 0;
	gettimeofday(&time, &zone);
	printf("%d X is eating\n", time.tv_usec);
}


// void* routine(void *arg){
// 	int	i = 0;
// 	while (i < 100)
// 	{
// 		eat();
// 		think();
// 	}
// 	return NULL;
// }




int main(int argc, char* argv[]) {
    pthread_t th[PHILO_NUM];
	t_philo	philo1;
    int	i;

	i = 0;
	philo1.zone.tz_dsttime = 0;
	philo1.zone.tz_minuteswest = 0;
	int	j = 0;
	gettimeofday(&philo1.time, &philo1.zone);
	philo1.pre_eat_start.tv_sec = 0;
	// print_time(&philo1);
	philo_eat(&philo1);
	philo_sleep(&philo1);
	philo_eat(&philo1);
}