#ifndef scalarFieldHeader
#define scalarFieldHeader

#include <string>
#include <vector>
#include <Eigen/Dense>

using Eigen::VectorXd;
//using namespace std;

class mesh;
class simulation;
class calculatedVectorField;

class scalarField
{
    std::string m_name;
    int m_N;
	std::vector<double> valueCurrent;
	std::vector<double> valueOld;

public:
	scalarField(std::string, mesh&);
    Eigen::MatrixXd ddtA(simulation&);
    Eigen::VectorXd ddtb(simulation&);
    void initialize(mesh&);
    void writeSF(simulation&);
    void update(Eigen::VectorXd&);
    Eigen::MatrixXd divA(calculatedVectorField&, simulation&);
    //Eigen::vectorXd divb(vectorField);
};


#endif
