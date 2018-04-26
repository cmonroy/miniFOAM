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

#include "faceVectorField.hpp"
#include "mesh.hpp"
#include "simulation.hpp"
#include <iostream>
#include <fstream>
#include <Eigen/Dense>
using namespace std;

using Eigen::VectorXd;
using namespace Eigen;


faceVectorField::faceVectorField(std::string name, mesh& mesh_)
{
    m_name=name;
    m_F=mesh_.getF();

    for (int i = 0; i < mesh_.getF(); i++)
	{
		Ux.push_back(0.0);
		Uy.push_back(0.0);
	}
}



void faceVectorField::initialize(mesh& mesh_)
{
    for (int i = 0; i < mesh_.getF(); i++)
    {
        this->Ux[i]=0.1;
        this->Uy[i]=0;
    }
}


