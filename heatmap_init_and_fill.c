/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap_init_and_fill.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 14:42:21 by dapinto           #+#    #+#             */
/*   Updated: 2019/07/18 10:39:51 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int		check_heat(t_filler *f, int i, int x, int y)
{
	int target;

	if (i == 0)
		target = ENNEMYHEAT;
	else
		target = i;
	if (x + 1 < f->wmap && f->heatmap[y][x + 1] == target)
		return (1);
	if (y + 1 < f->hmap && f->heatmap[y + 1][x] == target)
		return (1);
	if (x + 1 < f->wmap && y + 1 < f->hmap
			&& f->heatmap[y + 1][x + 1] == target)
		return (1);
	if (x + 1 < f->wmap && y - 1 >= 0 && f->heatmap[y - 1][x + 1] == target)
		return (1);
	if (x - 1 >= 0 && f->heatmap[y][x - 1] == target)
		return (1);
	if (y - 1 >= 0 && f->heatmap[y - 1][x] == target)
		return (1);
	if (x - 1 >= 0 && y - 1 >= 0 && f->heatmap[y - 1][x - 1] == target)
		return (1);
	if (x - 1 >= 0 && y + 1 < f->hmap && f->heatmap[y + 1][x - 1] == target)
		return (1);
	return (0);
}

static void		set_temperatures(t_filler *f)
{
	int x;
	int y;
	int i;

	i = -1;
	while (++i < f->wmap)
	{
		y = 0;
		while (y < f->hmap)
		{
			x = 0;
			while (x < f->wmap)
			{
				if (f->heatmap[y][x] == 0)
					if (check_heat(f, i, x, y) == 1)
						f->heatmap[y][x] = i + 1;
				x++;
			}
			y++;
		}
	}
}

static void		init_heatmap(int j, t_filler *f)
{
	int i;

	i = 0;
	while (i < f->wmap)
	{
		if (f->map[j][i] == f->my_id || f->map[j][i] == f->my_id + 32
				|| f->map[j][i] == f->his_id || f->map[j][i] == f->his_id + 32)
			f->heatmap[j][i] = (f->map[j][i] == f->my_id + 32
					|| f->map[j][i] == f->my_id
					|| f->map[j][i] == f->my_id + 32) ? MYHEAT : ENNEMYHEAT;
		else
			f->heatmap[j][i] = 0;
		i++;
	}
}

int				make_heatmap(t_filler *f)
{
	int j;

	if (!(f->heatmap = malloc(sizeof(int *) * f->hmap + 1)))
		return (-1);
	f->heatmap[f->hmap] = NULL;
	j = 0;
	while (j < f->hmap)
	{
		if (!(f->heatmap[j] = malloc(sizeof(int) * f->wmap)))
		{
			ft_inttabdel(j, &f->heatmap);
			return (-1);
		}
		init_heatmap(j, f);
		j++;
	}
	set_temperatures(f);
	return (0);
}
