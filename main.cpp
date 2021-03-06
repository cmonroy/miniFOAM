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
#include "faceVectorField.hpp"
#include <Eigen/Sparse>


using namespace std;

typedef Eigen::SparseMatrix<double> SpMat; // declares a column-major sparse matrix type of double


int main()
{

    simulation simu;

	cartesianGrid CG(simu.getNx(), simu.getL());

	CG.writeMesh(simu);

	CG.writeFaces(simu);

    SpMat A(CG.getN(),CG.getN());
    Eigen::VectorXd b(CG.getN());

    faceVectorField Uf("Uf", CG);
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
		A=alpha.ddtA(simu,CG)+alpha.divA(Uf,simu,CG);
        b=alpha.ddtb(simu,CG)+alpha.divb(Uf,simu,CG);
        //std::cout << Eigen::MatrixXd(A) << std::endl;
        //std::cout << b << std::endl;
        // Solving:
        //Eigen::SimplicialCholesky<SpMat> chol(A);  // performs a Cholesky factorization of A
        //Eigen::VectorXd x = chol.solve(b);         // use the factorization to solve for the given right hand side

        //std::cout << x << std::endl;

        A.makeCompressed();
         // Create solver
        Eigen::SimplicialLDLT<Eigen::SparseMatrix<double>, Eigen::Lower, Eigen::AMDOrdering<int> > solver;
    // Eigen::ConjugateGradient<Eigen::SparseMatrix<float>, Eigen::Lower> cg;

        // Eigen::ConjugateGradient<Eigen::SparseMatrix<float>, Eigen::Lower> cg;
        solver.analyzePattern(A);
        solver.compute(A);
        if (solver.info() != Eigen::Success)
         {
             std::cerr << "Decomposition Failed" << std::endl;
             getchar();
         }
        Eigen::VectorXd x = solver.solve(b);

       // std::cout << x << std::endl;

        // Updating alpha field:
        alpha.update(x);

        // Writing alpha field:
        //alpha.writeSF(simu);
        alpha.writeXYandSF(CG, simu);
    }


    simu.writeVisuFile();

	return 0;

}
