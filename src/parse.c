#include <philosophers.h>


int	parse_argment(int argc, char *argv[])
{
	size_t	i;
	size_t	j;
	size_t	philo_num;
	t_philo	*philo;

	if (argc != 5)
		return (1);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while(argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
