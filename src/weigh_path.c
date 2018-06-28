/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weigh_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 22:31:21 by wseegers          #+#    #+#             */
/*   Updated: 2018/06/28 22:32:59 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		weigh_path(t_graph *path, long weight)
{
	size_t	i;
	t_vert	*cur;
	t_vert	*prev;

	i = -1;
	prev = NULL;
	while (++i < path->size)
	{
		cur = s_vert_get(path, i);
		if (prev)
			s_vert_set_cost(prev, cur, weight);
		prev = cur;
	}
}
