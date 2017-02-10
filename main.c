//
// Created by Jonathan CARRA on 2/10/17.
//

#include <unistd.h>
#include <stdlib.h>

int		main()
{
	char *tmp;

	tmp = malloc(1);
	free(tmp);
	free(tmp);
	return (0);
}