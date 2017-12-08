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
#include <iostream>
#include "cartesianGrid.hpp"
#include "simulation.hpp"
#include "scalarField.hpp"
#include "calculatedVectorField.hpp"
#include <Eigen/Sparse>


using namespace std;

typedef Eigen::SparseMatrix<double> SpMat; // declares a column-major sparse matrix type of double


int main()
{

    simulation simu;

	cartesianGrid CG(25, 10.0);

	CG.writeMesh(simu);

    SpMat A(CG.getN(),CG.getN());
    Eigen::VectorXd b(CG.getN());

    calculatedVectorField Uf("Uf", CG);
    Uf.initialize(CG);

    scalarField alpha("alpha", CG);
    alpha.initialize(CG);
    //alpha.writeSF(simu);
    alpha.writeXYandSF(CG, simu);

    while(simu.getT()<simu.getEndTime())
    {
        simu.increment();
		std::cout << simu.getT() << std::endl;


        // Building linear system
		A=alpha.ddtA(simu)+alpha.divA(Uf,simu,CG);
        b=alpha.ddtb(simu);

        // Solving:
        Eigen::SimplicialCholesky<SpMat> chol(A);  // performs a Cholesky factorization of A
        Eigen::VectorXd x = chol.solve(b);         // use the factorization to solve for the given right hand side

        // Updating alpha field:
        alpha.update(x);

        // Writing alpha field:
        //alpha.writeSF(simu);
        alpha.writeXYandSF(CG, simu);
    }


    simu.writeVisuFile();

	return 0;

}
