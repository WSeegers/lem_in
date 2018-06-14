/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 09:50:57 by wseegers          #+#    #+#             */
/*   Updated: 2018/06/14 15:01:43 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lem_in.h"
#include "f_print.h"
#include "s_list.h"
#include "s_graph.h"
#include "s_grid.h"

int		main(void)
{
	t_env	*env;
	t_list 	*paths;

	env = parse_env();
	
	paths = get_paths(env);
	f_printf("\nFinal_paths:\n");
	for (size_t i = 0; i < paths->size; i++)
	{
		s_graph_print_verts(s_list_get(paths, i));
		f_printf("\n");
	}
	issue_orders(env, paths);
	exit (0);
}
