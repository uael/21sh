/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/word.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_WORD_H
# define USH_WORD_H
# include "var.h"
# include "tok.h"

extern void		sh_wordexplode(t_vec *av, char const *src, size_t n);
extern size_t	sh_wordresolve(t_sds *d, char const *s, size_t n, uint8_t *e);

#endif
