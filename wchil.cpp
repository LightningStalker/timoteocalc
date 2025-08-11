/* Compile with $ g++ -Wall -o wchil wchil.cpp
 *
 * ported from meteocalc by Project Crew™ on 8/1/2025
 * see https://web.archive.org/web/20110918010232/http://www.weather.gov/os/windchill/index.shtml
 * https://en.wikipedia.org/wiki/Wind_chill
 */

#include <iostream>
#include <cmath>
#include <string>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

#include "wchil.hpp"

void
usage(string argv0)
{
    cerr
        << endl
        << "  " << argv0 << " needs temp°F and wind speed." << endl
        << "  output is wind chill in °F" << endl
        << endl
        << "  Usage: " << argv0 << " [°F] [MPH]" << endl
        << "  Example: " << argv0 << " 13.0 4.0" << endl
        << "  Output should be: 6.13" << endl
        << endl;
}

int
main(int argc, char * argv[])
{
    float T, V;

    if (argc == 3)
    {
        try
        {
            /* shell args passed in */
            T = stod(argv[1]);
            V = stod(argv[2]);
        } catch (invalid_argument& e)
        {
            cerr << "error: arguments must be numeric." << endl;
            return EXIT_FAILURE;
        }

        /* putout */
        cout << fixed << setprecision(2)
             << wind_chill(T, V) << endl;

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
