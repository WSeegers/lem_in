/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 09:50:24 by wseegers          #+#    #+#             */
/*   Updated: 2018/06/14 15:01:41 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "s_list.h"
# include "s_graph.h"
# include "s_dstr.h"

# define CMD_START	"##start"
# define CMD_END	"##end"

# define PATH_WEIGHT 2

typedef struct	s_lemming
{
	size_t	number;
	size_t	delay;
	s_list	*orders;	
}				t_lemming;

typedef struct 	s_env
{
	t_graph 	*map;
	size_t		start;
	size_t		target;
	size_t		node_no;

	t_list		*lems;
	size_t		lem_no;

}				t_env;

t_env		*parse_env(void);
void		parse_graph(t_env *env);
t_list		*get_paths(t_env *env);

#endif
