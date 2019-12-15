/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece_check_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 11:16:03 by dapinto           #+#    #+#             */
/*   Updated: 2019/07/18 13:29:25 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	count_stars(t_filler *f)
{
	int j;
	int count;

	j = 0;
	count = 0;
	while (j < f->p.hei)
	{
		count += ft_str_nb_of_target(f->piece[j], "*");
		j++;
	}
	return (count);
}

static int	make_piece(char *pieceline, int i, t_filler *f)
{
	if (i == 0)
	{
		if (!(f->piece = malloc(sizeof(char *) * f->p.hei + 1)))
			return (-1);
		f->piece[f->p.hei] = NULL;
		if (!(f->piece[i] = ft_strdup(pieceline)))
			return (-1);
	}
	else if (!(f->piece[i] = ft_strdup(pieceline)))
		return (-1);
	return (0);
}

static int	checker(t_filler *f, int i)
{
	char	*ptr;

	ptr = f->line;
	if (ft_nchrchck(f->line, ".*", f->p.wid + 1) != -1
			&& ft_strlen(f->line) == (size_t)f->p.wid)
	{
		if (ft_nchrchck(ptr, ".*", f->p.wid))
		{
			if (make_piece(ptr, i, f) == -1)
				return (-1);
			return (1);
		}
		return (-1);
	}
	return (-1);
}

int			check_and_store_piece(t_filler *f)
{
	int i;
	int err;

	i = 0;
	while (i < f->p.hei && (err = get_next_line(STDIN_FILENO, &f->line)) > 0
			&& (err = checker(f, i)) > 0)
	{
		ft_strdel(&f->line);
		i++;
	}
	if (err < 0)
	{
		ft_tabdel(i, &f->piece);
		ft_strdel(&f->line);
		return (-1);
	}
	ft_strdel(&f->line);
	f->p.stars = count_stars(f);
	return (0);
}
