/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 21:45:21 by wseegers          #+#    #+#             */
/*   Updated: 2018/06/23 22:00:29 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "f_io.h"
#include "f_memory.h"
#include "s_list.h"
#include "f_string.h"
#include "f_print.h"

static int	check_for_command(t_env *env, char *line, int count)
{
	if (f_strstr(line, CMD_START))
	{
		if (env->start != NOT_SPEC)
			E_DSTART;
		env->start = count;
		f_printf("%s\n", line);
		return (1);
	}	
	else if (f_strstr(line, CMD_END))
	{
		if (env->target != NOT_SPEC)
			E_DEND;
		env->target = count;
		f_printf("%s\n", line);
		return (1);
	}
	else if (line[0] == '#')
	{
		f_printf("%s\n", line);
		return (1);
	}
	return (0);
}

static void	parse_neighbours(t_env *env, char* line)
{
	char	**split;
	int		i;

	i = 1;
	while (i || f_next_line(&line, STDIN))
	{
		f_printf("%s\n", line);
		i = 0;
		if (!f_strlen(line) || check_for_command(env, line, -1))
		{
			f_strdel(&line);
			continue ;
		}
		split = f_strsplit(line, '-');
		s_vert_add_adj(s_vert_by_name(env->map, split[0]), 
										s_vert_by_name(env->map, split[1]), 1);
		s_vert_add_adj(s_vert_by_name(env->map, split[1]), 
										s_vert_by_name(env->map, split[0]), 1);
		f_strarrdel(split);
	}
	return ;
}

void		parse_graph(t_env *env)
{
	char	*line;
	char	**split;
	int		count;

	count = 0;
	while (f_next_line(&line, STDIN) && !f_strchr(line, '-'))
	{
		if (check_for_command(env, line, count))
		{
			f_strdel(&line);
			continue ;
		}
		split = f_strsplit(line, ' ');
		s_graph_add_vert(env->map, s_vert_create(f_strdup(split[0])));
		f_strarrdel(split);
		count++;
		f_printf("%s\n", line);
		f_strdel(&line);
	}
	if (env->map->size < 2)
		E_ROOMS;
	if (env->start == NOT_SPEC || env->target == NOT_SPEC)
		E_NODEF;
	parse_neighbours(env, line);
	f_strdel(&line);
	env->node_no = count;
}
