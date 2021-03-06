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
#ifndef simulationHeader
#define simulationHeader
#include <string>


class simulation
{
	double dt;
	double endTime;
	double t;
	double L;
	int Nx;
    std::string simulationFolder;
    std::string divScheme;
    std::string BC;

public :
	simulation();
	//~simulation();
	double getT() const { return t; };
	double getDt() const { return dt; };
	double getEndTime() const { return endTime; };
	double getL() const { return L; };
	int getNx() const { return Nx; };
	std::string getFolder() const { return simulationFolder; };
	std::string getDivScheme() const { return divScheme; };
	std::string getBC() const { return BC; };
	void increment();
	void writeVisuFile();
};


#endif
