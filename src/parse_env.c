/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 10:07:28 by wseegers          #+#    #+#             */
/*   Updated: 2018/06/28 21:57:24 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "f_io.h"
#include "f_memory.h"
#include "s_list.h"
#include "f_string.h"
#include "f_print.h"

static void	del_lem(void *lem)
{
	f_memdel(&lem);
}

static void	init_env(t_env *env)
{
	char	*line;
	size_t	lem_no;
	int		ret;

	lem_no = 0;
	while ((ret = f_next_line(&line, STDIN)) && f_strchr(line, '#'))
	{
		f_printf("%s\n", line);
		f_strdel(&line);
	}
	if (ret == 0 || !f_isdigits(line) || !(lem_no = f_atoi(line)))
	{
		f_strdel(&line);
		E_LEMNO;
	}
	f_printf("%s\n", line);
	f_strdel(&line);
	env->map = s_graph_create();
	env->lem_no = lem_no;
	env->lems = s_list_create(del_lem);
	env->start = NOT_SPEC;
	env->target = NOT_SPEC;
}

t_env		*parse_env(void)
{
	t_env	*env;

	env = (t_env*)f_memalloc(sizeof(*env));
	init_env(env);
	parse_graph(env);
	return (env);
}
