/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh/var.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_VAR_H
# define MSH_VAR_H

# include <libft.h>

extern void		sh_varctor(t_map *vars);
extern void		sh_vardtor(t_map *vars);
extern void		sh_varset(t_map *vars, char *var, char *val);
extern char		*sh_varget(t_map *vars, char *var);

#endif
