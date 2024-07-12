/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshiminaoki <yoshiminaoki@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:04:47 by yoshiminaok       #+#    #+#             */
/*   Updated: 2024/07/12 13:16:06 by yoshiminaok      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

typedef struct s_command
{
    char **argv;
    int count;
} t_command;
#endif