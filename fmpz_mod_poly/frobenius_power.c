/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2014 William Hart

******************************************************************************/

#include <gmp.h>
#include "flint.h"
#include "ulong_extras.h"
#include "fmpz.h"
#include "fmpz_mod_poly.h"

void
fmpz_mod_poly_frobenius_power(fmpz_mod_poly_t res,
                            fmpz_mod_poly_frobenius_powers_2exp_t pow, 
                                              const fmpz_mod_poly_t f, ulong m)
{
    slong i = 0;
    ulong bit;
    fmpz_mod_poly_struct * r;
    fmpz_mod_poly_t tr;

    /* res = x^(p^0) = x */
    if (m == 0)
    {
       fmpz_mod_poly_set_coeff_ui(res, 1, 1);
       fmpz_mod_poly_set_coeff_ui(res, 0, 0);
       _fmpz_mod_poly_set_length(res, 2);
       if (f->length == 1)
          fmpz_mod_poly_rem(res, res, f);

       return;
    }

    if (res == f)
    {
       fmpz_mod_poly_init(tr, &f->p);
       r = tr;
    } else
       r = res;

    /* first nonzero bit */
    while ((m & (WORD(1) << i)) == 0)
       i++;

    /* res = f^(p^(2^i)) */
    fmpz_mod_poly_set(r, pow->pow + i);
    m ^= (WORD(1) << i);

    while (m != 0)
    {
       i++;
       
       bit = (WORD(1) << i);
       if ((bit & m) != 0)
       {
          fmpz_mod_poly_compose_mod(r, pow->pow + i, r, f);
          m ^= bit;
       }
    }

    if (res == f)
    {
       fmpz_mod_poly_swap(res, r);
       fmpz_mod_poly_clear(tr);
    }
}
