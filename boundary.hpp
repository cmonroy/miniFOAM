#ifndef boundaryHeader
#define boundaryHeader

#include <string>
#include <vector>

#include "face.hpp"

using namespace std;

class boundary
{
	std::vector<int> m_listOfFaces;

	//cell* m_owner;
	//cell* m_neighbour;

public:
	boundary(face*);
};


#endif
