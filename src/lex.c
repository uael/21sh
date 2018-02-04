/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:28:05 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/lex.h"
#include "ush/shell.h"
#include "ush/tok.h"

#define UEB "parse error: Unexpected token `%c' while looking for matching `%c'"
#define UEE "parse error: Unexpected EOF while looking for matching `%c'"
#define UEC "parse error: Unexpected closing bracket `%c'"

static char			g_stk[1000] = { 0 };
static int			g_sidx;
t_deq				*g_lextoks;

static inline int	lexone(int fd, t_tok *tok, char **it, char **ln)
{
	int		st;

	while (1)
		if ((st = sh_lexbslash(fd, it, ln)))
			return (st);
		else if (**it && ft_strchr(sh_varifs(), **it))
			++*it;
		else if (ISEOL(*it))
			return ((sh_tokpos(tok, ++*it, *ln)->id = TOK_EOL) & 0);
		else if (**it == '#')
			while (**it && !ISEOL(*it))
				++*it;
		else if (!**it)
			return ((sh_tokpos(tok, *it, *ln)->id = TOK_END) & 0);
		else
			break ;
	sh_tokpos(tok, *it, *ln);
	ft_isdigit(**it) ? ft_sdscpush((t_sds *)tok, *(*it)++) : 0;
	return (st = sh_lexop(fd, tok, it, ln)) != NOP ||
	(st = sh_lexword(fd, tok, it, ln)) != NOP ? st :
	sh_synerr(*ln, *it, "Unexpected token `%c'", **it);
}

static inline int	lexline(int fd, t_deq *toks, char **it, char **ln)
{
	int		st;
	t_tok	*tok;

	!ln ? (ln = it) : 0;
	while (1)
	{
		tok = ft_deqpush(toks);
		tok->len = 0;
		tok->spec = 0;
		if ((st = lexone(fd, tok, it, ln)))
			return (st);
		if (tok->id == TOK_EOL || tok->id == TOK_END)
			break ;
		if (ft_strchr("([{`", tok->id) && (!g_sidx || g_stk[g_sidx - 1] != '`'))
			g_stk[g_sidx++] = sh_rbracket(tok->id);
		else if (g_sidx && tok->id == g_stk[g_sidx - 1])
			--g_sidx;
		else if (ft_strchr(")}]`", tok->id) &&
			(!g_sidx || tok->id != g_stk[g_sidx - 1]))
			return (g_sidx ? sh_synerr(*ln, *ln + tok->pos, UEB, tok->id,
				g_stk[g_sidx - 1]) : sh_synerr(*ln, *ln + tok->pos, UEC,
				tok->id));
	}
	return (YEP);
}

int					sh_lex(int fd, t_deq *toks, char **it, char **ln)
{
	int		st;
	size_t	sve;
	size_t	cur;

	if (!*it || !**it)
		return (NOP);
	g_sidx = 0;
	g_lextoks = toks;
	sve = toks->cur;
	while (1)
	{
		cur = toks->len;
		if ((st = lexline(fd, toks, it, ln)))
			return (st);
		toks->cur = cur;
		if ((st = sh_lexreduce(fd, toks, it, ln)))
			return (st);
		toks->cur = sve;
		if (!g_sidx)
			return (YEP);
		if (!**it && (fd < 0 || (st = rl_catline(fd, 0, ln, it))))
			return (st < 0 || !g_sh->tty ?
				sh_synerr(*ln, *it, UEE, g_stk[g_sidx - 1]) : OUF);
	}
}
