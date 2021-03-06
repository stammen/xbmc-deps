/* Linear search functions.
   Copyright (C) 1996,97,98,2002 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1996.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

/* Adapted for PlibC by Nils Durner */

#include <string.h>

#ifndef __COMPAR_FN_T
# define __COMPAR_FN_T
#define __const const
typedef int (*__compar_fn_t) (__const void *, __const void *);

typedef __compar_fn_t comparison_fn_t;
#endif

void *lfind (__const void *__key, __const void *__base,
        size_t *__nmemb, size_t __size, __compar_fn_t __compar);

void *
lsearch (const void *key, void *base, size_t *nmemb, size_t size,
	 __compar_fn_t compar)
{
  void *result;

  /* Try to find it.  */
  result = lfind (key, base, nmemb, size, compar);
  if (result == NULL)
    {
      /* Not available.  Insert at the end.  */
      result = memcpy (((char*)base) + (*nmemb) * size, key, size);
      ++(*nmemb);
    }

  return result;
}


void *
lfind (const void *key, const void *base, size_t *nmemb, size_t size,
       __compar_fn_t compar)
{
  const void *result = base;
  size_t cnt = 0;

  while (cnt < *nmemb && (*compar) (key, result) != 0)
    {
      ((char*)result) += size;
      ++cnt;
    }

  return cnt < *nmemb ? (void *) result : NULL;
}

