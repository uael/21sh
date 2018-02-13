/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_test_3000.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 00:30:12 by mc                #+#    #+#             */
/*   Updated: 2018/02/13 18:43:33 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUPER_TEST_3000
# define SUPER_TEST_3000

# include "minunit.h"
# include "ush.h"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <limits.h>

/*
** glob
*/
void test_env(void);
void test_glob(void);
void test_glob_match(void);

#endif
