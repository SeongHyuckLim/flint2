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

    Copyright (C) 2011 Sebastian Pancratz

******************************************************************************/

#include <mpir.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpq.h"
#include "ulong_extras.h"

void fmpq_mul_fmpz(fmpq_t res, const fmpq_t op, const fmpz_t x)
{
    fmpz_t y;

    fmpz_init(y);
    fmpz_set_ui(y, 1);

    _fmpq_mul(fmpq_numref(res), fmpq_denref(res),
              fmpq_numref(op), fmpq_denref(op), x, y);

    fmpz_clear(y);
}
