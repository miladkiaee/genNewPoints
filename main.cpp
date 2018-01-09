#include "PtsLis.h"
#include "DepResult.h"
#include "Manager.h"
#include <cmath>

int main(int argc, char* argv[]) {

    std::string input = argv[1];

    if (input == "append_norm")
    {
        std::string s = argv[2];
        DepResult d;
        d.setNumberOfInjectionPoints(3);
        d.readRefFiles(); //reads the reference values
        d.readLogFiles("plog");
        d.addToNormFile(s);
    }

    return 0;
}
