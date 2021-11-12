/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:10:25 by tokino            #+#    #+#             */
/*   Updated: 2021/11/12 17:18:21 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clear_and_exit.h" 

void	clear_and_exit(int err_code, char *err_msg)
{
	printf("Error\n%s\n", err_msg);
	printf("\n\n---- LEAKS ----\n");
	system("leaks --quiet cub3d");
	exit(err_code);
}

void	cleanup_and_exit(t_data *data, int exit_status)
{
	t_window	*window;
	int			i;

	i = 0;
	window = &data->window;
	if (window->color_buffer)
		free(window->color_buffer);
	if (window->win_img.mlx_img)
		mlx_destroy_image(window->mlx_ptr, window->win_img.mlx_img);
	while (i < NUM_TEXTURES)
	{
		if (data->textures[i].mlx_img)
			mlx_destroy_image(window->mlx_ptr, data->textures[i].mlx_img);
		i++;
	}
	if (window->win_ptr)
		mlx_destroy_window(window->mlx_ptr, window->win_ptr);
	if (window->mlx_ptr)
	{
		mlx_destroy_display(window->mlx_ptr);
		free(window->mlx_ptr);
	}
	exit(exit_status);
}
