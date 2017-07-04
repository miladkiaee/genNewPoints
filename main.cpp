#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "Point.h"
#include "BSpline.h"

int main() {
    std::ifstream myInFile;
    myInFile.open("pts.lis");
    std::string line;
    std::vector<Point> cps;
    std::vector <BSpline> bsps;
    std::string tmp_string;

    if (myInFile.is_open()) {
        while (std::getline(myInFile, line)) {
            //store the lines
            std::stringstream ss(line);
            ss >> tmp_string;

            if (tmp_string == "CP"){
                std::getline(myInFile, line);
                std::stringstream ss(line);
                Point tmp_pt(0,0,0,0);
                size_t tmp_f;
                double x, y, z;

                ss >> tmp_f >> x >> y >> z;

                tmp_pt.setX(x);
                tmp_pt.setY(y);
                tmp_pt.setZ(z);
                tmp_pt.setFlag(tmp_f);
                tmp_pt.print();
                cps.push_back(tmp_pt);
            }
            else if (tmp_string == "BSP") {
                BSpline bsp;
                std::getline(myInFile, line);
                size_t pt_num1, pt_num2, N;
                std::stringstream ss(line);
                ss >> pt_num1 >> pt_num2 >> N;
                bsp.setNumPoints(N);

                // first point
                std::getline(myInFile, line);
                Point tmp_pt(0,0,0,0);
                std::stringstream ss2(line);
                double x, y, z;
                ss2 >> x >> y >> z;
                tmp_pt.setX(x);
                tmp_pt.setY(y);
                tmp_pt.setZ(z);
                tmp_pt.setFlag(pt_num1);
                bsp.setFirstPoint(tmp_pt);

                // internal points
                for (size_t i=0; i<N; i++){
                    std::getline(myInFile, line);
                    Point tmp_pt(0,0,0,0);
                    std::stringstream ss(line);
                    double x, y, z;
                    ss >> x >> y >> z;
                    tmp_pt.setX(x);
                    tmp_pt.setY(y);
                    tmp_pt.setZ(z);
                    tmp_pt.setFlag(i);
                    bsp.addNextPoint(tmp_pt);
                }
                // last point
                std::getline(myInFile, line);
                std::stringstream ss3(line);
                ss3 >> x >> y >> z;
                tmp_pt.setX(x);
                tmp_pt.setY(y);
                tmp_pt.setZ(z);
                tmp_pt.setFlag(pt_num2);
                bsp.setLastPoint(tmp_pt);
                bsp.print();
                bsps.push_back(bsp);
            }
        }
    }
    else {
        std::cout << "Error! check if the file is open ..."
                  << std::endl;
        return 0;
    }

    std::vector <Point> new_cps;
    std::vector <std::vector <Point> > new_bsps;
    myInFile.close();

    return 0;
}