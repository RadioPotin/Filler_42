/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anchor_point_management.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:59:08 by dapinto           #+#    #+#             */
/*   Updated: 2019/07/18 11:04:51 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		set_relativity(t_filler *f, int j)
{
	int min_y;
	int min_x;

	min_y = f->p.relat_coor[j][0];
	min_x = f->p.relat_coor[j][1];
	while (j < f->p.stars)
	{
		f->p.relat_coor[j][0] -= min_y;
		f->p.relat_coor[j][1] -= min_x;
		j++;
	}
}

static void		set_anchor(t_filler *f, int j)
{
	int x;
	int y;

	x = f->p.pi;
	y = f->p.pj;
	while (j < f->p.stars)
	{
		while (y < f->p.hei)
		{
			while (x < f->p.wid)
			{
				if (f->piece[y][x] == '*' && j < f->p.stars)
				{
					f->p.relat_coor[j][0] = y;
					f->p.relat_coor[j][1] = x;
					j++;
				}
				x++;
			}
			x = 0;
			y++;
		}
		y = 0;
	}
}

void			set_init_anchors(t_filler *f, int turn)
{
	int j;

	j = 0;
	f->p.anchor.px = f->mapx - f->p.pi;
	f->p.anchor.py = f->mapy - f->p.pj;
	f->p.anchor.star = turn;
	set_anchor(f, j);
	set_relativity(f, j);
}
