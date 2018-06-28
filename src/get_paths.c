/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 04:00:45 by wseegers          #+#    #+#             */
/*   Updated: 2018/06/28 22:34:07 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "f_print.h"
#include "s_graph.h"
#include "s_list.h"
#include <stdbool.h>

static bool	has_conflict(t_graph *g1, t_graph *g2)
{
	size_t i;
	size_t j;

	i = 0;
	while (++i < g1->size - 1)
	{
		j = 0;
		while (++j < g2->size - 1)
			if (s_vert_get(g1, i) == s_vert_get(g2, j))
				return (true);
	}
	return (false);
}

static bool	chk_new_paths(t_list *path_list, t_graph *conflict,
									t_graph *new_path, t_graph *next_path)
{
	size_t i;

	if (s_graph_equ(new_path, next_path))
	{
		s_list_append(path_list, conflict);
		return (true);
	}
	i = -1;
	while (++i < path_list->size)
		if (has_conflict(((t_graph*)s_list_get(path_list, i)), next_path))
		{
			s_list_append(path_list, conflict);
			return (true);
		}
	return (false);
}

static bool	resolve_conflicts(t_env *env, t_list *path_list, t_graph *conflict,
											t_graph *new_path)
{
	t_graph *next_path;
	bool	resolve;
	size_t	i;

	next_path = dijkstra(s_vert_get(env->map, env->start),
							s_vert_get(env->map, env->target));
	weigh_path(next_path, PATH_WEIGHT);
	s_graph_reset_path(env->map);
	if (chk_new_paths(path_list, conflict, new_path, next_path))
		return (false);
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
		weigh_path((t_graph*)s_list_get(path_list, i), PATH_WEIGHT);
	return (resolve);
}

bool		chk_conflicts(t_env *env, t_list *path_list, t_graph *new_path,
															bool first_check)
{
	size_t	i;
	t_graph	*conflict;

	if (!path_list->size)
		return (false);
	i = -1;
	while (++i < path_list->size)
		if (has_conflict(((t_graph*)s_list_get(path_list, i)), new_path))
		{
			conflict = (t_graph*)s_list_pop(path_list, i);
			if (!resolve_conflicts(env, path_list, conflict, new_path))
				return (true);
			else
				return (false);
		}
	if (first_check)
		s_list_append(path_list, new_path);
	return (false);
}

t_list		*get_paths(t_env *env)
{
	t_list	*path_list;
	t_graph	*new_path;

	path_list = s_list_create(NULL);
	while (1)
	{
		new_path = dijkstra(s_vert_get(env->map, env->start),
									s_vert_get(env->map, env->target));
		weigh_path(new_path, PATH_WEIGHT);
		s_graph_reset_path(env->map);
		if (!path_list->size)
			s_list_append(path_list, new_path);
		else if (chk_conflicts(env, path_list, new_path, true))
			return (path_list);
		if (new_path->size == 2)
			return (path_list);
	}
	return (path_list);
}
