//****************************************************************************//
//    This file is part of miniFOAM, simple, 2D, object-oriented CFD solver.  //
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
#include <Eigen/Dense>
//using namespace Eigen;

using namespace std;



int main()
{

    simulation simu;

	cartesianGrid CG(50, 10.0);

	CG.writeMesh();

    Eigen::MatrixXd A(CG.getN(),CG.getN());
    Eigen::VectorXd b(CG.getN());

    calculatedVectorField Uf("Uf", CG);

    scalarField alpha("alpha", CG);
    alpha.initialize(CG);
    alpha.writeSF(simu);


    while(simu.getT()<simu.getEndTime())
    {
        simu.increment();
		std::cout << simu.getT() << std::endl;

		A=alpha.ddtA(simu); //+alpha.divA(Uf,simu);
        b=alpha.ddtb(simu);

        Eigen::VectorXd x(CG.getN());
        x=A.colPivHouseholderQr().solve(b);

        alpha.update(x);

        alpha.writeSF(simu);

    }


	return 0;

}
