/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjup <hyungjup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:12:39 by hyungjup          #+#    #+#             */
/*   Updated: 2023/04/17 20:07:54 by hyungjup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_paint.h"

typedef struct	s_info
{
	int		w;
	int		h;
	char	big_c;
}	t_info;
t_info	info;

typedef struct	s_circle
{
	char	type;
	float	x;
	float	y;
	float	r;
	char	draw_c;
}	t_circle;

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	write(1, s, i);
	return (1);
}

int	file_error(void)
{
	ft_putstr("Error: Operation file corrupted\n");
	return (1);
}

int	check_circle(float x, float y, t_circle *c)
{
	float	dist;

	dist = sqrt(powf(x - c->x, 2) + powf(y - c->y, 2));
	if (dist > c->r)
		return (0);
	if (c->r - dist < (float)1)
		return (2);
	return (1);
}

void	mini_paint(char **map, t_circle *c)
{
	int	result;

	for (int i = 0; i < info.h; i++)
	{
		for (int j = 0; j < info.w; j++)
		{
			result = check_circle(j, i, c);
			if ((c->type == 'c' && result == 2) || (c->type == 'C' && result))
				map[i][j] = c->draw_c;
		}
	}
}

void	print_map(char **map)
{
	for (int i = 0; i < info.h; i++)
	{
		for (int j = 0; j < info.w; j++)
		{
			write(1, &map[i][j], 1);
		}
		write(1, "\n", 1);
	}
}

int	main(int argc, char **argv)
{
	int			i, j, result;
	char		**map;
	FILE		*f;
	t_circle	c;

	if (argc != 2)
	{
		ft_putstr("Error: argument\n");
		return (1);
	}
	f = fopen(argv[1], "r");
	if (f == NULL)
		return (file_error());
	if (fscanf(f, "%d %d %c\n", &info.w, &info.h, &info.big_c) != 3)
		return (file_error());
	if (!(info.w > 0 && info.w <= 300 && info.h > 0 && info.h <= 300))
		return (file_error());
	map = malloc(sizeof(char *) * (info.h + 1));
	if (map == NULL)
		return (1);
	for (i = 0; i < info.h; i++)
	{
		map[i] = malloc(info.w + 1);
		if (map[i] == NULL)
			return (1);
		for (j = 0; j < info.w; j++)
		{
			map[i][j] = info.big_c;
		}
		map[i][j] = 0;
	}
	map[i] = 0;
	while ((result = fscanf(f, "%c %f %f %f %c\n", &c.type, &c.x, &c.y, &c.r, &c.draw_c)) == 5)
	{
		if (c.r <= (float)0 || !(c.type == 'c' || c.type == 'C'))
			return (file_error());
		mini_paint(map, &c);
	}
	if (result != -1)
		return (file_error());
	print_map(map);
	for (i = 0; i < info.h; i++)
		free(map[i]);
	free(map);
	fclose(f);
	return (0);
}
