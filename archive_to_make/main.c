#include "main.h"

void	c(void)
{
	system("leaks a.out");
}

int	main(int ac, char **av)
{
	t_shared	*shared;
	t_philo		**philos;

	atexit(c);

	if (ac != 5 && ac != 6)
	{
		printf("Invalid ac\n");
		return (1);
	}
	shared = init_shared_info(av);
	philos = init_philo(shared);


	return (0);
}