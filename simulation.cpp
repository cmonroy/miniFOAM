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
#include "simulation.hpp"


#include <iostream>
#include <fstream>


#include <sstream>

using namespace std;


simulation::simulation() //TODO: create a constructor from a dictionnary
{
    t=0;
    dt=0.5;
    L=10.0; //length of the square
    Nx=30; //number of cells in x-direction
    endTime=10.0;
    simulationFolder="C:/Users/cmonroy/Documents/Trash";
    divScheme="centralDiff"; //"upwind" or "centralDiff"
    BC="vonNeuman"; //"vonNeumann" or "Dirichlet"
}


void simulation::increment()
{
    this->t=this->t+this->dt;
}


void simulation::writeVisuFile()
{
    double tvisu=0;
    std::string listOfTimeSteps="timeSteps=[";
    while(tvisu<endTime)
    {
           std::ostringstream strT;
           strT << tvisu;
           listOfTimeSteps=listOfTimeSteps+"\""+strT.str()+"\""+"," ;
           tvisu=tvisu+dt;
    }
    std::ostringstream strT;
    strT << endTime;
    listOfTimeSteps=listOfTimeSteps+"\""+strT.str()+"\"]";

  	std::ofstream pythonFile;
  	pythonFile.open (this->simulationFolder+"/"+"visu.py");
  	pythonFile << "#!/usr/bin/python" << "\n";
  	pythonFile << "# -*- coding: utf-8 -*-" << "\n";

  	pythonFile << "import numpy as np" << "\n";
  	pythonFile << "import matplotlib.pyplot as plt" << "\n";
  	pythonFile << "import matplotlib.cm as cm" << "\n";
  	pythonFile << "import matplotlib.animation as animation" << "\n";
  	pythonFile << "# Set up formatting for the movie files" << "\n";

  	pythonFile << "Writer = animation.writers['ffmpeg']" << "\n";
  	pythonFile << "writer = Writer(fps=15, metadata=dict(artist='Me'), bitrate=1800)" << "\n";
  	pythonFile << "images = []" << "\n";

  	pythonFile << "fig2 = plt.figure()" << "\n";

  	pythonFile << listOfTimeSteps << "\n";
  	pythonFile << "x,y,scalar = np.loadtxt('0/alpha').T #Transposed for easier unpacking" << "\n";
  	pythonFile << "nrows, ncols = "<< Nx <<", " << Nx << "\n";
  	pythonFile << "grid = scalar.reshape((nrows, ncols))" << "\n";
  	pythonFile << "img = plt.imshow(grid, extent=(x.min(), x.max(), y.min(), y.max()), interpolation='nearest')" << "\n";
  	pythonFile << "plt.xlabel('x');" << "\n";
  	pythonFile << "plt.ylabel('y');" << "\n";
  	pythonFile << "plt.colorbar(img);" << "\n";

  	//pythonFile << "plt.show();" << "\n";

  	pythonFile << "for t in timeSteps:" << "\n";
  	pythonFile << " x,y,scalar = np.loadtxt(t+'/alpha').T #Transposed for easier unpacking" << "\n";
  	pythonFile << " nrows, ncols = "<< Nx <<", " << Nx << "\n";
  	pythonFile << " grid = scalar.reshape((nrows, ncols))" << "\n";
  	pythonFile << " img = plt.imshow(grid, extent=(x.min(), x.max(), y.min(), y.max()), interpolation='nearest')" << "\n";
  	pythonFile << " images.append((img,))" << "\n";

  	pythonFile << "alpha_ani = animation.ArtistAnimation(fig2, images)" << "\n";
  	pythonFile << "alpha_ani.save('alpha.mp4', writer=writer)" << "\n";

	pythonFile.close();
}
