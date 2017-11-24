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
#include "cartesianGrid.hpp"
#include "cell.hpp"
#include "point.hpp"
#include "face.hpp"
#include <string>

using namespace std;



cartesianGrid::cartesianGrid(int a, float size) : mesh()
{
	n=a;
	L=size;

	totalNumberOfPoints=(n+1)*(n+1);
	totalNumberOfFaces=2*n*(n+1);
	totalNumberOfCells=n*n;

	float x(0.);
	float y(0.);
	int i(0);
	int j(0);
	int l(0);

// Creation of points
	for (j = 0; j < n+1; j++)
	{
		y=j*L/n;
		for (i = 0; i < n+1; i++)
		{
			l=j*(n+1)+i;
			x=i*(float)L/n-(float)L/2;
			y=j*(float)L/n-(float)L/2;
			points.push_back(new point(l,x,y));
		}
	}

// Creation of faces
	for (j = 0; j < n+1; j++)
	{
		for (i = 0; i < n; i++)
		{
			l=j*n+i;
			faces.push_back(new face(l, *points[j*(n+1)+i], *points[j*(n+1)+i+1]));
		}
	}
	for (j = 0; j < n; j++)
	{
		for (i = 0; i < n+1; i++)
		{
			l=n*(n+1)+j*(n+1)+i;
			faces.push_back(new face(l, *points[j*(n+1)+i], *points[j*(n+1)+i+n+1]));
		}
	}



// Creation of cells
	for (j = 0; j < n; j++)
	{
		for (i = 0; i < n; i++)
		{
			l=j*n+i;
			cells.push_back(new cell(l, *faces[l], *faces[n*(n+1)+j*(n+1)+i+1], *faces[l+n], *faces[n*(n+1)+j*(n+1)+i]));
		}
	}


// Creation of owner and neighbour
	j=0;
	for (i = 0; i < n; i++)
	{
		l=j*n+i;
		owner.push_back(l);
		neighbour.push_back(-1);
	}
	for (j = 0; j < n-1; j++)
	{
		for (i = 0; i < n; i++)
		{
			l=j*n+i;
			owner.push_back(l);
			neighbour.push_back(l+n);
		}
	}
	j=n-1;
	for (i = 0; i < n; i++)
	{
		l=j*n+i;
		owner.push_back(l);
		neighbour.push_back(-3);
	}

	for (j = 0; j < n; j++)
	{
		i=0;
		l=n*(n+1)+j*n+i;
		owner.push_back(j*n+i);
		neighbour.push_back(-4);

		for (int i = 1; i < n; i++)
		{
			l=n*(n+1)+j*n+i;
			owner.push_back(j*n+i-1);
			neighbour.push_back(j*n+i);
		}
		i=n;
		l=n*(n+1)+j*n+i;
		owner.push_back(j*n+i-1);
		neighbour.push_back(-2);
	}

}



