#include <libft.h>
#include <philosophers.h>

int	parse_argment(int argc, char *argv[])
{
	size_t	i;
	size_t	j;

	if (argc != 5 && argc != 6)
		return (ERR_ARG_NUM);
	i = 1;
	while (i < argc)
	{
		if (ft_isdigit_str(argv[i], 0) == false)
			return (ERR_INVALID_ARG);
		i++;
	}
	return (SUCCESS);
}
