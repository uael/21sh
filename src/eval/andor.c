/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/andor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

inline int		sh_evalandor(t_job *job, int fd, t_deq *toks, char **ln)
{
	t_tok *tok;
	t_job right;

	if (sh_evalpipeline(job, fd, toks, ln))
		return (NOP);
	while (1)
		if ((tok = sh_tokpeek(toks))->id == TOK_LAND)
		{
			while ((tok = sh_toknext(toks)))
				if (tok->id != TOK_EOL)
					break ;
			sh_jobctor(&right);
			if (sh_evalpipeline(&right, fd, toks, ln))
				return (sh_parseerr(*ln, tok, "Expected <pipeline> got `%s'",
					sh_tokstr(tok)));
			job->andor = ANDOR_AND;
			job->next = ft_memdup(&right, sizeof(t_job));
			job = job->next;
		}
		else if (tok->id == TOK_LOR)
		{
			while ((tok = sh_toknext(toks)))
				if (tok->id != TOK_EOL)
					break ;
			sh_jobctor(&right);
			if (sh_evalpipeline(&right, fd, toks, ln))
				return (sh_parseerr(*ln, tok, "Expected <pipeline> got `%s'",
					sh_tokstr(tok)));
			job->andor = ANDOR_OR;
			job->next = ft_memdup(&right, sizeof(t_job));
			job = job->next;
		}
		else
			return (YEP);
}
