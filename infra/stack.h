#ifndef _LIBINFRA_STACK_H
#define _LIBINFRA_STACK_H

/*
 * Copyright 2024 (c) Adrien Ricciardi
 * This file is part of the libinfra distribution (https://github.com/rshadr/libinfra)
 * See LICENSE for details
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stddef.h>
#include <stdint.h>

typedef struct InfraStack_s {
  void **   items;
  int32_t   size;
  int32_t   capacity;
} InfraStack;


/*
 * C readability
 */
#define InfraStack(comptime_typename) InfraStack


InfraStack *infra_stack_create(void);
void infra_stack_free(InfraStack *stack);


static inline void *
infra_stack_peek(InfraStack *stack)
{
  if (stack == NULL || stack->size == 0)
    return NULL;

  return stack->items[stack->size - 1];
}


void *infra_stack_push(InfraStack *stack, void *item);


static inline void *
infra_stack_pop(InfraStack *stack)
{
  if (stack == NULL || stack->size == 0)
    return NULL;

  void *item = stack->items[stack->size - 1];

  /*
   * valgrind is just lining up for these steps
   */
  stack->items[stack->size - 1] = NULL;
  stack->size -= 1;

  return item;
}


#define INFRA_STACK_FOREACH(stack, index) \
  for (int index = 0; index < (stack)->size; index++)


#define INFRA_STACK_REVERSE_FOREACH(stack, index) \
  for (int index = (stack)->size - 1; index >= 0; index--)


static inline int
infra_stack_index(InfraStack const *stack, void const *item)
{
  INFRA_STACK_FOREACH(stack, i)
    if (stack->items[i] == item)
      return i;

  return -1;
}

void *infra_stack_remove(InfraStack *stack, void *item);

void infra_stack_insert(InfraStack *stack, int idx, void *item);


#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */


#endif /* _LIBINFRA_STACK_H */

