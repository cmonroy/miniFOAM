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
#ifndef faceHeader
#define faceHeader

#include <string>
#include <vector>
#include "point.hpp"

using namespace std;

class face
{
	double m_Sfx;
	double m_Sfy;

	double m_length;

	int m_label;
 	std::vector<int> m_labelList;  //dans le cas 3D, m_labelList(3) ou m_labelList(4) ... à modifier


public:
	face(int, point&, point&);  //dans le cas 3D, créer 2 constructeurs différents (à partir de 3 points et de 4 points)
	vector<int> getLabelList() const { return m_labelList; };
	int getLabel() const { return m_label; };
	double getSfx() const { return m_Sfx; };
	double getSfy() const { return m_Sfy; };
	//~cartesianFace();
};


#endif
