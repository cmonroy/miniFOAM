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
#ifndef calculatedVectorFieldHeader
#define calculatedVectorFieldHeader

#include <string>
#include <vector>
#include <Eigen/Dense>

//using Eigen::VectorXd;


class mesh;
class simulation;

class calculatedVectorField
{
    std::string m_name;
    int m_F;
	std::vector<double> Ux;
	std::vector<double> Uy;

public:
	calculatedVectorField(std::string, mesh&);
    void initialize(mesh&);
    //void writeCVF(simulation&);
    //void update(Eigen::VectorXd&);

};


#endif
