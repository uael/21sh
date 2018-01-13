/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/var.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_VAR_H
# define USH_VAR_H

# include "env.h"

extern void		sh_scopepush(void);
extern t_bool	sh_scopepop(void);
extern void		sh_varset(char *var, char *val);
extern char		*sh_varget(char *var);

#endif