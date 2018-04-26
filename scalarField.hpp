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
class faceVectorField;

class scalarField
{
    std::string m_name;
    int m_N;
	std::vector<double> valueCurrent;
	std::vector<double> valueOld;

public:
	scalarField(std::string, mesh&);
    SpMat ddtA(simulation&, mesh&);
    Eigen::VectorXd ddtb(simulation&, mesh&);

    //std::vector<double> interpolateOnFaces(mesh&); //returns a vector of interpolated values at faces
    void initialize(mesh&);
    void writeSF(simulation&); //writes value of scalar field
    void writeXYandSF(mesh&,simulation&); //writes coordinates of centers of cells + values of scalar field
    void update(Eigen::VectorXd&);
    SpMat divA(faceVectorField&, simulation&, mesh&);
    Eigen::VectorXd divb(faceVectorField&, simulation&, mesh&);
    Eigen::VectorXd divb_explicit(faceVectorField&, simulation&, mesh&);
};


#endif
