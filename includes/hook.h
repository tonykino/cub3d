/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:09:53 by tokino            #+#    #+#             */
/*   Updated: 2021/11/14 17:52:31 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOK_H
# define HOOK_H

# include <stdlib.h>
# include <stdio.h>
# include "constants.h"
# include "clear_and_exit.h"
# include "data_struct.h"
# include "player_struct.h"

int	handle_keypress(int keycode, t_player *player);
int	handle_keyrelease(int keycode, t_data *data);
int	mouse_hook(int button, int x, int y);

#endif
