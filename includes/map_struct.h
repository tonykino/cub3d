/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:57:58 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 17:58:39 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_STRUCT_H
# define MAP_STRUCT_H

typedef struct s_map {
	int		tile_size;
	int		num_rows;
	int		num_cols;
	char	**grid;
}	t_map;

#endif
