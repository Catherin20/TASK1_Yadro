#include <vector>
#include <complex>

using namespace std;
typedef complex<double> Complex;

class Demodulator {
private:
	int M;					// Порядок модуляции
	int BitsPerSymbol;		// Количество бит на символ
public:
	Demodulator(int modulationOrder);
	vector<int> demodulate(const vector<Complex>& symbols);
private:
	int LevelDemod(double x, const vector<double>& Lev);
	int DemodSymbol(Complex s);
};