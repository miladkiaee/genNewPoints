#include "PtsLis.h"
#include "DepResult.h"
#include "Manager.h"
#include <cmath>

int main(int argc, char* argv[]) {

    std::string input = argv[1];

    if (input == "gen_pts")
    {
        PtsLis crntPtsLis;
        crntPtsLis.setInputFileName("pts.lis");
        crntPtsLis.readFile();
        double delta = atof(argv[2]);
        Manager manager(delta, crntPtsLis);
        manager.printPtsLisFiles();
    }

    if (input == "app_norm")
    {
        DepResult dep;
        dep.setNumberOfInjectionPoints(4);
        dep.readRefFiles(); //reads the reference values
        dep.readLogFiles("plog");
        dep.addToNormFile();
    }
    // generates the new set of ptslis objects
    if (input == "update")
    {
        double delta;

        if (argc == 3){
            delta = atof(argv[2]);
        } else {
            std::cout << "delta is not set. using default value."
                      << std::endl;
            delta = 0.0005;
        }

        Manager manager(delta);
        manager.update();
        manager.printGrad();
        manager.printNewMasterPtsLis();
        manager.printCompareGrad();

    }

    if (input == "compare_grads"){
        std::ifstream file;
        file.open("compare.txt");

        std::string line;

        std::getline(file, line);

        std::stringstream ss(line);
        double tmp;
        ss >> tmp;

        if (tmp < -0.5){
            std::ofstream ffile;
            ffile.open("change_delta");
            ffile << "indicator for change of step size!!";
            ffile.close();
        }

        file.close();
    }

    if (input == "gen_plotdata") {

        std::ifstream nFile;
        std::ifstream gFile;
        std::ifstream pFile;

        std::string n = "norm";
        std::string g = "grad";
        std::string p = "points";

        std::vector <double> nrm;
        std::vector <double> grd;
        std::vector <double> pts;

        std::string line;

        int N = atoi(argv[2]);
        int Npts=atoi(argv[3]);

        for (size_t i=0; i<N; i++){

            std::ostringstream noss;
            noss << "_" << i+1 ;
            std::string nname = n + noss.str();

            nFile.open(nname.c_str());
            while(std::getline(nFile, line)){
                std::stringstream ss(line);
                double tmp;
                ss >> tmp;
                nrm.push_back(tmp);
                nrm[i] = nrm[i]/nrm[0];
            }
            nFile.close();

            std::ostringstream goss;
            goss << "_" << i+1 ;
            std::string gname = g + goss.str();

            gFile.open(gname.c_str());
            while(std::getline(gFile, line)){
                std::stringstream ss(line);
                double tmp;
                ss >> tmp;
                grd.push_back(tmp);
            }
            gFile.close();

            std::ostringstream poss;
            poss << "_" << i ;
            std::string pname = p + poss.str();

            pFile.open(pname.c_str());
            while(std::getline(pFile, line)){
                std::stringstream ss(line);
                double tmp;
                std::string st;
                ss >> st >> tmp;
                pts.push_back(100.0*tmp);
            }
            pFile.close();
        }

        std::ofstream file;
        file.open("norm.dat");
        file << "# x    y" << std::endl;

        for (size_t i=0; i<N; i++){
            file << i+1 << "  " << nrm[i*(Npts)] << std::endl;
        }

        file.close();

        file.open("grad.dat");
        file << "# x    y" << std::endl;

        for (size_t i=0; i<N; i++){
            file << i+1 << "  " << sqrt(pow(grd[i*(Npts)+1],2)
		+ pow(grd[i*(Npts)+2],2)) << std::endl;
        }

        file.close();

        file.open("ptsx.dat");
        file << "# x    y" << std::endl;

        for (size_t i=0; i<N; i++){
            file << i+1 << "  " << pts[i*(Npts-1)] << std::endl;
        }

        file.close();
    }


    return 0;
}
