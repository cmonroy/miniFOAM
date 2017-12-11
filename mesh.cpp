//****************************************************************************//
//    This file is part of miniFOAM: simple, 2D, object-oriented CFD solver.  //
//                                                                            //
//    Copyright (C) Charles Monroy <charles.monroy@gmail.com>                 //
//                                                                            //
//    This program is free software: you can redistribute it and/or modify    //
//    it under the terms of the GNU General Public License as published by    //
//    the Free Software Foundation, either version 3 of the License, or       //
//    (at your option) any later version.                                     //
//                                                                            //
//    This program is distributed in the hope that it will be useful,         //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of          //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           //
//    GNU General Public License for more details.                            //
//                                                                            //
//    You should have received a copy of the GNU General Public License       //
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.   //
//****************************************************************************//
#include "mesh.hpp"
#include "simulation.hpp"
#include "point.hpp"
#include "face.hpp"
#include "cell.hpp"
#include <string>
#include <iostream>
#include <fstream>
//#include <boost>
using namespace std;

mesh::mesh()
{
	totalNumberOfCells=0;
}



mesh::~mesh()
{
/*	for (auto j : cells)
	{
		delete j;
	}

	for (auto k : points)
	{
		delete k;
	}
	for (auto l : faces)
	{
		delete l;
	}
*/
}



void mesh::writeMesh(simulation& simu_)
{

   /* boost::filesystem::path dir("~/trash/mesh");

    if(!(boost::filesystem::exists(dir))){
        std::cout<<"Doesn't Exist"<<std::endl;

        if (boost::filesystem::create_directory(dir))
            std::cout << "....Successfully Created !" << std::end;
    }*/

    std::string simuFolder(simu_.getFolder());

    std::string meshFolder = simuFolder + "/mesh";
    std::string myCommand("mkdir -p "  + meshFolder);
    system(myCommand.c_str());

//const char *path="/home/user/file.txt";
  	ofstream pointFile;
  	//pointFile.open ("/home/charles/trash/mesh/points.txt");
  	pointFile.open (meshFolder+"/points.txt");
  	pointFile << totalNumberOfPoints << "\n";
	for (int i=0;  i < totalNumberOfPoints; i++)
	{
  		pointFile << to_string(points[i]->getX()) << " " << to_string(points[i]->getY()) << " " << "\n";
	}
	pointFile.close();

  	ofstream faceFile;
  	faceFile.open (meshFolder+"/faces.txt");
  	faceFile << totalNumberOfFaces << "\n";
	for (int i=0;  i < totalNumberOfFaces; i++)
	{
		int sizeLabelList( (faces[i]->getLabelList()).size());
		for (int k=0; k<sizeLabelList; k++)
		{
  			faceFile <<  faces[i]->getLabelList()[k] << " ";
		}
		faceFile << " " << "\n";
	}
	faceFile.close();

  	ofstream cellFile;
  	cellFile.open (meshFolder+"/cells.txt");
  	cellFile << totalNumberOfCells << "\n";
	for (int i=0;  i < totalNumberOfCells; i++)
	{
		int sizeFaceList( (cells[i]->getFaceList()).size());
		for (int k=0; k<sizeFaceList; k++)
		{
  			cellFile <<  cells[i]->getFaceList()[k] << " ";
		}
		cellFile << " " << "\n";
	}
	cellFile.close();

  	ofstream ownerFile;
  	ownerFile.open (meshFolder+"/owners.txt");
  	ownerFile << totalNumberOfFaces << "\n";
	for (int i=0;  i < totalNumberOfFaces; i++)
	{
 		ownerFile <<  owner[i] << "\n";
	}
	ownerFile.close();

  	ofstream neigbourFile;
  	neigbourFile.open (meshFolder+"/neighbours.txt");
  	neigbourFile << totalNumberOfFaces << "\n";
	for (int i=0;  i < totalNumberOfFaces; i++)
	{
 		neigbourFile <<  neighbour[i] << "\n";
	}
	neigbourFile.close();

}

double mesh::getxCOG(int i) const
{

    double xCOG(0);
    for (int k=0; k<4; k++)
    {
        for (int l=0; l<2; l++)
        {
           xCOG=xCOG+0.125*this->points[this->faces[this->cells[i]->getFaceList()[k]]->getLabelList()[l]]->getX();
        }
    }
    return xCOG;
}

double mesh::getyCOG(int i) const
{

    double yCOG(0);
    for (int k=0; k<4; k++)
    {
        for (int l=0; l<2; l++)
        {
           yCOG=yCOG+0.125*this->points[this->faces[this->cells[i]->getFaceList()[k]]->getLabelList()[l]]->getY();
        }
    }
    return yCOG;
}

double mesh::getV(int i) const
{

    double V_(0);
    //see Peric eq.8.42
    for (int k=0; k<4; k++)
    {
        double xc(0);
        double yc(0);
        for (int l=0; l<2; l++)
        {
           xc=xc+0.5*this->points[this->faces[this->cells[i]->getFaceList()[k]]->getLabelList()[l]]->getX();
           yc=yc+0.5*this->points[this->faces[this->cells[i]->getFaceList()[k]]->getLabelList()[l]]->getY();
        }
        double Sfxc_=this->faces[this->cells[i]->getFaceList()[k]]->getSfx();
        //double Sfyc_=this->faces[this->cells[i]->getFaceList()[k]]->getSfy();
        V_=V_+xc*Sfxc_;//+yc*Sfyc_;
    }
    return V_;
}


