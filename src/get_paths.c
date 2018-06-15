/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 04:00:45 by wseegers          #+#    #+#             */
/*   Updated: 2018/06/15 05:23:04 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "f_print.h"
#include "s_graph.h"
#include "s_list.h"
#include <stdbool.h>

static bool chk_conflicts(t_env *env, t_list *path_list, t_graph *new_path,
		bool first_check);

static bool has_conflict(t_graph *g1, t_graph *g2)
{
	size_t i;
	size_t j;
	
	//f_printf("\nhas_conflict\n");
		//s_graph_print_verts(g1);
	//f_printf("\n");
		//s_graph_print_verts(g2);
	//f_printf("\n");
	i = 0;
	while (++i < g1->size - 1)
	{
		j = 0;
		while (++j < g2->size - 1)
		{
			//f_printf("%s vs %s\n", s_vert_get(g1, i)->name, s_vert_get(g2, j)->name);
			if (s_vert_get(g1, i) == s_vert_get(g2, j))
				return (true);
		}
	}
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

static bool resolve_conflicts(t_env *env, t_list *path_list, t_graph *conflict,
											t_graph *new_path)
{
	t_graph *next_path;
	bool	resolve;
	size_t	i;
	t_graph *delme;

	next_path = dijkstra(s_vert_get(env->map, env->start),
							s_vert_get(env->map, env->target));
	weigh_path(next_path, PATH_WEIGHT);
	s_graph_reset_path(env->map);
	//f_printf("conflict: ");
//		s_graph_print_verts(conflict);
//	f_printf("\n");
//	f_printf("new path: ");
//		s_graph_print_verts(new_path);
//	f_printf("\n");
//	f_printf("next path:");
//		s_graph_print_verts(next_path);
//	f_printf("\n\n");
	if (s_graph_equ(new_path, next_path))
	{
		s_list_append(path_list, conflict);
		return (false);
	}
	i = -1;
	while (++i < path_list->size)
		if (has_conflict(((t_graph*)s_list_get(path_list, i)), next_path))
		{
			s_list_append(path_list, conflict);
			return (false);
		}
	if (!has_conflict(next_path, conflict) && (resolve = true))
		s_list_append(path_list, conflict);
	else if (!has_conflict(next_path, new_path) && (resolve = true))
		s_list_append(path_list, new_path);
	if (resolve)
		s_list_append(path_list, next_path);
	else
		s_list_append(path_list, conflict);
	i = -1;
	weigh_path(next_path, 1);
	weigh_path(conflict, 1);
	weigh_path(new_path, 1);
	while (++i < path_list->size)
	{
//		f_printf("Reweigh-> ");
		weigh_path((delme = (t_graph*)s_list_get(path_list, i)), PATH_WEIGHT);
//		s_graph_print_verts(delme);
//		f_printf("\n");
	}
	return (resolve);
}

static bool chk_conflicts(t_env *env, t_list *path_list, t_graph *new_path, bool first_check)
{
	size_t i;
	t_graph *conflict;

	if (!path_list->size)
		return (false);

//	f_printf("Chk: ");
//	s_graph_print_verts(new_path);
//	f_printf("\n\n");

	i = -1;
	while (++i < path_list->size)
		if (has_conflict(((t_graph*)s_list_get(path_list, i)), new_path))
		{
			conflict = (t_graph*)s_list_pop(path_list, i);
			if(!resolve_conflicts(env, path_list, conflict, new_path))
				return (true);
			else
				return (false);
		}
//	f_printf("chk pass\n");
	if (first_check)
		s_list_append(path_list, new_path);
	return (false);
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
		if (!path_list->size)
			s_list_append(path_list, new_path);
		else if(chk_conflicts(env, path_list, new_path, true))
			return (path_list);
//		f_printf("\n\nI: %d \n", i);
//		for (size_t i = 0; i < path_list->size; i++)
//		{
//			s_graph_print_verts(s_list_get(path_list, i));
//			f_printf("\n");
//		}
//		f_printf("\n");
	}
	return (path_list);
}
