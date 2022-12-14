/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:42:50 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/17 17:01:07 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*
 * Check config file elements :
*/

void	checker(t_elm *elm, char *arg)
{
	char	**file;
	int		i;

	if (ft_strncmp(arg + ft_strlen(arg) - 4, ".cub", 4) || ft_strlen(arg) <= 4)
		exit(puterror("file extension must be .cub"));
	file = read_file(arg);
	elm->map_width = map_width(file);
	elm->map_height = map_height(file);
	elm->map = (char **)ft_calloc(elm->map_height + 1, sizeof(char *));
	i = -1;
	while (file[++i])
	{
		elm->map[i] = (char *)ft_calloc(elm->map_width + 1, sizeof(char));
		ft_strlcpy(elm->map[i], file[i], ft_strlen(file[i]) + 1);
	}
	elm->map[i] = NULL;
	free_double_pointer(file);
	check_map(elm->map);
}

char	**read_file(char *arg)
{
	char	**file;
	int		fd;
	int		i;

	fd = open(arg, O_RDONLY);
	if (fd == -1)
		exit(puterror("Cub3D file not found"));
	file = (char **)malloc(sizeof(char *) * 1000);
	i = 0;
	file[i] = get_next_line(fd);
	if (!file[i])
		exit(puterror("Cub3D file unreadable"));
	while (file[i++])
		file[i] = get_next_line(fd);
	close(fd);
	return (file);
}

void	check_map(char **map)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (is_player(map[i][j]))
				count++;
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' ' && \
				map[i][j] != 'd' && map[i][j] != 'e' && !is_player(map[i][j]))
				exit(puterror("Invalid map"));
			if ((map[i][j] == '0' || map[i][j] == 'd' || \
				map[i][j] == 'e' || is_player(map[i][j])) && \
				!map_is_valid(map, i, j))
				exit(puterror("Invalid map"));
		}
	}
	if (count != 1)
		exit(puterror("Invalid map"));
}

int	map_is_valid(char **map, int i, int j)
{
	if (!i || !map[i + 1] || !map[i + 1][j] || (i && !map[i - 1][j]) || \
		!j || !map[i][j + 1] || (j && !map[i][j - 1]) || \
		map[i + 1][j] == ' ' || (i && map[i - 1][j] == ' ') || \
		map[i][j + 1] == ' ' || (j && map[i][j - 1] == ' '))
		return (0);
	return (1);
}
