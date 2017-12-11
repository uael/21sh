/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/08 16:02:50 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/reduce.h"

inline t_st	sh_reduce(t_sh *self)
{
	t_sz	sz;
	t_tok	*tok;
	t_st	st;

	if (SZ_NOK(sz = ft_lexer_until(&self->lexer, '\n')))
		return (SZ_TOST(sz));
	tok = (t_tok *)ft_deq_begin(&self->lexer.toks) - 1;
	while (++tok != ft_deq_end(&self->lexer.toks))
		if (tok->id == SH_TOK_HEREDOC && !tok->val)
		{
			if (ISE(st = sh_reduce_heredoc(self, tok)))
				return (st);
		}
	return (OK);
}