/* Compile with $ g++ -o dp2rh dp2rh.cpp
 *
 * Project Crew™ 7/7/2026
 */

#include <iostream>
#include <map>
#include <cmath>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

void
usage(string argv0)
{
    cerr
        << endl
        << "  Relative humidity from temperature and dew point" << endl
        << endl
        << "  " << argv0 << " needs temp\u00b0C and dew point." << endl
        << "  output is relative%humidity" << endl
        << endl
        << "  Usage: " << argv0 << " [\u00b0C] [%RH]" << endl
        << "  Example:  $ " << argv0 << " 76.28 65.38" << endl
        << "  Output should be: 62.40" << endl
        << endl;
}

int
main(int argc, char * argv[])
{
    float pb, pc, DP, T, rh;

    if (argc == 3)
    {
        try
        {
            /* shell args passed in */
            T = stod(argv[1]);
            DP = stod(argv[2]);
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

        /* declare working map */
        map<char, float> cnstnt;

        /* our ternary */
        cnstnt = (T > 0) ? CONSTANTS["positive"] : CONSTANTS["negative"];

        /* the equations */
        pb = exp(cnstnt['b'] * DP / (DP + cnstnt['c']));
        pc = 100.0 * pb * exp(-T * cnstnt['b'] / (cnstnt['c'] + T));
        rh = pc > 100.0 ? 100.0 : pc;   // can't be more

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
