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

    Copyright (C) 2014 Fredrik Johansson

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "flint.h"
#include "fmpz_poly.h"


/*
Generated with Mathematica:
Table[Mod[MinimalPolynomial[2 Cos[2 Pi/n]][1337], 31337], {n,1,300}]
*/

static const short testdata[] = {
    1,
    1335, 1339, 1338, 1337, 2696, 1336, 30796, 1358, 28101, 22, 16072,
    1357, 27681, 28078, 31189, 26616, 22997, 28099, 20964, 25259, 17018,
    22796, 30688, 26615, 22301, 20150, 29305, 17687, 9574, 22041, 8475, 7232,
    10663, 7961, 13573, 11608, 29844, 21343, 18774, 11954, 567, 3486, 29805,
    11421, 18574, 29135, 11600, 7231, 20430, 10970, 11026, 8358, 23296, 29303,
    29465, 7825, 18111, 6414, 7407, 17482, 24400, 23824, 15398, 369, 22359,
    21281, 11824, 5620, 15124, 14927, 18872, 19778, 26463, 11425, 15476,
    22320, 19336, 26824, 2803, 24475, 13995, 26790, 674, 13858, 20896, 2448,
    18877, 500, 29090, 20982, 29875, 18862, 28199, 5071, 17613, 368, 11772,
    14214, 22871, 23416, 4199, 13435, 30768, 28568, 14665, 10308, 5414, 27939,
    12535, 553, 23997, 4593, 19403, 14479, 16270, 11719, 478, 1838, 14679,
    24868, 7207, 15155, 17797, 5274, 12718, 17266, 24266, 10811, 3642, 14826,
    4303, 15580, 23409, 13321, 22900, 6391, 21282, 26640, 9512, 15545, 12204,
    23111, 25241, 29067, 3513, 15817, 4995, 14499, 6958, 1947, 291, 1200,
    10431, 713, 25007, 4203, 19018, 23045, 20460, 10443, 7161, 13993, 15648,
    16029, 1937, 17704, 14407, 26439, 11237, 3102, 27729, 2590, 26643, 30727,
    7383, 26725, 10074, 10529, 12963, 14061, 15546, 9796, 10285, 24968, 11937,
    16138, 7408, 8463, 21869, 18111, 24123, 10810, 3396, 14512, 1151, 20074,
    1947, 26128, 29704, 8563, 5705, 19865, 6008, 14178, 512, 6704, 22538,
    13703, 15666, 28703, 24657, 20780, 10454, 5940, 18964, 7590, 22848, 1181,
    9240, 17694, 1587, 13900, 12588, 29985, 19185, 24610, 8093, 23116, 8123,
    17443, 18050, 27235, 30794, 20569, 31185, 25668, 165, 3984, 26063, 1309,
    24253, 8622, 16958, 28598, 27709, 14446, 27388, 27031, 7724, 16401, 29876,
    8203, 26109, 19861, 17381, 22046, 3554, 8667, 12029, 30411, 21643, 18480,
    29179, 3346, 14467, 20617, 4657, 23663, 25078, 23617, 20420, 4932, 8553,
    24377, 30730, 19167, 10860, 26527, 570, 12845, 6218, 13958, 17211, 19509,
    446, 29828, 26270, 9090, 7617, 8895, 25810, 6364, 21910, 26031, 3113,
    21469, 30799, 9950, 8422, 17632,
    -1
};


int main()
{
    fmpz_poly_t p;
    slong n;

    FLINT_TEST_INIT(state);

    flint_printf("cos_minpoly....");
    fflush(stdout);

    fmpz_poly_init(p);

    for (n = 0; testdata[n] != -1; n++)
    {
        mp_limb_t y;

        fmpz_poly_randtest(p, state, 20, 1 + n_randint(state, 100));

        fmpz_poly_cos_minpoly(p, n);
        y = fmpz_poly_evaluate_mod(p, 1337, 31337);

        if (y != testdata[n])
        {
            flint_printf("FAIL\nn = %wd\n", n);
            flint_printf("y = %wu\n", y);
            flint_printf("p = "); fmpz_poly_print(p);
            flint_printf("\n\n");
            abort();
        }
    }

    fmpz_poly_clear(p);

    FLINT_TEST_CLEANUP(state);
    flint_printf("PASS\n");
    return 0;
}
