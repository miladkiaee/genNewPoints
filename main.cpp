#include "PtsLis.h"
#include "DepResult.h"
#include "Manager.h"
#include <cmath>

int main(int argc, char* argv[]) {

    std::string input = argv[1];

    if (input == "append_norm")
    {
        std::string output = argv[2];
        DepResult dep;
        dep.setNumberOfInjectionPoints(3);
        dep.readRefFiles(); //reads the reference values
        dep.readLogFiles("plog");
        dep.addToNormFile(output);
    }

    return 0;
}
