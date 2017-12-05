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
#ifndef scalarFieldHeader
#define scalarFieldHeader

#include <string>
#include <vector>
#include <Eigen/Sparse>
typedef Eigen::SparseMatrix<double> SpMat; // declares a column-major sparse matrix type of double



class mesh;
class simulation;
class calculatedVectorField;

class scalarField
{
    std::string m_name;
    int m_N;
	std::vector<double> valueCurrent;
	std::vector<double> valueOld;

public:
	scalarField(std::string, mesh&);
    SpMat ddtA(simulation&);
    Eigen::VectorXd ddtb(simulation&);



    void initialize(mesh&);
    void writeSF(simulation&);
    void update(Eigen::VectorXd&);
    SpMat divA(calculatedVectorField&, simulation&);
    //Eigen::vectorXd divb(vectorField);
};


#endif
