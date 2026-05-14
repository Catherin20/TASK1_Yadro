#include <vector>
#include <complex>
#include <random>

using namespace std;
typedef complex<double> Complex;

class AWGNChannel {
private:
	default_random_engine generator;
	normal_distribution<double> distribution;	// Распределение Гаусса
public:
	AWGNChannel(double Var);
	vector <Complex> addNoise(const vector<Complex>& symbols);
};