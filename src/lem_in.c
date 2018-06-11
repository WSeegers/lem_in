/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 09:50:57 by wseegers          #+#    #+#             */
/*   Updated: 2018/06/11 13:27:55 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "f_print.h"
#include "s_list.h"
#include "s_vertex.h"

int		main(void)
{
	t_env	*env;

	env = parse_env();
	for (size_t i = 0; i < env->node_no; i++)
	{
		f_printf("%s\n", ((t_vert*)s_list_pop(env->map->vert_list, 0))->name);
	}
	return (0);
}
