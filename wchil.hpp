/* wind chill header file
 */

/* wind chill calc function */
float
wind_chill(float T, float V)
{
    float WINDCHILL;

    #ifndef _FEELS_LIKE
    if (T > 50 || V <= 3)
    {
        cerr << endl
             << "  Wind Chill Temperature is only defined for" << endl
             << "  temperatures at or below 50 F and wind speeds" << endl
             << "  above 3 mph." << endl
             << endl;
        return EXIT_FAILURE;
    }
    #endif

    WINDCHILL = 35.74 + 0.6215 * T - 35.75 * powf(V, 0.16) +
        0.4275 * T * powf(V, 0.16);

    return WINDCHILL;
}
