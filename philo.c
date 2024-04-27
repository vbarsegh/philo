#include "philo.h"

int main(int ac, char **av)
{
	t_info	info;
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
	{
		write(1,"Invalid count of argc\n", 22);
		return (1);
	}
	if (init_info(ac, av, &info) == -1)
		return (1 && printf("Error\n"));
	start_emulation(&info);
}

