#include "philo.h"

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

long    my_atol(char *str)
{
    long    res;
    int     i;
    int len;

    res = 0;
    i = 0;
    len = 0;
    if(ft_strlen(str) > 10)
        return (-1);
    if(str[i] == '\0' || str[i] < '0' || str[i] > '9')
        return (-1);
    while(str[i] >= '0' && str[i] <= '9')
        res = (res * 10) + (str[i++] - 48);
    if (str[i] || res > 2147483647)
        return (-1);
    return (res);
}
