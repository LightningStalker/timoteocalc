/* heat index header file
 */

/* coefficients from human body model */
const float
    c1 = -42.379,
    c2 = 2.04901523,
    c3 = 10.14333127,
    c4 = -0.22475541,
    c5 = -6.83783e-3,
    c6 = -5.481717e-2,
    c7 = 1.22874e-3,
    c8 = 8.5282e-4,
    c9 = -1.99e-6;

/* heat index calc function */
float
heat_index(float T, float RH)
{
    float HI;

    /* array of intermediate polynomial */
    float poly[] = {
        c1,
        c2 *      T,
        c3 *      RH,
        c4 *      T      * RH,
        c5 * powf(T,  2),
        c6 * powf(RH, 2),
        c7 * powf(T,  2) * RH,
        c8 *      T      * powf(RH, 2),
        c9 * powf(T,  2) * powf(RH, 2),
    };

    if (T >= 80 && RH >= 40)
    {
        /* sum up our array */
        HI = accumulate(begin(poly), end(poly), 0.0, plus<float>());
    }else
    {
        /* using simplified formula */
        HI = 0.5 * (T + 61. + (T - 68.) * 1.2 + RH * 0.094);
    }

    return HI;
}
