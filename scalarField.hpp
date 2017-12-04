#ifndef scalarFieldHeader
#define scalarFieldHeader

#include <string>
#include <vector>
#include <Eigen/Sparse>
typedef Eigen::SparseMatrix<double> SpMat; // declares a column-major sparse matrix type of double



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
    SpMat ddtA(simulation&);
    Eigen::VectorXd ddtb(simulation&);



    void initialize(mesh&);
    void writeSF(simulation&);
    void update(Eigen::VectorXd&);
    SpMat divA(calculatedVectorField&, simulation&);
    //Eigen::vectorXd divb(vectorField);
};


#endif
