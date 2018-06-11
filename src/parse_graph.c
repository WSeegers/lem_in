/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 21:45:21 by wseegers          #+#    #+#             */
/*   Updated: 2018/06/11 22:18:38 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "f_io.h"
#include "f_memory.h"
#include "s_list.h"
#include "f_string.h"
#include "f_print.h"

/*static void	parse_neighbours(t_env *env)
{

}*/

static int	check_for_command(t_env *env, char *line, int count)
{
	if (f_strstr(line, CMD_START))
	{
		env->start = count;
		f_printf("%s\n", line);
		return (1);
	}	
	else if (f_strstr(line, CMD_END))
	{
		env->end = count;
		f_printf("%s\n", line);
		return (1);
	}
	return (0);
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
			//f_strdel(&line);
			continue ;
		}
		split = f_strsplit(line, ' ');
		s_graph_add_vert(env->map, s_vert_create(f_strdup(split[0])));
		//f_strarrdel(&split);
		count++;
		f_printf("%s\n", line);
		f_strdel(&line);
	}
	env->node_no = count;
}
