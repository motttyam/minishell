/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 23:16:28 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/08 00:17:47 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

void	fatal_error(const char *msg) __attribute__((noreturn));
void	handle_malloc_error(void);
void	quote_error(void);
#endif