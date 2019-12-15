/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:14:43 by dapinto           #+#    #+#             */
/*   Updated: 2019/07/18 14:50:57 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int		allocate_relative_coordinates(t_filler *f)
{
	int j;

	j = 0;
	if (!(f->p.relat_coor = malloc(sizeof(int *) * f->p.stars + 1)))
		return (-1);
	f->p.relat_coor[f->p.stars] = NULL;
	while (j < f->p.stars)
	{
		if (!(f->p.relat_coor[j] = malloc(sizeof(int) * 2)))
		{
			ft_inttabdel(j, &f->p.relat_coor);
			return (-1);
		}
		j++;
	}
	return (0);
}

static void		print_decision(t_filler f)
{
	ft_putnbr(f.final_y);
	ft_putchar(' ');
	ft_putnbr(f.final_x);
	ft_putchar('\n');
}

int				main(void)
{
	t_filler f;

	ft_bzero(&f, sizeof(t_filler));
	if (get_players(&f) < 0)
		return (-1);
	while (1)
	{
		if (get_map_size(&f) < 0 || check_and_store_map(&f) < 0
				|| get_piece_size(&f) < 0 || check_and_store_piece(&f) < 0)
			return (-1);
		if (make_heatmap(&f) < 0 || allocate_relative_coordinates(&f) < 0)
			return (-1);
		solver(&f);
		print_decision(f);
		free_filler(&f);
	}
	return (0);
}
