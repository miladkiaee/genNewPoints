//
// Created by milad on 04/07/17.
//

#include "PtsLis.h"


void PtsLis::setControlPoints(std::vector <Point> cps)
{
    control_points = cps;
}

void PtsLis::setBSplines(std::vector <BSpline> sps)
{
    bsplines = sps;
}

void PtsLis::setInputFileName(std::string s)
{
    input_file_name = s;
}

std::string PtsLis::getInputFileName()
{
    return input_file_name;
}

void PtsLis::setOutputFileName(std::string s)
{
    output_file_name = s;
}

std::string PtsLis::getOutputFileName()
{
    return output_file_name;
}

void PtsLis::readFile()
{
    std::ifstream myInFile;
    myInFile.open(input_file_name.c_str());
    std::string line;
    std::vector<Point> cps;
    std::vector <BSpline> bsps;
    std::string tmp_string;

    if (myInFile.is_open())
    {
        while (std::getline(myInFile, line))
        {
            //store the lines
            std::stringstream ss(line);
            ss >> tmp_string;

            if (tmp_string == "CP")
            {
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
                cps.push_back(tmp_pt);
            }
            else if (tmp_string == "BSP")
            {
                BSpline bsp;
                std::getline(myInFile, line);
                int pt_num1, pt_num2;
                size_t N;
                std::stringstream ss(line);
                ss >> pt_num1 >> pt_num2 >> N;
                bsp.setNumPoints(N);
                // bspline points
                for (size_t i=0; i<N; i++)
                {
                    std::getline(myInFile, line);
                    Point tmp_pt(0,0,0,0);
                    std::stringstream ss(line);
                    double x, y, z;
                    ss >> x >> y >> z;
                    tmp_pt.setX(x);
                    tmp_pt.setY(y);
                    tmp_pt.setZ(z);
                    bsp.addNextPoint(tmp_pt);
                }
                bsps.push_back(bsp);
            }
        }
    }
    else
    {
        std::cout << "Error! check if the file is open ..."
                  << std::endl;
    }
    this->setControlPoints(cps);
    this->setBSplines(bsps);
    myInFile.close();
}

void PtsLis::printFile()
{
    std::ofstream myOutFile;
    myOutFile.open(output_file_name.c_str());
    for (size_t i=0; i< control_points.size(); i++)
    {
        myOutFile << "CP" << std::endl;
        myOutFile << control_points[i].getFlag() << " "
                << control_points[i].getX() << " "
                << control_points[i].getY() << " "
                << control_points[i].getZ() << std::endl;
    }

    for (size_t i=0; i<bsplines.size(); i++)
    {
        myOutFile << "BSP" << std::endl;
        myOutFile << bsplines[i].getPoint(0).getFlag() << " "
                  << bsplines[i].
                          getPoint(bsplines[i].getNumPoints()-1).
                          getFlag() << " "
                  << bsplines[i].getNumPoints() << std::endl;
        for (size_t j=0; j<bsplines[i].getNumPoints(); j++)
            myOutFile << bsplines[i].getPoint(j).getX() << " "
                      << bsplines[i].getPoint(j).getY() << " "
                      << bsplines[i].getPoint(j).getZ() << std::endl;
    }
    myOutFile.close();
}

std::vector <Point> PtsLis::getControlPoints()
{
    return control_points;
}

std::vector <BSpline> PtsLis::getBSplines()
{
    return bsplines;
}


