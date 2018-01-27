/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/proc/err.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_PROC_ERR_H
# define USH_PROC_ERR_H

# include "../shell.h"

struct s_proc;

typedef struct	s_procerr
{
	int			st;
	char		*msg;
	char		*ln;
	size_t		pos;
}				t_procerr;

extern t_procerr	*sh_procerr(struct s_proc *pr, char *m, char *ln, size_t p);
extern int			sh_procerrlaunch(struct s_proc *prc);

#endif
