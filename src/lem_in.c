/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 09:50:57 by wseegers          #+#    #+#             */
/*   Updated: 2018/06/13 15:22:35 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lem_in.h"
#include "f_print.h"
#include "s_list.h"
#include "s_graph.h"

void	weigh_path(t_graph *path)
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
			s_vert_set_cost(prev, cur, 2);
		prev = cur;
	}
}

t_list	*get_paths(t_env *env)
{
	t_list	*paths;
	t_vert	*start;
	t_vert	*target;
	t_graph	*shrt_path;
	size_t 	i;

	paths = s_list_create(NULL);
	start = s_vert_get(env->map, env->start);
	target = s_vert_get(env->map, env->target);
	i = -1;
	while (1)
	{
		shrt_path = dijkstra(start, target);
		
		weigh_path(shrt_path);

		if (s_graph_equ(shrt_path, (t_graph*)s_list_get(paths, 0)))
			break;
		s_graph_print_verts(shrt_path);
		f_printf("\n");
		s_list_append(paths, shrt_path);
		s_graph_reset_path(env->map);
	}
	return (paths);
}

int		main(void)
{
	t_env	*env;
	t_list 	*paths;

	env = parse_env();
	paths = get_paths(env); 
	//paths = get_best_paths(paths);
	//issue_orders();
	exit (0);
}
