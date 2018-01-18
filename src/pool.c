/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/pool.h"

static t_vec	g_pools_stack = { NULL, sizeof(t_pool), 0, 0 };
static t_vec	*g_pools = &g_pools_stack;
t_pool			*g_pool = NULL;
size_t			g_scopelvl = 0;

inline void		sh_poolscope(void)
{
	g_pool = ft_vecpush(g_pools);
	g_scopelvl = g_pools->len;
}

/*
** TODO: check for running jobs
*/

inline t_bool	sh_poolunscope(void)
{
	if (g_pool && ft_vecpop(g_pools, NULL))
	{
		g_scopelvl = g_pools->len;
		return (1);
	}
	g_scopelvl = g_pools->len;
	ft_vecdtor(g_pools, NULL);
	return (0);
}

inline t_job	*sh_poolpush(t_job *job)
{
	size_t	i;
	t_job	*new;
	t_proc	*proc;

	if (g_pool->len == CHILD_MAX)
		return (NULL);
	new = ft_memcpy(g_pool->jobs + g_pool->len++, job, sizeof(t_job));
	sh_joblaunch(new, 0);
	ft_putf(STDOUT_FILENO, "[%d] ", g_pools->len);
	i = 0;
	while (i < job->processes.len)
	{
		proc = job->processes.buf + i++;
		ft_putf(STDOUT_FILENO, i < job->processes.len ? "%d " : "%d",
			proc->pid);
	}
	ft_putf(STDOUT_FILENO, "\n");
	return (new);
}

inline t_job	*sh_poolfind(pid_t pgid)
{
	size_t	i;
	t_job	*job;

	if (!g_pool)
		return (NULL);
	i = 0;
	while (i < g_pool->len)
		if ((job = g_pool->jobs + i++)->pgid == pgid)
			return (job);
	return (NULL);
}
