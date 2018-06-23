/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 09:50:57 by wseegers          #+#    #+#             */
/*   Updated: 2018/06/23 22:18:56 by wseegers         ###   ########.fr       */
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
	f_printf("\n");
	paths = get_paths(env);
	s_list_mergesort(paths, chk_len);
	issue_orders(env, paths);
	turn = 1;
	while (walk(env->lems, turn))
		turn++;
	if (turn == 1)
		f_printf("No routes exist\n");
	exit (0);
}
