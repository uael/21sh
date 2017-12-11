/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/bi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/08 15:14:38 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/eval.h"

inline t_st	sh_eval_bi(t_sh *self, t_job **pjob, t_tok *tok)
{
	t_vstr		av;
	t_st		st;
	t_bi_fn		bi;
	t_job		job;
	t_job		hdoc;

	if (tok->id != SH_TOK_WORD)
		return (SH_NEXT);
	if (!(bi = sh_bi(ft_tok_ident(tok)->buf)))
		return (SH_NEXT);
	FT_INIT(&job, t_job);
	if (ISE(st = sh_exe_av(self, &av, ft_tok_ident(tok)->buf)))
		return (st);
	self->st = bi(self, (int)av.len, av.buf, &job);
	job.av ? 0 : sh_bi_job(&job, av.buf, self->env.buf);
	if ((tok = sh_skip(self, "\t ")) && tok->id == SH_TOK_HEREDOC)
	{
		sh_next(self, NULL);
		ft_job_output(&hdoc, ft_tok_ident(tok)->buf);
		if (!(*pjob = ft_worker_push(&self->worker, &hdoc)))
			return (ENO);
		ft_job_pipe(*pjob);
	}
	ft_job_data(&job, self);
	return ((*pjob = ft_worker_push(&self->worker, &job)) ? SH_OK : ENO);
}