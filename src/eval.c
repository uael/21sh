/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/22 13:39:06 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

#define UNEX "1: Unexpected token `%s'"

static t_map		g_binaries_stack =
{
	0, 0, 0, 0, NULL, { (t_hashfn *)ft_strhash, (t_eqfn *)ft_streq },
	sizeof(char *), sizeof(char *), NULL, NULL
};
t_map				*g_binaries = &g_binaries_stack;

inline void			sh_evaldtor(void)
{
	ft_mapdtor(g_binaries, (t_dtor)ft_pfree, (t_dtor)ft_pfree);
}

static inline int	evalfini(int ret, t_deq *toks)
{
	t_tok	*tok;

	if (ret > 0)
	{
		tok = sh_tokpeek(toks);
		while (tok)
			if (tok->id != TOK_EOL && tok->id != TOK_END)
				tok = sh_toknext(toks);
			else
			{
				sh_toknext(toks);
				break ;
			}
		return (NOP);
	}
	return (YEP);
}

inline int			sh_eval(int fd, t_deq *toks, char **ln)
{
	t_tok	*tok;
	int		st;

	st = 0;
	while (!st)
	{
		if (!(tok = sh_tokpeek(toks)))
			return (evalfini(YEP, toks));
		while (tok && tok->id == TOK_EOL)
			tok = sh_toknext(toks);
		if (!sh_tokpeek(toks))
			return (evalfini(YEP, toks));
		if ((st = sh_evallist(fd, toks, ln)) == OUF)
			return (evalfini(NOP, toks));
		if (!(tok = sh_tokpeek(toks)))
			return (evalfini(YEP, toks));
		if (tok->id == TOK_SEMICOLON)
			sh_toknext(toks);
		else if (tok->id == TOK_END)
			return (evalfini(YEP, toks));
		else if (tok->id == TOK_EOL && st)
			st = 0;
	}
	tok = sh_tokpeek(toks);
	return (evalfini(sh_evalerr(*ln, tok, UNEX, sh_tokstr(tok)), toks));
}
