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
#include "face.hpp"
#include <string>
#include <math.h>

using namespace std;

face::face(int l, point& pointA, point& pointB)
{
	m_label = l;
	m_length = pow(pow(pointB.getX()-pointA.getX(),2)+pow(pointB.getY()-pointA.getY(),2),0.5);
	m_Sfx = -(pointB.getY()-pointA.getY());
	m_Sfy = (pointB.getX()-pointA.getX());
	m_labelList.push_back(pointA.getLabel());
	m_labelList.push_back(pointB.getLabel());
}


