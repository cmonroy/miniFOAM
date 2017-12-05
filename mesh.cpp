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



void mesh::writeMesh()
{

   /* boost::filesystem::path dir("~/trash/mesh");

    if(!(boost::filesystem::exists(dir))){
        std::cout<<"Doesn't Exist"<<std::endl;

        if (boost::filesystem::create_directory(dir))
            std::cout << "....Successfully Created !" << std::end;
    }*/

    std::string myPath("/home/charles/trash/mesh");
    std::string myCommand("mkdir -p "  + myPath);
    //system("mkdir -p ~/trash/mesh");
    system(myCommand.c_str());
//const char *path="/home/user/file.txt";
  	ofstream pointFile;
  	//pointFile.open ("/home/charles/trash/mesh/points.txt");
  	pointFile.open (myPath+"/points.txt");
  	pointFile << totalNumberOfPoints << "\n";
	for (int i=0;  i < totalNumberOfPoints; i++)
	{
  		pointFile << to_string(points[i]->getX()) << " " << to_string(points[i]->getY()) << " " << "\n";
	}
	pointFile.close();

  	ofstream faceFile;
  	faceFile.open (myPath+"/faces.txt");
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
  	cellFile.open (myPath+"/cells.txt");
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
  	ownerFile.open (myPath+"/owners.txt");
  	ownerFile << totalNumberOfFaces << "\n";
	for (int i=0;  i < totalNumberOfFaces; i++)
	{
 		ownerFile <<  owner[i] << "\n";
	}
	ownerFile.close();

  	ofstream neigbourFile;
  	neigbourFile.open (myPath+"/neighbours.txt");
  	neigbourFile << totalNumberOfFaces << "\n";
	for (int i=0;  i < totalNumberOfFaces; i++)
	{
 		neigbourFile <<  neighbour[i] << "\n";
	}
	neigbourFile.close();

}

float mesh::getxCOG(int i) const
{

    float xCOG(0);
    for (int k=0; k<4; k++)
    {
        for (int l=0; l<2; l++)
        {
           xCOG=xCOG+0.125*this->points[this->faces[this->cells[i]->getFaceList()[k]]->getLabelList()[l]]->getX();
        }
    }
    return xCOG;
}

float mesh::getyCOG(int i) const
{

    float yCOG(0);
    for (int k=0; k<4; k++)
    {
        for (int l=0; l<2; l++)
        {
           yCOG=yCOG+0.125*this->points[this->faces[this->cells[i]->getFaceList()[k]]->getLabelList()[l]]->getY();
        }
    }
    return yCOG;
}

