/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_floats_pf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 20:27:15 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/01 16:11:10 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_set_flt(t_flt *flt, long long unsigned *primer)
{
	int		check;
	int		i;

	*primer = 2LLU << 62;
	while (*primer && !(*primer & flt->mant))
		*primer >>= 1;
	flt->curr_exp = flt->exp;
	flt->val_n = (int[6]){ -8192, -4096, 0, 4096, 8192, 16383 };
	i = 0;
	while (flt->curr_exp > flt->val_n[i])
		i++;
	flt->curr_exp = flt->val_n[i];
	check = i == 0 ? set_add_neg_8k(flt) : 0;
	i == 1 ? (check = set_add_neg_4k(flt)) : 0;
	i == 2 ? flt->add = ft_strdup("1") : 0;
	i == 2 && flt->add ? (check = 1) : 0;
	i == 3 ? (check = set_add_pos_4k(flt)) : 0;
	i == 4 ? (check = set_add_pos_8k(flt)) : 0;
	i == 5 ? (check = set_add_pos_16k(flt)) : 0;
	if (!((flt->val_l = ft_strdup("0"))
			&& (flt->val_r = ft_strdup("00"))))
		return (0);
	return (check);
}

int		trim_ret(t_flt *flt)
{
	int		pos;
	char	*trimmed;

	pos = ft_strlen(flt->val_r);
	while (flt->val_r[--pos] == '0' && pos > 1)
		flt->val_r[pos] = 0;
	pos = 0;
	while (flt->val_l[pos] == '0' && flt->val_l[pos + 1])
		pos++;
	if (!(trimmed = ft_strdup(flt->val_l + pos)))
		return (0);
	flt->val_l = trimmed;
	return (1);
}

int		ft_calc_flt(t_flt *flt)
{
	long long unsigned		primer;

	if (!(ft_set_flt(flt, &primer)))
		return (0);
	while (primer)
	{
		if (primer & flt->mant)
		{
			flt->curr_exp > flt->exp ? (flt->add = ft_strdiv(&flt->add
					, flt->curr_exp - flt->exp, -1, -1)) : 0;
			flt->curr_exp = flt->exp;
			if (flt->exp > -1)
				flt->val_l = ft_stradd(flt->val_l, flt->add);
			else
				flt->val_r = ft_stradd_fract(flt->val_r, flt->add);
			if (!flt->val_l || !flt->val_r)
				return (0);
		}
		primer >>= 1;
		--flt->exp ? 0 : (flt->curr_exp = 0);
		if (!flt->exp && !(flt->add = ft_strdup("1")))
			return (0);
	}
	return (trim_ret(flt));
}
