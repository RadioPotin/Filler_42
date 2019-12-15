/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:49:02 by dapinto           #+#    #+#             */
/*   Updated: 2019/07/05 11:26:15 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		free_filler(t_filler *f)
{
	if (f->piece || f->map || f->heatmap || f->line || f->p.relat_coor)
	{
		if (f->line)
			ft_strdel(&f->line);
		if (f->piece)
			ft_tabdel(f->p.hei, &f->piece);
		if (f->map)
			ft_tabdel(f->hmap, &f->map);
		if (f->heatmap)
			ft_inttabdel(f->hmap, &f->heatmap);
		if (f->p.relat_coor)
			ft_inttabdel(f->p.stars, &f->p.relat_coor);
	}
	else
		return (0);
	return (0);
}
