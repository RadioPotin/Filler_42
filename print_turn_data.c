/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_turn_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 12:52:40 by dapinto           #+#    #+#             */
/*   Updated: 2019/07/18 13:39:20 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		print_turn(t_filler f)
{
	ft_printf("Res:(%d;%d). Star %d:(%d;%d), heat:%d. Mapcoord:(%d;%d)\n",
			f.p.anchor.py, f.p.anchor.px,
			f.p.anchor.star, f.p.pj, f.p.pi, f.p.anchor.heat,
			f.mapy, f.mapx);
}

static void		print_heatmap(t_filler f)
{
	int i;
	int j;

	j = 0;
	ft_printf("----HEATMAP----\n");
	if (f.heatmap)
		while (j < f.hmap)
		{
			i = 0;
			ft_printf("line %d:", j);
			while (i < f.wmap)
			{
				ft_printf("%d", f.heatmap[j][i]);
				if (i != f.wmap - 1)
					ft_printf(",");
				else
					ft_printf("\n");
				i++;
			}
			j++;
		}
	else
		ft_printf("HEATMAP is NULL\n");
}

static void		print_map(t_filler f)
{
	int j;

	j = 0;
	ft_printf("------MAP------\n");
	ft_printf("MAP INFO: WIDTH: %d, HEIGHT: %d, SIZE: %d\n", f.wmap,
			f.hmap, f.wmap * f.hmap);
	if (f.map)
	{
		while (j < f.hmap)
		{
			if (j <= 9)
				ft_printf("line %d: |%s|\n", j, f.map[j]);
			else
				ft_printf("line %d:|%s|\n", j, f.map[j]);
			j++;
		}
	}
	else
		ft_printf("MAP is NULL\n");
}

static void		print_piece(t_filler f)
{
	int j;

	j = 0;
	if (f.piece)
		while (j < f.p.hei)
		{
			ft_printf("line %d:|%s|\n", j, f.piece[j]);
			j++;
		}
	else
		ft_printf("Piece is NULL\n");
}

void			print_turn_data(t_filler f, int flag)
{
	if (!flag)
		print_turn(f);
	else
	{
		ft_printf("\n\nMY_ID:%c, ENEMY_ID:%c\n", f.my_id, f.his_id);
		ft_printf("-----PIECE-----\n");
		ft_printf("PIECE INFO: WIDTH: %d, HEIGHT: %d, SIZE: %d\n", f.p.wid,
				f.p.hei, f.p.wid * f.p.hei);
		ft_printf("STARS = %d\n", f.p.stars);
		ft_printf("Chosen star = %d for %d heat\n", f.p.tmpsave.star,
				f.p.tmpsave.heat);
		print_map(f);
		print_piece(f);
		print_heatmap(f);
	}
}
