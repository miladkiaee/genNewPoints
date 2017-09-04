//
// Created by milad on 04/07/17.
//

#include "PtsLis.h"

PtsLis & PtsLis::operator=(PtsLis A) {
    input_file_name = A.getInputFileName();
    output_file_name = A.getOutputFileName();
    points = A.getPoints();
    n_points = A.getNumPoints();
    return *this;
}

void PtsLis::setPoints(std::vector <Point> cps)
{
    points = cps;
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

size_t PtsLis::getNumPoints() {
    return n_points;
}

void PtsLis::setNumPoints(size_t n) {
    n_points = n;
}

void PtsLis::readFile()
{
    std::ifstream myInFile;
    myInFile.open(input_file_name.c_str());
    std::string line;
    std::vector<Point> cps;

    n_points=0;
    if (myInFile.is_open())
    {
        while (std::getline(myInFile, line))
        {
            //store the lines
            std::stringstream ss(line);
            Point tmp_pt("",0,0,0);
            std::string tmp_f;
            double x, y, z;
            ss >> tmp_f >> x >> y >> z;
            tmp_pt.setX(x);
            tmp_pt.setY(y);
            tmp_pt.setZ(z);
            tmp_pt.setFlag(tmp_f);
            cps.push_back(tmp_pt);
            n_points++;
        }
    }
    else
    {
        std::cout << "Error! check if the pts.files can be opened ..."
                  << std::endl;
    }
    n_points = cps.size();
    this->setPoints(cps);
    myInFile.close();
}

void PtsLis::printFile()
{
    std::ofstream myOutFile;
    myOutFile.open(output_file_name.c_str());
    for (size_t i=0; i< points.size(); i++)
    {
        myOutFile << points[i].getFlag() << " "
                << points[i].getX() << " "
                << points[i].getY() << " "
                << points[i].getZ() << std::endl;
    }
    myOutFile.close();
}

std::vector <Point> PtsLis::getPoints()
{
    return points;
}

void PtsLis::differOnePoint(size_t i, double dx){
    double xold = points[i].getX();
    points[i].setX(xold + dx);
}