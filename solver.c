/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:54:39 by dapinto           #+#    #+#             */
/*   Updated: 2019/07/18 12:39:22 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static	int		check_placement(t_filler *f)
{
	int j;
	int relaty;
	int relatx;

	j = 1;
	while (j < f->p.stars)
	{
		relaty = f->p.relat_coor[j][0];
		relatx = f->p.relat_coor[j][1];
		if ((f->mapy + relaty < f->hmap && f->mapy + relaty >= 0
					&& f->mapx + relatx < f->wmap && f->mapx + relatx >= 0)
				&& f->map[f->mapy + relaty][f->mapx + relatx] == '.')
			j++;
		else
			return (0);
	}
	return (1);
}

static int		check_stars(t_filler *f, int turn)
{
	int j;
	int i;
	int count;

	j = 0;
	count = 0;
	if (turn < f->p.stars)
		while (j < f->p.hei)
		{
			i = 0;
			while (i < f->p.wid)
			{
				if (f->piece[j][i] == '*' && count == turn)
				{
					f->p.pj = j;
					f->p.pi = i;
					return (1);
				}
				else if (f->piece[j][i] == '*' && count != turn)
					count++;
				i++;
			}
			j++;
		}
	return (0);
}

static int		save(t_filler *f, int j)
{
	int relaty;
	int relatx;

	while (j < f->p.stars)
	{
		relaty = f->p.relat_coor[j][0];
		relatx = f->p.relat_coor[j][1];
		f->p.anchor.heat += f->heatmap[f->mapy + relaty][f->mapx + relatx];
		j++;
	}
	if ((f->p.tmpsave.heat == 0 || f->p.anchor.heat < f->p.tmpsave.heat)
			|| (f->p.anchor.heat == f->p.tmpsave.heat
				&& f->p.anchor.star > f->p.tmpsave.star))
	{
		f->p.tmpsave = f->p.anchor;
		ft_bzero(&f->p.anchor, sizeof(t_anchor));
	}
	return (0);
}

static int		try_piece(t_filler *f)
{
	int turn;

	f->p.pi = 0;
	f->p.pj = 0;
	turn = 0;
	while (check_stars(f, turn) == 1)
	{
		ft_bzero(&f->p.anchor, sizeof(t_anchor));
		set_init_anchors(f, turn);
		if (check_placement(f) == 1)
			save(f, 1);
		turn++;
	}
	return (0);
}

int				solver(t_filler *f)
{
	ft_bzero(&f->p.tmpsave, sizeof(t_anchor));
	f->mapy = 0;
	while (f->mapy < f->hmap)
	{
		f->mapx = 0;
		while (f->mapx < f->wmap)
		{
			if (f->map[f->mapy][f->mapx] == f->my_id
					|| f->map[f->mapy][f->mapx] == f->my_id + 32)
				if (try_piece(f) == -1)
					return (-1);
			f->mapx++;
		}
		f->mapy++;
	}
	f->final_y = f->p.tmpsave.py;
	f->final_x = f->p.tmpsave.px;
	return (0);
}
