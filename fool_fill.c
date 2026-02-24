/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fool_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:34:50 by rabdolho          #+#    #+#             */
/*   Updated: 2026/02/24 12:36:11 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

t_queue	*queue_create(int max_size)
{
	t_queue	*q;

	q = malloc(sizeof(t_queue));
	if (!q)
		return (NULL);
	q->x = malloc(sizeof(int) * max_size);
	q->y = malloc(sizeof(int) * max_size);
	if (!q->x || !q->y)
	{
		free(q->x);
		free(q->y);
		free(q);
		return (NULL);
	}
	q->head = 0;
	q->tail = 0;
	q->size = max_size;
	return (q);
}

int	queue_push(t_queue *q, int x, int y)
{
	if (q->tail >= q->size)
		return (0);
	q->x[q->tail] = x;
	q->y[q->tail] = y;
	q->tail++;
	return (1);
}

int	queue_pop(t_queue *q, int *x, int *y)
{
	if (q->head == q->tail)
		return (0);
	*x = q->x[q->head];
	*y = q->y[q->head];
	q->head++;
	return (1);
}

void	queue_free(t_queue *q)
{
	if (!q)
		return ;
	free(q->x);
	free(q->y);
	free(q);
}
