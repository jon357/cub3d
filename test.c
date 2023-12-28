#include <stdio.h>

typedef struct s_1
{
	char *str;
}	t_1;

typedef struct s_2
{
	t_1	s1;
}	t_2;

void	test(t_2 *s2)
{
	s2->s1.str = "test";
	printf("%s\n", s2->s1.str);
}

int	main(void)
{
	t_2 s2;

	test(&s2);
}