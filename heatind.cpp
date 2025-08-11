/* compile with $ g++ -Wall -Os -o heatind heatind.cpp
 *
 * ported to C++ from meteocalc by Project Crew™ 7/28/2025
 * tested against "Heat index calculator" of Calculator.net
 * see https://en.wikipedia.org/wiki/Heat_index
 *     http://www.wpc.ncep.noaa.gov/html/heatindex_equation.shtml
 */

#include <iostream>
#include <iomanip>
#include <numeric>
#include <cmath>
#include <string>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

#include "heatind.hpp"

void
usage(string argv0)
{
    cerr
        << endl
        << "  " << argv0 << " needs temp°F and relative%humidity." << endl
        << "  output is heat index in °F" << endl
        << endl
        << "  Usage: " << argv0 << " [°F] [%]" << endl
        << "  Example: " << argv0 << " 89.16 69.68" << endl
        << "  Output should be: 103.26" << endl
        << endl;
}

int
main(int argc, char * argv[])
{
    float T, RH;

    if (argc == 3)
    {
        try
        {
            /* shell args passed in */
            T = stod(argv[1]);
            RH = stod(argv[2]);
        } catch (invalid_argument& e)
        {
            cerr << "error: arguments must be numeric." << endl;
            return EXIT_FAILURE;
        }

        /* output */
        cout << fixed << setprecision(2)
             << heat_index(T, RH) << endl;
    }else
    {
        /* declare path and initialize */
        fs::path argv0(argv[0]);

        /* basename */
        usage(string(argv0.stem()));
        return EXIT_FAILURE;
    }

    /* the end */
    return EXIT_SUCCESS;
}
