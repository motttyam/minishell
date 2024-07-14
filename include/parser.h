/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:04:47 by yoshiminaok       #+#    #+#             */
/*   Updated: 2024/07/14 22:09:12 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_command
{
	char	**argv;
	int		count;
    int     redirect_flag;
    t_fd    fd;
}			t_command;

int		redirect(t_token **ptr);

#endif