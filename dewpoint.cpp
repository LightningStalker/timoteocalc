/* Compile with $ g++ -Wall -o dewpoint dewpoint.cpp
 *
 * ported from meteocalc by Project Crew™ on 7/26/2025
 */

#include <iostream>
#include <map>
#include <cmath>
#include <string>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

void
usage(string argv0)
{
    cerr
        << endl
        << "  " << argv0 << " needs temp°C and relative%humidity." << endl
        << "  output is dew point" << endl
        << endl
        << "  Usage: " << argv0 << " [°C] [%]" << endl
        << "  Example: " << argv0 << " 23.69 77.16" << endl
        << "  Output should be: 19.4509" << endl
        << endl;
}

int
main(int argc, char * argv[])
{
    float pa, dp, T, RH;

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

        // Create map of maps
        map<std::string, map<char, float> > CONSTANTS;

        // Adding elements to nest
        CONSTANTS.insert({ "positive", { { 'b', 17.368 }, { 'c', 238.88 } } });
        CONSTANTS.insert({ "negative", { { 'b', 17.966 }, { 'c', 247.15 } } });

        /* and this.is -> cool */

        /* declare working map */
        map<char, float> cnstnt;

        /* our ternary */
        cnstnt = (T > 0) ? CONSTANTS["positive"] : CONSTANTS["negative"];

        /* the equations */
        pa = RH /
            100. * exp(cnstnt['b'] * T /
                       (cnstnt['c'] + T)
                       );
        dp = cnstnt['c'] * log(pa) /
            (cnstnt['b'] - log(pa));

        /* putout */
        cout << dp << endl;

        /* hæ Timoteo */
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
