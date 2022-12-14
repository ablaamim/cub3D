/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:55:44 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/16 22:12:54 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		close_win(data);
	else if (keycode == W_KEY || keycode == A_KEY || keycode == UP_KEY)
	{
		data->player.mov_direction = 1;
		data->player.side_angle = 0;
		if (keycode == A_KEY)
			data->player.side_angle = M_PI / 2;
	}
	else if (keycode == S_KEY || keycode == D_KEY || keycode == DOWN_KEY)
	{
		data->player.mov_direction = -1;
		data->player.side_angle = 0;
		if (keycode == D_KEY)
			data->player.side_angle = M_PI / 2;
	}
	else if (keycode == RIGHI_KEY)
		data->player.rot_direction = 1;
	else if (keycode == LEFT_KEY)
		data->player.rot_direction = -1;
	key_press_2(keycode, data);
	return (0);
}

void	key_press_2(int keycode, t_data *data)
{
	if (keycode == KEY_SHIFT)
		data->player.mov_speed = SHIFT_MODE;
	else if (keycode == X_KEY && !data->weapon.render_shooting && \
			!data->weapon.render_reloading)
	{
		ft_afplay(GUNSHOT, &data->pid_gunshot);
		data->weapon.render_shooting = 1;
	}
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == W_KEY || keycode == A_KEY || \
		keycode == S_KEY || keycode == D_KEY || \
		keycode == UP_KEY || keycode == DOWN_KEY)
		data->player.mov_direction = 0;
	else if (keycode == RIGHI_KEY || keycode == LEFT_KEY)
		data->player.rot_direction = 0;
	else if (keycode == KEY_SHIFT)
		data->player.mov_speed = NORMAL_MODE;
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	data->player.rot_direction = 0;
	if (x >= 0 && x <= WIN_WIDTH && y >= 0 && y <= WIN_HEIGHT)
		data->player.rot_direction = (x - (WIN_WIDTH / 2)) / 1000.0;
	return (0);
}

int	close_win(t_data *data)
{
	kill(data->pid_music, SIGKILL);
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}
