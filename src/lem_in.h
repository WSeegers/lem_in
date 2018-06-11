/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 09:50:24 by wseegers          #+#    #+#             */
/*   Updated: 2018/06/11 22:11:20 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "s_list.h"
# include "s_graph.h"
# include "s_dstr.h"

# define CMD_START	"##start"
# define CMD_END	"##end"

typedef t_list *t_lemings;

typedef struct 	s_env
{
	t_graph 	*map;
	size_t		start;
	size_t		end;
	size_t		node_no;

	t_lemings	*lemings;
	int			lem_no;

}				t_env;

t_env		*parse_env(void);
void		parse_graph(t_env *env);
t_dstr		*walk(t_env *env);

#endif
