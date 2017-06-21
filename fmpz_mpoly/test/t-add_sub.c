/*
    Copyright (C) 2017 William Hart

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_mpoly.h"
#include "ulong_extras.h"

int
main(void)
{
    int i, j, result;
    FLINT_TEST_INIT(state);

    flint_printf("add/sub....");
    fflush(stdout);

    /* Check (f + g) - g = f */
    for (i = 0; i < 1000 * flint_test_multiplier(); i++)
    {
       fmpz_mpoly_ctx_t ctx;
       fmpz_mpoly_t f, g, h, k;
       ordering_t ord;
       slong nvars, len, exp_bound, coeff_bits, exp_bits;

       ord = mpoly_ordering_randtest(state);
       nvars = n_randint(state, 2) + 1;

       fmpz_mpoly_ctx_init(ctx, nvars, ord);

       fmpz_mpoly_init(f, ctx);
       fmpz_mpoly_init(g, ctx);
       fmpz_mpoly_init(h, ctx);
       fmpz_mpoly_init(k, ctx);

       len = n_randint(state, 2);

       exp_bits = n_randint(state, FLINT_BITS -
                     mpoly_ordering_isdeg(ord)*FLINT_BIT_COUNT(nvars) - 1) + 1;
       exp_bound = n_randbits(state, exp_bits);
       coeff_bits = n_randint(state, 200);

       fmpz_mpoly_randtest(f, state, len, exp_bound, coeff_bits, ctx);
       fmpz_mpoly_randtest(g, state, len, exp_bound, coeff_bits, ctx);
       fmpz_mpoly_randtest(h, state, len, exp_bound, coeff_bits, ctx);

       for (j = 0; j < 10; j++)
       {
          len = f->length;

          fmpz_mpoly_add(h, g, f, ctx);
             
          fmpz_mpoly_sub(k, h, g, ctx);

          result = fmpz_mpoly_equal(f, k, ctx);

          if (!result)
          {
             const char * vars[20];
             vars[0] = "x1", vars[1] = "x2", vars[2] = "x3", vars[3] = "x4",
             vars[4] = "x5", vars[5] = "x6", vars[6] = "x7", vars[7] = "x8",
             vars[8] = "x9", vars[9] = "x10", vars[10] = "x11", vars[11] = "x12",
             vars[12] = "x13", vars[13] = "x14", vars[14] = "x15", vars[15] = "x16",
             vars[16] = "x17", vars[17] = "x18", vars[18] = "x19", vars[19] = "x20";

             printf("FAIL\n");

             printf("ord = "); mpoly_ordering_print(ord);
             printf(", len = %ld, exp_bits = %ld, exp_bound = %lx, "
                                      "coeff_bits = %ld, nvars = %ld\n\n",
                                  len, exp_bits, exp_bound, coeff_bits, nvars);

             fmpz_mpoly_print_pretty(f, vars, ctx); printf("\n\n");
             fmpz_mpoly_print_pretty(g, vars, ctx); printf("\n\n");
             fmpz_mpoly_print_pretty(h, vars, ctx); printf("\n\n");
             fmpz_mpoly_print_pretty(k, vars, ctx); printf("\n\n");
          
             flint_abort();
          }
       }

       fmpz_mpoly_clear(f, ctx);  
       fmpz_mpoly_clear(g, ctx);  
       fmpz_mpoly_clear(h, ctx);  
       fmpz_mpoly_clear(k, ctx);  
    }

    /* Check f + g = g + f */
    for (i = 0; i < 1000 * flint_test_multiplier(); i++)
    {
       fmpz_mpoly_ctx_t ctx;
       fmpz_mpoly_t f, g, h, k;
       ordering_t ord;
       slong nvars, len, exp_bound, coeff_bits, exp_bits;

       ord = mpoly_ordering_randtest(state);
       nvars = n_randint(state, 2) + 1;

       fmpz_mpoly_ctx_init(ctx, nvars, ord);

       fmpz_mpoly_init(f, ctx);
       fmpz_mpoly_init(g, ctx);
       fmpz_mpoly_init(h, ctx);
       fmpz_mpoly_init(k, ctx);

       len = n_randint(state, 2);

       exp_bits = n_randint(state, FLINT_BITS -
                     mpoly_ordering_isdeg(ord)*FLINT_BIT_COUNT(nvars) - 1) + 1;
       exp_bound = n_randbits(state, exp_bits);
       coeff_bits = n_randint(state, 200);

       fmpz_mpoly_randtest(f, state, len, exp_bound, coeff_bits, ctx);
       fmpz_mpoly_randtest(g, state, len, exp_bound, coeff_bits, ctx);
       fmpz_mpoly_randtest(h, state, len, exp_bound, coeff_bits, ctx);
       fmpz_mpoly_randtest(k, state, len, exp_bound, coeff_bits, ctx);

       for (j = 0; j < 10; j++)
       {
          len = f->length;

          fmpz_mpoly_add(h, f, g, ctx);
             
          fmpz_mpoly_add(k, g, f, ctx);

          result = fmpz_mpoly_equal(h, k, ctx);

          if (!result)
          {
             const char * vars[20];
             vars[0] = "x1", vars[1] = "x2", vars[2] = "x3", vars[3] = "x4",
             vars[4] = "x5", vars[5] = "x6", vars[6] = "x7", vars[7] = "x8",
             vars[8] = "x9", vars[9] = "x10", vars[10] = "x11", vars[11] = "x12",
             vars[12] = "x13", vars[13] = "x14", vars[14] = "x15", vars[15] = "x16",
             vars[16] = "x17", vars[17] = "x18", vars[18] = "x19", vars[19] = "x20";

             printf("FAIL\n");

             printf("ord = "); mpoly_ordering_print(ord);
             printf(", len = %ld, exp_bits = %ld, exp_bound = %lx, "
                                      "coeff_bits = %ld, nvars = %ld\n\n",
                                  len, exp_bits, exp_bound, coeff_bits, nvars);

             fmpz_mpoly_print_pretty(f, vars, ctx); printf("\n\n");
             fmpz_mpoly_print_pretty(g, vars, ctx); printf("\n\n");
             fmpz_mpoly_print_pretty(h, vars, ctx); printf("\n\n");
             fmpz_mpoly_print_pretty(k, vars, ctx); printf("\n\n");
          
             flint_abort();
          }
       }

       fmpz_mpoly_clear(f, ctx);  
       fmpz_mpoly_clear(g, ctx);  
       fmpz_mpoly_clear(h, ctx);  
       fmpz_mpoly_clear(k, ctx);  
    }

    /* Check f - g = -g + f */
    for (i = 0; i < 1000 * flint_test_multiplier(); i++)
    {
       fmpz_mpoly_ctx_t ctx;
       fmpz_mpoly_t f, g, h, k;
       ordering_t ord;
       slong nvars, len, exp_bound, coeff_bits, exp_bits;

       ord = mpoly_ordering_randtest(state);
       nvars = n_randint(state, 2) + 1;

       fmpz_mpoly_ctx_init(ctx, nvars, ord);

       fmpz_mpoly_init(f, ctx);
       fmpz_mpoly_init(g, ctx);
       fmpz_mpoly_init(h, ctx);
       fmpz_mpoly_init(k, ctx);

       len = n_randint(state, 2);

       exp_bits = n_randint(state, FLINT_BITS -
                     mpoly_ordering_isdeg(ord)*FLINT_BIT_COUNT(nvars) - 1) + 1;
       exp_bound = n_randbits(state, exp_bits);
       coeff_bits = n_randint(state, 200);

       fmpz_mpoly_randtest(f, state, len, exp_bound, coeff_bits, ctx);
       fmpz_mpoly_randtest(g, state, len, exp_bound, coeff_bits, ctx);
       fmpz_mpoly_randtest(h, state, len, exp_bound, coeff_bits, ctx);
       fmpz_mpoly_randtest(k, state, len, exp_bound, coeff_bits, ctx);

       for (j = 0; j < 10; j++)
       {
          len = f->length;

          fmpz_mpoly_sub(h, f, g, ctx);
             
          fmpz_mpoly_neg(k, g, ctx);
          fmpz_mpoly_add(k, k, f, ctx);

          result = fmpz_mpoly_equal(h, k, ctx);

          if (!result)
          {
             const char * vars[20];
             vars[0] = "x1", vars[1] = "x2", vars[2] = "x3", vars[3] = "x4",
             vars[4] = "x5", vars[5] = "x6", vars[6] = "x7", vars[7] = "x8",
             vars[8] = "x9", vars[9] = "x10", vars[10] = "x11", vars[11] = "x12",
             vars[12] = "x13", vars[13] = "x14", vars[14] = "x15", vars[15] = "x16",
             vars[16] = "x17", vars[17] = "x18", vars[18] = "x19", vars[19] = "x20";

             printf("FAIL\n");

             printf("ord = "); mpoly_ordering_print(ord);
             printf(", len = %ld, exp_bits = %ld, exp_bound = %lx, "
                                      "coeff_bits = %ld, nvars = %ld\n\n",
                                  len, exp_bits, exp_bound, coeff_bits, nvars);

             fmpz_mpoly_print_pretty(f, vars, ctx); printf("\n\n");
             fmpz_mpoly_print_pretty(g, vars, ctx); printf("\n\n");
             fmpz_mpoly_print_pretty(h, vars, ctx); printf("\n\n");
             fmpz_mpoly_print_pretty(k, vars, ctx); printf("\n\n");
          
             flint_abort();
          }
       }

       fmpz_mpoly_clear(f, ctx);  
       fmpz_mpoly_clear(g, ctx);  
       fmpz_mpoly_clear(h, ctx);  
       fmpz_mpoly_clear(k, ctx);  
    }

    /* Check f + (g + h) = (f + g) + h */
    for (i = 0; i < 1000 * flint_test_multiplier(); i++)
    {
       fmpz_mpoly_ctx_t ctx;
       fmpz_mpoly_t f, g, h, k1, k2;
       ordering_t ord;
       slong nvars, len, exp_bound, coeff_bits, exp_bits;

       ord = mpoly_ordering_randtest(state);
       nvars = n_randint(state, 2) + 1;

       fmpz_mpoly_ctx_init(ctx, nvars, ord);

       fmpz_mpoly_init(f, ctx);
       fmpz_mpoly_init(g, ctx);
       fmpz_mpoly_init(h, ctx);
       fmpz_mpoly_init(k1, ctx);
       fmpz_mpoly_init(k2, ctx);

       len = n_randint(state, 2);

       exp_bits = n_randint(state, FLINT_BITS -
                     mpoly_ordering_isdeg(ord)*FLINT_BIT_COUNT(nvars) - 1) + 1;
       exp_bound = n_randbits(state, exp_bits);
       coeff_bits = n_randint(state, 200);

       fmpz_mpoly_randtest(f, state, len, exp_bound, coeff_bits, ctx);
       fmpz_mpoly_randtest(g, state, len, exp_bound, coeff_bits, ctx);
       fmpz_mpoly_randtest(h, state, len, exp_bound, coeff_bits, ctx);
       fmpz_mpoly_randtest(k1, state, len, exp_bound, coeff_bits, ctx);
       fmpz_mpoly_randtest(k2, state, len, exp_bound, coeff_bits, ctx);

       for (j = 0; j < 10; j++)
       {
          len = f->length;

          fmpz_mpoly_add(k1, f, g, ctx);
          fmpz_mpoly_add(k1, k1, h, ctx);
 
          fmpz_mpoly_add(k2, g, h, ctx);
          fmpz_mpoly_add(k2, k2, f, ctx);

          result = fmpz_mpoly_equal(k1, k2, ctx);

          if (!result)
          {
             const char * vars[20];
             vars[0] = "x1", vars[1] = "x2", vars[2] = "x3", vars[3] = "x4",
             vars[4] = "x5", vars[5] = "x6", vars[6] = "x7", vars[7] = "x8",
             vars[8] = "x9", vars[9] = "x10", vars[10] = "x11", vars[11] = "x12",
             vars[12] = "x13", vars[13] = "x14", vars[14] = "x15", vars[15] = "x16",
             vars[16] = "x17", vars[17] = "x18", vars[18] = "x19", vars[19] = "x20";

             printf("FAIL\n");

             printf("ord = "); mpoly_ordering_print(ord);
             printf(", len = %ld, exp_bits = %ld, exp_bound = %lx, "
                                      "coeff_bits = %ld, nvars = %ld\n\n",
                                  len, exp_bits, exp_bound, coeff_bits, nvars);

             fmpz_mpoly_print_pretty(f, vars, ctx); printf("\n\n");
             fmpz_mpoly_print_pretty(g, vars, ctx); printf("\n\n");
             fmpz_mpoly_print_pretty(h, vars, ctx); printf("\n\n");
             fmpz_mpoly_print_pretty(k1, vars, ctx); printf("\n\n");
             fmpz_mpoly_print_pretty(k2, vars, ctx); printf("\n\n");
          
             flint_abort();
          }
       }

       fmpz_mpoly_clear(f, ctx);  
       fmpz_mpoly_clear(g, ctx);  
       fmpz_mpoly_clear(h, ctx);  
       fmpz_mpoly_clear(k1, ctx);  
       fmpz_mpoly_clear(k2, ctx);  
    }

    /* Check f - (g + h) = (f - g) - h */
    for (i = 0; i < 1000 * flint_test_multiplier(); i++)
    {
       fmpz_mpoly_ctx_t ctx;
       fmpz_mpoly_t f, g, h, k1, k2;
       ordering_t ord;
       slong nvars, len, exp_bound, coeff_bits, exp_bits;

       ord = mpoly_ordering_randtest(state);
       nvars = n_randint(state, 2) + 1;

       fmpz_mpoly_ctx_init(ctx, nvars, ord);

       fmpz_mpoly_init(f, ctx);
       fmpz_mpoly_init(g, ctx);
       fmpz_mpoly_init(h, ctx);
       fmpz_mpoly_init(k1, ctx);
       fmpz_mpoly_init(k2, ctx);

       len = n_randint(state, 2);

       exp_bits = n_randint(state, FLINT_BITS -
                     mpoly_ordering_isdeg(ord)*FLINT_BIT_COUNT(nvars) - 1) + 1;
       exp_bound = n_randbits(state, exp_bits);
       coeff_bits = n_randint(state, 200);

       fmpz_mpoly_randtest(f, state, len, exp_bound, coeff_bits, ctx);
       fmpz_mpoly_randtest(g, state, len, exp_bound, coeff_bits, ctx);
       fmpz_mpoly_randtest(h, state, len, exp_bound, coeff_bits, ctx);
       fmpz_mpoly_randtest(k1, state, len, exp_bound, coeff_bits, ctx);
       fmpz_mpoly_randtest(k2, state, len, exp_bound, coeff_bits, ctx);

       for (j = 0; j < 10; j++)
       {
          len = f->length;

          fmpz_mpoly_add(k1, g, h, ctx);
          fmpz_mpoly_sub(k1, f, k1, ctx);
 
          fmpz_mpoly_sub(k2, f, g, ctx);
          fmpz_mpoly_sub(k2, k2, h, ctx);

          result = fmpz_mpoly_equal(k1, k2, ctx);

          if (!result)
          {
             const char * vars[20];
             vars[0] = "x1", vars[1] = "x2", vars[2] = "x3", vars[3] = "x4",
             vars[4] = "x5", vars[5] = "x6", vars[6] = "x7", vars[7] = "x8",
             vars[8] = "x9", vars[9] = "x10", vars[10] = "x11", vars[11] = "x12",
             vars[12] = "x13", vars[13] = "x14", vars[14] = "x15", vars[15] = "x16",
             vars[16] = "x17", vars[17] = "x18", vars[18] = "x19", vars[19] = "x20";

             printf("FAIL\n");

             printf("ord = "); mpoly_ordering_print(ord);
             printf(", len = %ld, exp_bits = %ld, exp_bound = %lx, "
                                      "coeff_bits = %ld, nvars = %ld\n\n",
                                  len, exp_bits, exp_bound, coeff_bits, nvars);

             fmpz_mpoly_print_pretty(f, vars, ctx); printf("\n\n");
             fmpz_mpoly_print_pretty(g, vars, ctx); printf("\n\n");
             fmpz_mpoly_print_pretty(h, vars, ctx); printf("\n\n");
             fmpz_mpoly_print_pretty(k1, vars, ctx); printf("\n\n");
             fmpz_mpoly_print_pretty(k2, vars, ctx); printf("\n\n");
          
             flint_abort();
          }
       }

       fmpz_mpoly_clear(f, ctx);  
       fmpz_mpoly_clear(g, ctx);  
       fmpz_mpoly_clear(h, ctx);  
       fmpz_mpoly_clear(k1, ctx);  
       fmpz_mpoly_clear(k2, ctx);  
    }

    /* Check aliasing first arg */
    for (i = 0; i < 1000 * flint_test_multiplier(); i++)
    {
       fmpz_mpoly_ctx_t ctx;
       fmpz_mpoly_t f, g, h;
       ordering_t ord;
       fmpz_t c;
       slong nvars, len, exp_bound, coeff_bits, exp_bits;

       fmpz_init(c);

       ord = mpoly_ordering_randtest(state);
       nvars = n_randint(state, 20) + 1;

       fmpz_mpoly_ctx_init(ctx, nvars, ord);

       fmpz_mpoly_init(f, ctx);
       fmpz_mpoly_init(g, ctx);
       fmpz_mpoly_init(h, ctx);

       len = n_randint(state, 100);

       exp_bits = n_randint(state, FLINT_BITS -
                     mpoly_ordering_isdeg(ord)*FLINT_BIT_COUNT(nvars) - 1) + 1;
       exp_bound = n_randbits(state, exp_bits);
       coeff_bits = n_randint(state, 200);

       fmpz_mpoly_randtest(f, state, len, exp_bound, coeff_bits, ctx);
       fmpz_mpoly_randtest(g, state, len, exp_bound, coeff_bits, ctx);
       fmpz_mpoly_set(h, f, ctx);

       for (j = 0; j < 10; j++)
       {
          len = f->length;

          fmpz_mpoly_add(f, f, g, ctx);

          fmpz_mpoly_sub(f, f, g, ctx);

          result = fmpz_mpoly_equal(f, h, ctx);

          if (!result)
          {
             const char * vars[20];
             vars[0] = "x1", vars[1] = "x2", vars[2] = "x3", vars[3] = "x4",
             vars[4] = "x5", vars[5] = "x6", vars[6] = "x7", vars[7] = "x8",
             vars[8] = "x9", vars[9] = "x10", vars[10] = "x11", vars[11] = "x12",
             vars[12] = "x13", vars[13] = "x14", vars[14] = "x15", vars[15] = "x16",
             vars[16] = "x17", vars[17] = "x18", vars[18] = "x19", vars[19] = "x20";

             printf("FAIL\n");
             
             printf("Aliasing test1\n");
             printf("ord = "); mpoly_ordering_print(ord);
             printf(", len = %ld, exp_bits = %ld, exp_bound = %lx, "
                                      "coeff_bits = %ld, nvars = %ld\n\n",
                                  len, exp_bits, exp_bound, coeff_bits, nvars);

             fmpz_mpoly_print_pretty(f, vars, ctx); printf("\n\n");
             fmpz_mpoly_print_pretty(g, vars, ctx); printf("\n\n");
             fmpz_mpoly_print_pretty(h, vars, ctx); printf("\n\n");

             flint_abort();
          }
       }

       fmpz_mpoly_clear(f, ctx);  
       fmpz_mpoly_clear(g, ctx);  
       fmpz_mpoly_clear(h, ctx);  
    }

    /* Check aliasing second arg */
    for (i = 0; i < 1000 * flint_test_multiplier(); i++)
    {
       fmpz_mpoly_ctx_t ctx;
       fmpz_mpoly_t f, g, h;
       ordering_t ord;
       fmpz_t c;
       slong nvars, len, exp_bound, coeff_bits, exp_bits;

       fmpz_init(c);

       ord = mpoly_ordering_randtest(state);
       nvars = n_randint(state, 20) + 1;

       fmpz_mpoly_ctx_init(ctx, nvars, ord);

       fmpz_mpoly_init(f, ctx);
       fmpz_mpoly_init(g, ctx);
       fmpz_mpoly_init(h, ctx);

       len = n_randint(state, 100);

       exp_bits = n_randint(state, FLINT_BITS -
                     mpoly_ordering_isdeg(ord)*FLINT_BIT_COUNT(nvars) - 1) + 1;
       exp_bound = n_randbits(state, exp_bits);
       coeff_bits = n_randint(state, 200);

       fmpz_mpoly_randtest(f, state, len, exp_bound, coeff_bits, ctx);
       fmpz_mpoly_randtest(g, state, len, exp_bound, coeff_bits, ctx);

       for (j = 0; j < 10; j++)
       {
          len = f->length;

          if ((j % 2) == 0)
          {
             fmpz_mpoly_add(h, g, f, ctx);

             fmpz_mpoly_add(f, g, f, ctx);
          } else
          {
             fmpz_mpoly_sub(h, g, f, ctx);

             fmpz_mpoly_sub(f, g, f, ctx);
          }

          result = fmpz_mpoly_equal(f, h, ctx);

          if (!result)
          {
             const char * vars[20];
             vars[0] = "x1", vars[1] = "x2", vars[2] = "x3", vars[3] = "x4",
             vars[4] = "x5", vars[5] = "x6", vars[6] = "x7", vars[7] = "x8",
             vars[8] = "x9", vars[9] = "x10", vars[10] = "x11", vars[11] = "x12",
             vars[12] = "x13", vars[13] = "x14", vars[14] = "x15", vars[15] = "x16",
             vars[16] = "x17", vars[17] = "x18", vars[18] = "x19", vars[19] = "x20";

             printf("FAIL\n");
             
             printf("Aliasing test2\n");
             printf("ord = "); mpoly_ordering_print(ord);
             printf(", len = %ld, exp_bits = %ld, exp_bound = %lx, "
                                      "coeff_bits = %ld, nvars = %ld\n\n",
                                  len, exp_bits, exp_bound, coeff_bits, nvars);

             fmpz_mpoly_print_pretty(f, vars, ctx); printf("\n\n");
             fmpz_mpoly_print_pretty(g, vars, ctx); printf("\n\n");
             fmpz_mpoly_print_pretty(h, vars, ctx); printf("\n\n");

             flint_abort();
          }
       }

       fmpz_mpoly_clear(f, ctx);  
       fmpz_mpoly_clear(g, ctx);  
       fmpz_mpoly_clear(h, ctx);  
    }

    FLINT_TEST_CLEANUP(state);
    
    flint_printf("PASS\n");
    return 0;
}
