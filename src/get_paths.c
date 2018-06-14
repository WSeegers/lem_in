/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 04:00:45 by wseegers          #+#    #+#             */
/*   Updated: 2018/06/14 08:10:29 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "f_print.h"
#include "s_graph.h"
#include "s_list.h"
#include <stdbool.h>

bool 	chk_conflicts(t_env *env, t_list *path_list, t_graph *new_path);
void	weigh_path(t_graph *path, long weight);

static bool has_conflict(t_graph *g1, t_graph *g2)
{
	size_t i;
	size_t j;
	
	f_printf("\nhas_conflict\n");
		s_graph_print_verts(g1);
	f_printf("\n");
		s_graph_print_verts(g2);
	f_printf("\n");
	i = 0;
	while (++i < g1->size - 1)
	{
		j = 0;
		while (++j < g2->size - 1)
		{
			f_printf("%s vs %s\n", s_vert_get(g1, i)->name, s_vert_get(g2, j)->name);
			if (s_vert_get(g1, i) == s_vert_get(g2, j))
				return (true);
		}
	}
	return (false);
}

static bool resolve_conflicts(t_env *env, t_list *path_list, t_graph *conflict,
											t_graph *new_path)
{
	t_graph *next_path;
	bool	resolve;
	size_t	i;

	next_path = dijkstra(s_vert_get(env->map, env->start),
							s_vert_get(env->map, env->target));
	weigh_path(next_path, PATH_WEIGHT);
	s_graph_reset_path(env->map);
	//if (chk_conflicts(env, path_list, next_path))
	//	return (false);
	//weigh_path(next_path, 0);
	//weigh_path(conflict, 0);
	//weigh_path(new_path, 0);
	f_printf("conflict: ");
		s_graph_print_verts(conflict);
	f_printf("\n");
	f_printf("new path: ");
		s_graph_print_verts(new_path);
	f_printf("\n");
	f_printf("next path:");
		s_graph_print_verts(next_path);
	f_printf("\n");
	if (!has_conflict(next_path, conflict) && (resolve = true))
		s_list_append(path_list, conflict);
	else if (!has_conflict(next_path, new_path) && (resolve = true))
		s_list_append(path_list, new_path);
	if (resolve)
		s_list_append(path_list, next_path);
	else
		s_list_append(path_list, conflict);
	i = -1;
	//while (++i < path_list->size)
		//weigh_path((t_graph*)s_list_get(path_list, i), PATH_WEIGHT);
	return (resolve);
}

bool chk_conflicts(t_env *env, t_list *path_list, t_graph *new_path)
{
	size_t i;
	t_graph *conflict;
	bool	had_conflict;

	f_printf("checking conflicts...");
	if (!path_list->size)
	{
		s_list_append(path_list, new_path);
		return (false);
	}
	i = -1;
	had_conflict = false;
	while (++i < path_list->size)
		if (has_conflict(((t_graph*)s_list_get(path_list, i)), new_path))
		{
			conflict = (t_graph*)s_list_pop(path_list, i);
			if(!resolve_conflicts(env, path_list, conflict, new_path))
				return (true);
		}
	if (!had_conflict)
		s_list_append(path_list, new_path);
	return (false);
}

void	weigh_path(t_graph *path, long weight)
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

t_list		*get_paths(t_env *env)
{
	t_list	*path_list;
	t_graph	*new_path;
	int 	i;

	path_list = s_list_create(NULL);
	i = -1;
	while (++i >= 0)
	{
		new_path = dijkstra(s_vert_get(env->map, env->start),
									s_vert_get(env->map, env->target));
		weigh_path(new_path, PATH_WEIGHT);
		s_graph_reset_path(env->map);
		
		f_printf("new_path: ");
		s_graph_print_verts(new_path);
		f_printf("\n");

		if(chk_conflicts(env, path_list, new_path))
		{
			f_printf("no more paths\n");
			return (path_list);
		}
		f_printf("resolved\n");
	}
	return (path_list);
}
