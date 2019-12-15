/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info_fetcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 10:57:03 by dapinto           #+#    #+#             */
/*   Updated: 2019/07/04 15:25:37 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	extract_map_size(t_filler *f, char *mapsizeline)
{
	char	*ptr;

	ptr = ft_strchr(mapsizeline, ' ') + 1;
	if (ptr)
		f->hmap = ft_atoi(ptr);
	ptr = ft_strchr(ptr, ' ') + 1;
	if (ptr)
		f->wmap = ft_atoi(ptr);
	if (f->hmap <= 0 || f->wmap <= 0)
		return (-1);
	return (0);
}

int			get_map_size(t_filler *f)
{
	if (get_next_line(STDIN_FILENO, &f->line) > 0)
	{
		if (!ft_strstr(f->line, "Plateau")
				|| ft_str_nb_of_target(f->line, " ") != 2)
		{
			ft_strdel(&f->line);
			return (-1);
		}
		else
		{
			if (extract_map_size(f, f->line) < 0)
			{
				ft_strdel(&f->line);
				return (-1);
			}
			ft_strdel(&f->line);
			return (0);
		}
		ft_strdel(&f->line);
	}
	return (-1);
}
