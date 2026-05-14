#include <vector>		// для динамических массивов
#include <complex>		// для комплексных чисел

using namespace std;
typedef complex<double> Complex;

class Modulator {
private:
	int M;				// Порядок модуляции
	int BitsPerSymbol;	// Количество бит на символ
public:
	Modulator(int modulationOrder);
	vector<Complex> modulate(const vector<int>& bits);
private:
	Complex mapToConstellation(int value);
};