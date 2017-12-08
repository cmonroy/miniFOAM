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
#ifndef meshHeader
#define meshHeader

#include <string>
#include <vector>

class simulation;

class cell;
class face;
class point;

class mesh
{
protected:
	std::vector<point*> points;
	std::vector<face*> faces;
	std::vector<cell*> cells;

	//std::vector<int> listOfFaces;
	//std::vector<vector<int>> labelListList;
	std::vector<int> owner;
	std::vector<int> neighbour;



	int totalNumberOfPoints;
	int totalNumberOfFaces;
	int totalNumberOfCells;

public:
	mesh();
	~mesh();
	void writeMesh(simulation&);
	int getN() const { return totalNumberOfCells; };
	int getF() const { return totalNumberOfFaces; };
	float getxCOG(int) const;
	float getyCOG(int) const;
	std::vector<int> getOwnerList() const { return owner; };
	std::vector<int> getNeighbourList() const { return neighbour; };
	std::vector<face*> getFaces() const { return faces; };
	//void splitCell(cell &c);
};


#endif
