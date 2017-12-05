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
#include "scalarField.hpp"
#include "mesh.hpp"
#include "simulation.hpp"
#include "calculatedVectorField.hpp"

#include <iostream>
#include <fstream>

#include <Eigen/Sparse>
typedef Eigen::SparseMatrix<double> SpMat; // declares a column-major sparse matrix type of double
typedef Eigen::Triplet<double> T;

using namespace std;


scalarField::scalarField(std::string name, mesh& mesh_)
{
    m_name=name;
    m_N=mesh_.getN();

    for (int i = 0; i < mesh_.getN(); i++)
	{
		valueCurrent.push_back(0.0);
		valueOld.push_back(0.0);
	}
}



void scalarField::initialize(mesh& mesh_)
{
    for (int i = 0; i < mesh_.getN(); i++)
    {
        float radius(2.0);
        if ((pow(mesh_.getxCOG(i),2)+pow(mesh_.getyCOG(i),2))<radius)
        {
            this->valueCurrent[i]=1.0;
            this->valueOld[i]=1.0;
        }
    }
}

void scalarField::writeSF(simulation& simu_)
{
    std::string simuFolder(simu_.getFolder());
    std::ostringstream strT;
    strT << simu_.getT();
    std::string timeFolder = simuFolder + "/" + strT.str() + "/";
    std::string myCommand("mkdir -p "  + timeFolder);
    system(myCommand.c_str());

  	ofstream scalarFile;
  	scalarFile.open (timeFolder+this->m_name);
  	scalarFile << this->m_N << "\n";
	for (int i=0;  i < this->m_N; i++)
	{
 		scalarFile <<  this->valueCurrent[i] << "\n";
	}
	scalarFile.close();
}

void scalarField::update(Eigen::VectorXd& b)
{
    for (int i = 0; i < m_N; i++)
    {
        this->valueOld[i]=this->valueCurrent[i];
        this->valueCurrent[i]=b(i);
    }
}


SpMat scalarField::ddtA(simulation& simu_)
{
    SpMat A_(this->m_N,this->m_N);
    std::vector<T> tripletList;


    for (int i = 0; i < this->m_N; i++)
    {
        for (int j = 0; j < this->m_N; j++)
        {
            if (i==j)
            {
               tripletList.push_back(T(i,j,1.0/simu_.getDt()));
            }
        }
    }

    A_.setFromTriplets(tripletList.begin(), tripletList.end());

    return A_;
}


Eigen::VectorXd scalarField::ddtb(simulation& simu_)
{
    Eigen::VectorXd b_(this->m_N);

    for (int i = 0; i < this->m_N; i++)
    {
        b_(i)=(this->valueOld[i])/simu_.getDt();
    }

    return b_;
}

SpMat scalarField::divA(calculatedVectorField& Uf_, simulation& simu_)
{
    SpMat A_(this->m_N,this->m_N);


    //TODO: code divergence operator
    /*for (int i = 0; i < this->m_N; i++)
    {
        for (int j = 0; j < this->m_N; j++)
        {
            if (i==j)
            {
               A_(i,j)=1.0/simu_.getDt();
            }
            else
            {
                A_(i,j)=0.0;
            }
        }
    }*/

    return A_;
}
