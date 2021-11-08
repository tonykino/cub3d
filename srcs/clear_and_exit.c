#include "clear_and_exit.h" 

void	clear_and_exit(int err_code, char *err_msg)
{
	printf("Error\n%s\n", err_msg);
	printf("\n\n---- LEAKS ----\n");
	system("leaks --quiet cub3d");
	exit(err_code);
}