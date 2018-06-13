/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 09:50:57 by wseegers          #+#    #+#             */
/*   Updated: 2018/06/13 11:26:13 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lem_in.h"
#include "f_print.h"
#include "s_list.h"
#include "s_vertex.h"

int		main(void)
{
	t_env	*env;
	t_vert	*target;
	t_vert	*start;
	t_vert	*temp;
	size_t 	i;

	env = parse_env();
	start = s_vert_get(env->map->vert_list, env->start);
	target = s_vert_get(env->map->vert_list, env->target);
	f_printf("start: %s\n", start->name);
	f_printf("target: %s\n", target->name);
	f_printf("dijkstra started..");
	dijkstra(start, target);
	f_printf("dijkstra ended\n");
	i = -1;
	/*while (++i < env->map->vert_list->size)
	{
		temp = s_vert_get(env->map->vert_list, i);
		if (temp->parent)
			f_printf("target: %s -> parent: %s\n",temp->name, temp->parent->name);
	}*/
	f_printf(target->name);
	temp = target->parent;
	while (temp)
	{
		f_printf("<-%s",temp->name);
		temp = temp->parent;
	}
	f_printf("\n");

	exit (0);
}
