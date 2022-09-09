/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_modify.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:27:38 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/09 16:41:17 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vector_GENERIC.h"

extern void		ft_bzero(void *s, size_t n);

static void	ft_memcpy(void *dest, const void *src, size_t nbyte)
{
	size_t				i;
	unsigned char		*u_dest;
	const unsigned char	*u_src;

	u_dest = dest;
	u_src = src;
	i = 0;
	while (i < nbyte)
	{
		u_dest[i] = u_src[i];
		++i;
	}
}

void	*vector_GENERIC_reserve(t_vector_GENERIC *vec, size_t new_capacity)
{
	void	*new_data;

	new_data = NULL;
	if (vec->capacity < new_capacity)
	{
		new_data = new_GENERIC_data_malloc(new_capacity);
		if (new_data != NULL)
		{
			ft_memcpy(new_data, vec->data, (vec->size * sizeof(t_GENERIC)));
			free(vec->data);
			vec->data = new_data;
			vec->capacity = new_capacity;
		}
	}
	return ((void *)(new_data));
}

void	*vector_GENERIC_shrink_to_fit(t_vector_GENERIC *vec)
{
	void	*shrinked_data;

	shrinked_data = NULL;
	if (vec->size < vec->capacity)
	{
		shrinked_data = new_GENERIC_data_malloc(vec->size);
		if (shrinked_data != NULL)
		{
			ft_memcpy(shrinked_data, vec->data, (vec->size * sizeof(t_GENERIC)));
			free(vec->data);
			vec->data = shrinked_data;
			vec->capacity = vec->size;
		}
	}
	return (shrinked_data);
}

void	vector_GENERIC_push_back(t_vector_GENERIC *vec, t_GENERIC data_in)
{
	void	*status;

	if (vec == NULL)
		return ;
	if (vec->size >= vec->capacity)
	{
		status = vector_GENERIC_reserve(vec, vec->capacity * 2);
		if (status == NULL)
			return ;
	}
	vector_GENERIC_set_data(vec, vec->size, data_in);
	(vec->size)++;
}

void	vector_GENERIC_pop_back(t_vector_GENERIC *vec)
{
	if (vec->size > 0)
	{
		ft_bzero(vec->get_last(vec), sizeof(t_GENERIC));
		(vec->size)--;
	}
}
