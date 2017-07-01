#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <math.h>

#include "Point.h"
#include "BSpline.h"

int main() {
    std::vector <Point> vAllP;
    std::ifstream myInFile;
    myInFile.open("pts.list");

    int value;
    double value_doublex, value_doubley, value_doublez;
    char c;
    std::string flag_string = "";
    std::vector<std::string> lines;
    std::string line;
    std::vector<Point> cps;
    std::vector<std::vector <Point> > bspss;
    std::vector <BSpline> bsps;
    std::string tmp_string;

    if (myInFile.is_open())
    {
        while (std::getline(myInFile, line))
        {
            //store the lines
            lines.push_back(line);
            std::stringstream ss(line);
            ss >> tmp_string;

            if (tmp_string == "CP"){
                std::getline(myInFile, line);
                std::stringstream ss(line);
                Point* tmp_pt;
                size_t tmp_f;
                double x, y, z;

                ss >> tmp_f >> x >> y >> z;

                tmp_pt->setX(x);
                tmp_pt->setY(y);
                tmp_pt->setZ(z);
                tmp_pt->setFlag(tmp_f);
                cps.push_back(*tmp_pt);
            }
            else if (tmp_string == "BSP")
            {
                std::getline(myInFile, line);
                size_t pt_num1, pt_num2, N;
                Point* tmp_pt;
                std::vector <Point> tmp_pt_vec;
                std::stringstream ss(line);
                ss >> pt_num1 >> pt_num2 >> N;

                for (size_t i=0; i<N+2; i++){
                    std::getline(myInFile, line);
                    Point* tmp_pt;
                    std::stringstream ss(line);
                    double x, y, z;
                    ss >> x >> y >> z;
                    tmp_pt->setX(x);
                    tmp_pt->setY(y);
                    tmp_pt->setZ(z);
                    tmp_pt->setFlag(i);
                    tmp_pt_vec.push_back(*tmp_pt);
                }

                bsps.push_back(tmp_pt_vec);
            }
        }
    } else {
        std::cout << "Error! check if the file is open .." << std::endl;
        return 0;
    }

    std::vector <Point> new_cps;
    std::vector <std::vector <Point> > new_bsps;

    myInFile.close();
    return 0;
}