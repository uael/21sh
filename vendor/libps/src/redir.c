/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libps/redir.h"

inline int		ps_redirect(t_redirs *redirs, int *scope)
{
	size_t	i;
	t_redir	*redir;

	i = 0;
	while (i < redirs->len)
	{
		redir = redirs->buf + i++;
		if (scope && redir->from >= 0 && redir->from <= 2 &&
			scope[redir->from] < 0)
			scope[redir->from] = dup(redir->from);
	}
	i = 0;
	while (i < redirs->len)
	{
		redir = redirs->buf + i++;
		if (redir->to < 0 && close(redir->from))
			return (THROW(WUT));
		else if (redir->to >= 0 && dup2(redir->to, redir->from) < 0)
			return (THROW(WUT));
	}
	return (YEP);
}

inline void		ps_redirectclose(t_redirs *redirs)
{
	size_t	i;
	t_redir	*redir;

	i = 0;
	while (i < redirs->len)
		if ((redir = redirs->buf + i++)->to > 2)
			close(redir->to);
}
