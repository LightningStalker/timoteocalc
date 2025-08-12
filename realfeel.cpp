/* Compile with $ g++ -Wall -o realfeel realfeel.cpp
 *
 * what feels like temperature is?
 * ported from meteocalc by Project Crew™ on 8/9/2025
 */

#include <iostream>
#include <cmath>
#include <numeric>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

#include "heatind.hpp"
#include "wchil.hpp"

#define _FEELS_LIKE

void
usage(string argv0)
{
    cerr
        << endl
        << "  " << argv0 << " needs temp°F, relative%humidity and wind speed." << endl
        << "  output is \"feels like\" temperature in °F" << endl
        << endl
        << "  Usage: " << argv0 << " [°F] [%] [MPH]" << endl
        << "  Example: " << argv0 << " 85.43 68.16 6.8" << endl
        << "  Output should be: 92.97" << endl
        << endl;
}

int
main(int argc, char * argv[])
{
    float T,
          RH,
          V,
          FEELS_LIKE;

    if (argc == 4)
    {
        try
        {
            /* shell args passed in */
            T = stod(argv[1]);
            RH = stod(argv[2]);
            V = stod(argv[3]);
        } catch (invalid_argument& e)
        {
            cerr << "error: arguments must be numeric." << endl;
            return EXIT_FAILURE;
        }

        /* begin to process */
        if (T <= 50 && V > 3)
        {
            /* we need the chills */
            FEELS_LIKE = wind_chill(T, V);
            
        }else if (T >= 80)
        {
            FEELS_LIKE = heat_index(T, RH);

        }else
        {
            /* just the temp */
            FEELS_LIKE = T;
        }

        /* putout */
        cout << fixed << setprecision(2)
             << FEELS_LIKE << endl;

    }else
    {
        /* declare path and initialize */
        fs::path argv0(argv[0]);

        /* basename */
        usage(string(argv0.stem()));
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
/* and I really feel
 * like I'm losing my mighty real friend
 * no I can't fight this feelin it could be
 * the end
 */
