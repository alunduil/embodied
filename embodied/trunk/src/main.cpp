#include <iostream>
#include <cstdlib>
#include <iomanip>

#include "../include/embodied.h"
#include "../include/output.h"

using namespace std;

int main(int argc, char **argv)
{
    Embodied *application;
    vector<vector<vector<double> > > potential;
    try
    {
        application = new Embodied(argc, argv);
        potential = application->CalculatePotential();
    }
    catch (EmbodiedArgumentError e)
    {
        if (e.GetMessage().length() > 0) ERROR(e.GetMessage());
        cout << e.GetDescription() << endl;
        return EXIT_FAILURE;
    }
    catch (EmbodiedError e)
    {
        if (e.GetMessage().length() > 0) ERROR(e.GetMessage());
        return EXIT_FAILURE;
    }

    for (int i = 0; i < potential.size(); ++i)
        for (int j = 0; j < potential[i].size(); ++j)
            for (int k = 0; k < potential[i][j].size(); ++k)
                cout << "(" << setfill('0') << setw(6) << i << "," << setw(6) << j << "," << setw(6) << k << ") " << scientific << setprecision(14) << potential[i][j][k] << endl;

    return EXIT_SUCCESS;
}
// kate: indent-mode cstyle; space-indent on; indent-width 4;
