/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 09:50:57 by wseegers          #+#    #+#             */
/*   Updated: 2018/06/15 08:06:09 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lem_in.h"
#include "f_print.h"
#include "s_list.h"
#include "s_graph.h"
#include "s_grid.h"

bool	walk(t_list *lems, size_t turn)
{
	size_t		lem_no;
	t_lemming	*cur;
	t_vert		*next_step;
	bool 		finished;

	finished = true;
	lem_no = -1;
	while (++lem_no < lems->size)
	{
		cur = (t_lemming*)s_list_get(lems, lem_no);
		if (cur->delay < turn && (next_step = s_list_pop(cur->orders, 0)))
		{
			finished = false;
			f_printf("L%d-%s ", cur->number, next_step->name);
		}
	}
	if (finished)
		return (false);
	f_printf("\n");
	return (true);
}

static int	chk_len(void *g1, void *g2)
{
	return(((t_graph*)g2)->size - ((t_graph*)g1)->size);
}

int		main(void)
{
	t_env	*env;
	t_list 	*paths;
	size_t	turn;

	env = parse_env();
	
	paths = get_paths(env);
	s_list_mergesort(paths, chk_len);
	//f_printf("\nFinal_paths:\n");
	//for (size_t i = 0; i < paths->size; i++)
	//{
	//	s_graph_print_verts(s_list_get(paths, i));
	//	f_printf("\n");
	//}
	issue_orders(env, paths);
	//f_printf("lem issued: %lu\n", env->lems->size);
	//for (size_t i = 0; i < env->lems->size; i++)
	//{
	//	t_lemming *temp = s_list_get(env->lems, 0);
	//	s_list_rot(env->lems, 1);
	//	f_printf("lem_no: %lu, delay: %lu, path, ", temp->number, temp->delay);
	//	s_graph_print_verts(temp->orders);
	//	f_printf("\n");
	//}
	turn = 0;
	while (walk(env->lems, ++turn))
		;
	exit (0);
}
