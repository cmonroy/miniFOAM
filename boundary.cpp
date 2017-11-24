#include "cell.hpp"
#include <string>

using namespace std;

cell::cell()
{
	m_alpha = 0;   
	m_alpha_o = 0;
	m_alpha_oo = 0;
	m_U = 0;
	m_V = 0;	
}

void cell::advanceInTime()
{
	m_alpha_oo=m_alpha_o;
	m_alpha_o=m_alpha;
}

void cell::splitCell()
{
}
