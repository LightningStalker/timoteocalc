/* Compile with $ g++ -o bulb bulb.cpp
 *
 * Project Crew™ 7/7/2026
 */

#include <iostream>
#include <map>
#include <cmath>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

const float
    b = 17.625,
    c = 243.04;

void
usage(string argv0)
{
    cerr
        << endl
        << "  Relative humidity from wet bulb and dry bulb temperature" << endl
        << endl
        << "  " << argv0 << " needs temp\u00b0C of the wet and dry thermometer bulbs." << endl
        << "  output is the percent relative humidity" << endl
        << endl
        << "  Usage: " << argv0 << " [\u00b0C wet] [\u00b0C dry]" << endl
        << "  Example:  $ " << argv0 << " 15.0 24.1" << endl
        << "  Output should be: 56.81" << endl
        << endl;
}

int
main(int argc, char * argv[])
{
    float WBT, DBT, rh;

    if (argc == 3)
    {
        try
        {
            /* shell args passed in */
            WBT = stod(argv[1]);
            DBT = stod(argv[2]);
        } catch (invalid_argument& e)
        {
            cerr << "error: arguments must be numeric." << endl;
            return EXIT_FAILURE;
        }

        if(WBT < 0 or DBT < 0)
        {
            cerr << "error: we can't work below freezing" << endl;
            exit(EXIT_FAILURE);
        }else if(WBT > 99.0 or DBT > 99.0)
        {
            cerr << "error: looks hot" << endl;
            exit(EXIT_FAILURE);
        }else if(WBT > DBT)
        {
            cerr << "error: wet bulb is greater than dry bulb" << endl;
            exit(EXIT_FAILURE);
        }

        /* the equations */
        rh = 100 * exp((b * WBT) /
                       (c + WBT)) /
                   exp((b * DBT) /
                       (c + DBT));

        /* output */
        cout << fixed << setprecision(2)
             << rh << endl;
    } else
    {
        /* declare path and initialize */
        fs::path argv0(argv[0]);

        /* basename */
        usage(string(argv0.stem()));
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
