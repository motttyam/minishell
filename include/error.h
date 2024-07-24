/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 23:16:28 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/24 20:21:54 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

void	fatal_error(const char *msg) __attribute__((noreturn));
void	handle_malloc_error(void);
void	quote_error(void);
void	put_error_message(char *argv, char *message);
#endif