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
#include "face.hpp"
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
        float radius(1.0);
        if ((pow(mesh_.getxCOG(i),2)+pow(mesh_.getyCOG(i),2))<pow(radius,2))
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

void scalarField::writeXYandSF(mesh& mesh_,simulation& simu_)
{
    std::string simuFolder(simu_.getFolder());
    std::ostringstream strT;
    strT << simu_.getT();
    std::string timeFolder = simuFolder + "/" + strT.str() + "/";
    std::string myCommand("mkdir -p "  + timeFolder);
    system(myCommand.c_str());

  	ofstream scalarFile;
  	scalarFile.open (timeFolder+this->m_name);
  	scalarFile << "# " << this->m_N << "\n";
	for (int i=0;  i < this->m_N; i++)
	{
 		scalarFile <<  mesh_.getxCOG(i) << " " << mesh_.getyCOG(i) << " " << this->valueCurrent[i] << "\n";
	}
	scalarFile.close();
}




void scalarField::update(Eigen::VectorXd& b)
{
    for (int i = 0; i < this->m_N; i++)
    {
        this->valueOld[i]=this->valueCurrent[i];
        this->valueCurrent[i]=b(i);
    }
}


SpMat scalarField::ddtA(simulation& simu_, mesh& mesh_)
{
    SpMat A_(this->m_N,this->m_N);
    std::vector<T> tripletList;


    for (int i = 0; i < this->m_N; i++)
    {
        for (int j = 0; j < this->m_N; j++)
        {
            if (i==j)
            {
               double V_=mesh_.getV(i);
               tripletList.push_back(T(i,j,V_*1.0/simu_.getDt()));
            }
        }
    }

    A_.setFromTriplets(tripletList.begin(), tripletList.end());

    return A_;
}


Eigen::VectorXd scalarField::ddtb(simulation& simu_, mesh& mesh_)
{
    Eigen::VectorXd b_(this->m_N);

    for (int i = 0; i < this->m_N; i++)
    {
        double V_=mesh_.getV(i);
        b_(i)=V_*(this->valueOld[i])/simu_.getDt();
    }

    return b_;
}

SpMat scalarField::divA(calculatedVectorField& Uf_, simulation& simu_, mesh& mesh_)
{
    SpMat A_(this->m_N,this->m_N);

    Eigen::VectorXd diagCoefs_= Eigen::VectorXd::Zero(this->m_N);

    std::vector<T> tripletList;

    for (int k=0; k<mesh_.getF(); k++) // loop on the faces
    {
        int owner=mesh_.getOwnerList()[k];
        int neighbour=mesh_.getNeighbourList()[k];

        double flux_=Uf_.getUx()[k]*mesh_.getFaces()[k]->getSfx()+Uf_.getUy()[k]*mesh_.getFaces()[k]->getSfy();

        if (neighbour>=0) //internal face
        {
            //central-difference scheme:
            /*diagCoefs_[owner]=diagCoefs_[owner]+flux_*0.5;
            diagCoefs_[neighbour]=diagCoefs_[neighbour]-flux_*0.5;
            tripletList.push_back(T(owner,neighbour,flux_*0.5));
            tripletList.push_back(T(neighbour,owner,-flux_*0.5));*/

            //Upwind
            if (flux_>0)
            {
                diagCoefs_[owner]=diagCoefs_[owner]+flux_;

                tripletList.push_back(T(owner,neighbour,0.0));
                tripletList.push_back(T(neighbour,owner,-flux_));
            }
            else
            {
                diagCoefs_[neighbour]=diagCoefs_[neighbour]-flux_;
                tripletList.push_back(T(owner,neighbour,flux_));
                tripletList.push_back(T(neighbour,owner,0.0));
            }
        }
        else // boundary face
        {
            // Neumann boundary condition (ie zero-gradient BC):
            diagCoefs_[owner]=diagCoefs_[owner]+flux_;
            //diagCoefs_[owner]=diagCoefs_[owner];
        }
    }

    for (int i=0; i<this->m_N; i++)
    {
        tripletList.push_back(T(i,i,diagCoefs_[i]));
    }

    A_.setFromTriplets(tripletList.begin(), tripletList.end());

    return A_;
}


Eigen::VectorXd scalarField::divb_explicit(calculatedVectorField& Uf_, simulation& simu_, mesh& mesh_)
{
    Eigen::VectorXd b_=Eigen::VectorXd::Zero(this->m_N);

    for (int k=0; k<mesh_.getF(); k++) // loop on the faces
    {
        int owner=mesh_.getOwnerList()[k];
        int neighbour=mesh_.getNeighbourList()[k];
        double flux_=Uf_.getUx()[k]*mesh_.getFaces()[k]->getSfx()+Uf_.getUy()[k]*mesh_.getFaces()[k]->getSfy();


        if (neighbour>=0) //internal face
        {
            //central difference scheme
            b_(owner)=b_(owner)+flux_*(0.5*this->valueCurrent[owner]+0.5*this->valueCurrent[neighbour]);
            b_(neighbour)=b_(neighbour)-flux_*(0.5*this->valueCurrent[owner]+0.5*this->valueCurrent[neighbour]);

            //Upwind
            /*if (flux_>0)
            {
                b_(owner)=b_(owner)+flux_*(this->valueOld[owner]);
                b_(neighbour)=b_(neighbour)-flux_*(this->valueOld[neighbour]);
            }
            else
            {
                b_(owner)=b_(owner)-flux_*(this->valueOld[owner]);
                b_(neighbour)=b_(neighbour)+flux_*(this->valueOld[neighbour]);
            }*/
        }
        else
        {
                b_(owner)=b_(owner)+flux_*(this->valueOld[owner]);
        }

    }



    return b_;
}

