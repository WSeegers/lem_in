/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 09:50:24 by wseegers          #+#    #+#             */
/*   Updated: 2018/06/23 21:33:59 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <limits.h>
# include "s_list.h"
# include "s_graph.h"
# include "s_dstr.h"

# define CMD_START	"##start"
# define CMD_END	"##end"
# define NOT_SPEC	ULONG_MAX

# define PATH_WEIGHT 4

# define E_LEMNO f_exit(0, "Error: Specify correctly the number of lem-ins\n")
# define E_NODEF f_exit(0, "Error: Start or end not specified\n")
# define E_ROOMS f_exit(0, "Error: Specify atleast 2 rooms\n")
# define E_DSTART f_exit(0, "Error: Double start\n");
# define E_DEND	f_exit(0, "Error: Double end\n");

typedef struct	s_lemming
{
	size_t	number;
	size_t	delay;
	t_list	*orders;	
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
void		issue_orders(t_env *env, t_list *paths);

#endif
