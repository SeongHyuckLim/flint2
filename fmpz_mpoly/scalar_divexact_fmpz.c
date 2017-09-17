/*
    Copyright (C) 2016 William Hart

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include <gmp.h>
#include <stdlib.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_mpoly.h"

void _fmpz_mpoly_scalar_divexact_fmpz(fmpz * poly1, ulong * exps1,
  const fmpz * poly2, const ulong * exps2, slong len2, slong N, const fmpz_t c)
{
   slong i;

   for (i = 0; i < len2; i++)
      fmpz_divexact(poly1 + i, poly2 + i, c);

   if (exps1 != exps2)
      mpn_copyi(exps1, exps2, N*len2);
}

void fmpz_mpoly_scalar_divexact_fmpz(fmpz_mpoly_t poly1,
          const fmpz_mpoly_t poly2, const fmpz_t c, const fmpz_mpoly_ctx_t ctx)
{
   slong N;

   if (fmpz_is_zero(c))
   {
      _fmpz_mpoly_set_length(poly1, 0, ctx);
      return;
   }

   N = words_per_exp(ctx->n, poly2->bits);

   fmpz_mpoly_fit_length(poly1, poly2->length, ctx);
   fmpz_mpoly_fit_bits(poly1, poly2->bits, ctx);

   _fmpz_mpoly_scalar_divexact_fmpz(poly1->coeffs, poly1->exps, 
                         poly2->coeffs, poly2->exps, poly2->length, N, c);
      
   _fmpz_mpoly_set_length(poly1, poly2->length, ctx);
   poly1->bits = poly2->bits;
}
