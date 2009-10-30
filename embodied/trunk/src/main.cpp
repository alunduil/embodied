#include <iostream>
#include <cstdlib>
#include <embodied.h>

using namespace std;

int main(int argc, char **argv)
{
    Embodied *application;
    std::vector<std::vector<std::vector<double> > > potential;
    try
    {
        application = new Embodied(argc, argv);
        potential = application->CalculatePotential();
    }
    catch (EmbodiedArgumentError e)
    {
        if (e.GetMessage().length() > 0) cout << e.GetMessage() << endl;
        cout << e.GetDescription() << endl;
        return EXIT_FAILURE;
    }
    catch (EmbodiedError e)
    {
        if (e.GetMessage().length() > 0) cout << e.GetMessage() << endl;
        return EXIT_FAILURE;
    }

    for (int i = 0; i < potential.size(); ++i)
        for (int j = 0; j < potential[i].size(); ++j)
            for (int k = 0; k < potential[i][j].size(); ++k)
                cout << "(" << i << "," << j << "," << k << ") " << potential[i][j][k] << endl;

    return EXIT_SUCCESS;
}
// kate: indent-mode cstyle; space-indent on; indent-width 4;
