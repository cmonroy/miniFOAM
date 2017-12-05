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
#ifndef cellHeader
#define cellHeader

#include <string>
#include "face.hpp"

class cell
{
	int m_label;
	float m_alpha; // value at current time step
	float m_alpha_o;	// value at (n-1)
	float m_alpha_oo;	// value at (n-2)
	float m_U;
	float m_V;

 	std::vector<int> m_faceList;

public:
	cell(int, face&, face&, face&, face&); //TODO: extend to an arbitrary number of faces
	//~cell();
	vector<int> getFaceList() const { return m_faceList; };
	void splitCell();
	void advanceInTime();
	float getU() const { return m_U; };
	float getV() const { return m_V; };

};


#endif
