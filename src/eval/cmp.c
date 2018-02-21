/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/cmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

#define UEH "Expected `<filename>' got `%s'"

inline int			sh_evalcmp(t_job *job, t_deq *toks, char **ln)
{
	t_tok	*tok;
	t_proc	*proc;
	t_redir	r;
	t_tok	*op;
	char	buf[PATH_MAX];

	op = sh_tokpeek(toks);
	if (!(tok = sh_toknext(toks)) || !TOK_ISWORD(tok->id))
		return (sh_evalerr(*ln, tok, UEH, sh_tokstr(tok)));
	if (!sh_redirword(job, buf, toks, *ln))
		return (YEP);
	proc = ft_vecback((t_vec *)&job->procs);
	if ((r.to = open(buf, O_RDWR | O_CREAT, 0644)) < 0)
	{
		ps_procerr(proc, ft_strcat(ft_strcat(buf, ": "),
			ft_strerr(errno)), *ln, tok->pos);
		return (YEP);
	}
	r.from = ft_isdigit(*(*ln + op->pos)) ? *(*ln + op->pos) - '0' : 0;
	*(t_redir *)ft_vecpush((t_vec *)&proc->redirs) = r;
	return (YEP);
}
