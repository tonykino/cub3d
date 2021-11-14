/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:41:38 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 13:42:43 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	number_of_splitted_elt(char **ary)
{
	int	count;

	count = 0;
	while (ary[count])
		count++;
	return (count);
}

void	free_ary(char **ary)
{
	int	i;

	i = 0;
	while (ary[i])
		free(ary[i++]);
	free(ary);
}

void	free_line_and_eoe(char *line, t_data *data, char *err_msg)
{
	free(line);
	exit_on_error(data, err_msg);
}

void	free_ary_line_and_eoe(char **res, char *line, t_data *data, char *emsg)
{
	free_ary(res);
	free_line_and_eoe(line, data, emsg);
}
