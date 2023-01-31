/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:54:48 by vmuller           #+#    #+#             */
/*   Updated: 2023/01/30 19:28:32 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_token	t_token;
typedef struct s_pars	t_pars;

struct	s_token
{
	char	*line;
	char	*command;
	char	*text;
	int		flag;
	int		error;
	int		len_line;
	int		first;
};

struct	s_pars
{
	t_token	token;
};


#endif