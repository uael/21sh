/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh/shell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_SHELL_H
# define MSH_SHELL_H

# include "tokenize.h"

extern int	sh_process(int fd);
extern int	sh_exit(int exitno, char const *fmt, ...);

#endif
