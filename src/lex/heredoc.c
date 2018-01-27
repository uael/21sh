/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/lex.h"

#define UXPTDEOF "Unexpected EOF while looking for heredoc delimiter `%s'"

inline int			sh_lexheredoc(int fd, t_tok *tok, char **it, char **ln)
{
	char	*eof;
	size_t	eofl;
	int		st;

	eofl = tok->len;
	eof = ft_memdup(tok->val, (tok->len + 1) * sizeof(char));
	tok->len = 0;
	while (1)
		if (!**it && (st = fd < 0 ? NOP : rl_catline(fd, 0, ln, it)))
			return (st < 0 ? WUT : sh_synerr(*ln, *it, "Unexpected "
				"EOF while looking for heredoc delimiter `%s'", eof)); // todo: free
		else if (*ft_sdscpush((t_sds *)tok, *(*it)++) == '\n' && tok->len >=
			eofl + 1 && (*(*it - (eofl + 2)) == '\n' ||
			(*it - (eofl + 1)) == *ln) &&
			!ft_strncmp(*it - (eofl + 1), eof, eofl))
		{
			ft_sdsnpop((t_sds *)tok, eofl + 1, NULL);
			break ;
		}
	free(eof);
	return (YEP);
}

inline int			sh_lexheredoct(int fd, t_tok *tok, char **it, char **ln)
{
	char	*eof;
	size_t	eofl;
	int		st;

	eofl = tok->len;
	eof = ft_memdup(tok->val, (tok->len + 1) * sizeof(char));
	tok->len = 0;
	while (1)
	{
		if (!**it && (st = fd < 0 ? NOP : rl_catline(fd, 0, ln, it)))
			return (st < 0 ? WUT : sh_synerr(*ln, *it, UXPTDEOF, eof)); // todo: free
		if (*(*it - 1) == '\n')
			while (**it == '\t')
				++*it;
		if (*ft_sdscpush((t_sds *)tok, *(*it)++) == '\n' && tok->len >=
			eofl + 1 && (*(*it - (eofl + 2)) == '\n' ||
			(*it - (eofl + 1)) == *ln) &&
			!ft_strncmp(*it - (eofl + 1), eof, eofl))
		{
			ft_sdsnpop((t_sds *)tok, eofl + 1, NULL);
			break ;
		}
	}
	free(eof);
	return (YEP);
}
