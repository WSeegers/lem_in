/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   issue_orders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 08:29:18 by wseegers          #+#    #+#             */
/*   Updated: 2018/06/15 02:58:17 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "s_list.h"
#include "f_memory.h"

static t_lemming	*create_lemming(size_t no, t_graph *orders, size_t delay)
{
	t_lemming *lem;

	lem = (t_lemming*)f_memalloc(sizeof(*lem));
	lem->number = no;
  	lem->delay = delay;
	lem->orders = s_list_copy(orders);	
	return (lem);
}

void				issue_orders(t_env *env, t_list *paths)
{
	t_lemming *new_lem;
	size_t lem_no;
	size_t delay;

	lem_no = -1;
	delay = -1;

	while (++lem_no < env->lem_no)
	{
		if (!(lem_no % paths->size))
			++delay;
		new_lem = create_lemming(lem_no, 
				s_list_get(paths, lem_no % paths->size),
				delay);
		s_list_append(env->lems, new_lem);
	}
}
