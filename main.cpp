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

        double delta;

        std::ifstream file;
        file.open("DELTAX");
        std::string line;
        getline(file, line);
        file.close();

        std::stringstream ss(line);
        std::string tmp;
        ss >> tmp;

        delta = atof(tmp.c_str());

        /*
        std::cout << "tmp = " << tmp << std::endl;
        std::cout << "line = " << line << std::endl;
        std::cout << "delta = " << delta << std::endl;
        */

        Manager manager(delta, crntPtsLis);
        manager.printPtsLisFiles();
    }

    if (input == "app_norm")
    {
        int i = atoi(argv[2]);
        std::string output = argv[3];
        DepResult dep;
        dep.setNumberOfInjectionPoints(4);
        dep.readRefFiles(); //reads the reference values
        dep.readLogFiles("plog");
        dep.addToNormFile(i, output);
    }
    // generates the new set of ptslis objects
    if (input == "update")
    {
        double delta;

        std::ifstream file;
        file.open("DELTAX");
        std::string line;
        getline(file, line);
        file.close();
        std::stringstream ss(line);
        std::string tmp;
        ss >> tmp;

        delta = atof(tmp.c_str());

        Manager manager(delta);
        manager.update();
        manager.printGrad();
        manager.printNewMasterPtsLis();
    }

    if (input == "compare_grads"){

        std::ifstream file, prevFile;

        std::vector <double> g, gprev;
        size_t n = 0;
        std::string line;

        file.open("grad-update");
        prevFile.open("grad-prev");

        while (getline(file, line)){
            std::stringstream ss(line);
            double tmp;
            ss >> tmp;
            g.push_back(tmp);
            n++;
        }
        file.close();

        while (getline(prevFile, line)){
            std::stringstream ss(line);
            double tmp;
            ss >> tmp;
            gprev.push_back(tmp);
        }
        file.close();

        double c=0;
        double s=0;
        for (size_t i=0; i<=n; i++){
            c += g[i]*gprev[i];
            s += gprev[i]*gprev[i];
        }
        c /= s;

        if (c < -0.5){
            double del;
            std::ifstream file;
            file.open("DELTAX");
            std::string line;
            getline(file, line);
            std::stringstream ss(line);

            std::string tmp;
            ss >> tmp;

            del = atof(tmp.c_str());

            del /= 2;

            std::ofstream ffile;
            ffile.open("DELTAX-update");
            ffile << del;
            ffile.close();
        }
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
                //nrm[i] = nrm[i]/nrm[0];
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
            poss << "_" << i+1 ;
            std::string pname = p + poss.str();
            std::cout << pname << " : " << std::endl;

            pFile.open(pname.c_str());
            while(std::getline(pFile, line)){
                std::stringstream ss(line);
                double tmp;
                std::string st;
                ss >> st >> tmp;
                pts.push_back(100.0*tmp);
                std::cout << pts.back() << std::endl;
            }
            pFile.close();
        }

        std::ofstream file;
        file.open("norm.dat");
        file << "# x    y" << std::endl;

        for (size_t i=0; i<N; i++){
            file << i+1 << "  " << nrm[i*(Npts+1)] << std::endl;
        }

        file.close();

        file.open("grad1.dat");
        file << "# x    y" << std::endl;

        for (size_t i=0; i<N; i++){
            file << i+1 << "  " << grd[i*(Npts+1) + 1] << std::endl;
        }

        file.close();

	file.open("grad2.dat");
        file << "# x    y" << std::endl;

        for (size_t i=0; i<N; i++){
            file << i+1 << "  " << grd[i*(Npts+1) + 2] << std::endl;
        }

        file.close();

	file.open("grad3.dat");
        file << "# x    y" << std::endl;

        for (size_t i=0; i<N; i++){
            file << i+1 << "  " << grd[i*(Npts+1) + 3] << std::endl;
        }

        file.close();

        file.open("ptsx1.dat");
        file << "# x    y" << std::endl;

        for (size_t i=0; i<N; i++){
            file << i+1 << "  " << pts[i*(Npts)] << std::endl;
        }

        file.close();

        file.open("ptsx2.dat");
        file << "# x    y" << std::endl;

        for (size_t i=0; i<N; i++){
            file << i+1 << "  " << pts[i*(Npts) + 1] << std::endl;
        }

        file.close();

        file.open("ptsx3.dat");
        file << "# x    y" << std::endl;

        for (size_t i=0; i<N; i++){
            file << i+1 << "  " << pts[i*(Npts) + 2] << std::endl;
        }

        file.close();
    }


    return 0;
}
