/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_BI_H
# define USH_BI_H

# include "proc.h"

extern t_procfn	*sh_bifn(char const *exe);

extern int		sh_biecho(int ac, char **argv, char **env);
extern int		sh_biexit(int ac, char **av, char **env);
extern int		sh_biunsetenv(int ac, char **av, char **env);
extern int		sh_bienv(int ac, char **av, char **env);
extern int		sh_bisetenv(int ac, char **av, char **env);
extern int		sh_bicd(int ac, char **av, char **env);
extern int		sh_biset(int ac, char **av, char **env);
extern int		sh_biunset(int ac, char **av);
extern int		sh_biexport(int ac, char **av, char **env);
extern int		sh_bibg(int ac, char **av, char **env);
extern int		sh_bifg(int ac, char **av, char **env);
extern int		sh_bijobs(int ac, char **av, char **env);

#endif
