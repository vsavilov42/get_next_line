#include "get_next_line.h"

int	main(void)
{
	int		fd;
	int		i;
	char	*s;
	
	i = 0;
	fd = open("read.txt", O_RDONLY);
	s = get_next_line(fd);
	printf("%s", s);
	while (s)
	{
		free(s);
		s = get_next_line(fd);
		i++;
		printf("l %i: %s", i, s);
	}
//system("leaks a.out");
	return (0);
}
