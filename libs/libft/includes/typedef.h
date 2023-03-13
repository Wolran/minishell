/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 20:11:09 by troberts          #+#    #+#             */
/*   Updated: 2022/10/04 20:12:14 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# ifndef T_LIST
#  define T_LIST

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

# endif

# ifndef T_BOOL
#  define T_BOOL

typedef enum e_bool
{
	false = 0,
	true = 1
}	t_bool;

# endif
#endif