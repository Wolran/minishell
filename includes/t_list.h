/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:03:34 by troberts          #+#    #+#             */
/*   Updated: 2023/02/15 10:16:03 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_LIST_H
# define T_LIST_H

# define T_LIST

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

#endif