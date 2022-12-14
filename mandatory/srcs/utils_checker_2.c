/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_checker_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:07:23 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/16 16:18:06 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	is_color(char *str, int **count)
{
	if (!ft_strncmp(str, "F ", 2))
	{
		(*count)[0]++;
		return (0);
	}
	if (!ft_strncmp(str, "C ", 2))
	{
		(*count)[1]++;
		return (1);
	}
	return (-1);
}

int	is_direction(char *str, int **count)
{
	if (!ft_strncmp(str, "NO ", 3))
	{
		(*count)[2]++;
		return (NORTH);
	}
	if (!ft_strncmp(str, "SO ", 3))
	{
		(*count)[3]++;
		return (SOUTH);
	}
	if (!ft_strncmp(str, "EA ", 3))
	{
		(*count)[4]++;
		return (EAST);
	}
	if (!ft_strncmp(str, "WE ", 3))
	{
		(*count)[5]++;
		return (WEST);
	}
	return (-1);
}

int	commas_number(char *str)
{
	int	commas_num;
	int	i;

	commas_num = 0;
	i = -1;
	while (str[++i])
		if (str[i] == ',')
			commas_num++;
	return (commas_num);
}

int	*copy_rgb_color(char **tab)
{
	int	*rgb;
	int	i;

	rgb = (int *)malloc(sizeof(int) * 3);
	i = -1;
	while (tab[++i])
	{
		rgb[i] = ft_atoi(tab[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			exit(puterror("Invalid color"));
	}
	return (rgb);
}

int	create_trgb(int transparency, int red, int green, int blue)
{
	int	trgb;

	trgb = 0;
	trgb += transparency << 24;
	trgb += red << 16;
	trgb += green << 8;
	trgb += blue;
	return (trgb);
}
