/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 10:07:28 by wseegers          #+#    #+#             */
/*   Updated: 2018/06/11 13:27:45 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "f_io.h"
#include "f_memory.h"
#include "s_list.h"
#include "f_string.h"
#include "f_print.h"

static void	parse_graph(t_env *env)
{
	char	*line;
	char	**split;
	t_vert	*vert;
	int		count;

	count = 0;
	while (f_next_line(&line, STDIN) && !f_strchr(line, '-'))
	{
		if (f_strstr(line, CMD_START))
		{
			env->start = count;
			f_printf("%s\n", line);
			f_strdel(&line);
			f_next_line(&line, STDIN);
		}	
		else if (f_strstr(line, CMD_END))
		{
			env->start = count;
			f_printf("%s\n", line);
			f_strdel(&line);
			f_next_line(&line, STDIN);
		}
		split = f_strsplit(line, ' ');
		f_printf("%s\n", split[0]);
		vert = s_vert_create(split[0]);
		s_graph_add_vert(env->map, vert);
		count++;
		f_strdel(&line);
		//f_printf("%s\n", line);
	}
	//parse_adj_nodes();
	env->node_no = count;
}

static void	del_lem(void* lem)
{
	f_memdel(&lem);
}

static void	init_env(t_env *env, size_t lem_no)
{
	env->map = s_graph_create();
	env->lemings = (t_lemings*)f_memalloc(sizeof(*env->lemings) * lem_no);
	env->lem_no = lem_no;
	while (--lem_no + 1)
		env->lemings[lem_no] = s_list_create(del_lem);
}

t_env		*parse_env(void)
{
	t_env	*env;
	char	*line;
	size_t	no_lem;

	env = (t_env*)f_memalloc(sizeof(*env));
	f_next_line(&line, STDIN);
	no_lem = f_atoi(line);
	f_strdel(&line);
	f_printf("%d\n", no_lem);
	init_env(env, no_lem);
	parse_graph(env);
	return (env);
}