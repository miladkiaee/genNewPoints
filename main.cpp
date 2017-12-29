#include "PtsLis.h"
#include "DepResult.h"
#include "Manager.h"
#include <cmath>

int main(int argc, char* argv[]) {

    std::string input = argv[1];

    if (input == "append_norm")
    {
        std::string O = argv[2];
        DepResult D;
        D.setNumberOfInjectionPoints(3);
        D.readRefFiles(); //reads the reference values
        D.readLogFiles("plog");
        D.addToNormFile(O);
    }

    return 0;
}
