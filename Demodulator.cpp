#include "Demodulator.h"
#include <cmath>

Demodulator::Demodulator(int modulationOrder) {
	M = modulationOrder;
	BitsPerSymbol = log2(M);
}

vector<int> Demodulator::demodulate(const vector<Complex>& symbols)
{
	vector<int> bits;

	for (auto s : symbols) {
		int value = DemodSymbol(s);

		for (int i = BitsPerSymbol - 1;
			i >= 0;
			i--)
		{
			bits.push_back((value >> i) & 1);
		}
	}
	return bits;
}
// Демодулятор извлекает биты по минимуму евклидова расстояния
int Demodulator::LevelDemod(double x, const vector<double>& Lev)
{
	double minDist = 1e9;
	int Idx = 0;

	for (int i = 0; i < Lev.size(); i++) {
		double d = abs(x - Lev[i]);
		if (d < minDist) {
			minDist = d;
			Idx = i;
		}
	}
	return Idx;
}

int Demodulator::DemodSymbol(Complex s) {
	// QPSK
	if (M == 4) {
		int bit0 = real(s) > 0 ? 1 : 0;
		int bit1 = imag(s) > 0 ? 1 : 0;
		return bit0 | (bit1 << 1);
	}
	// QAM-16
	else if (M == 16) {
		vector<double> Lev = {
			-3 / sqrt(10.0),
			-1 / sqrt(10.0),
			 1 / sqrt(10.0),
			 3 / sqrt(10.0)
		};
		int bit0 = LevelDemod(real(s), Lev);
		int bit1 = LevelDemod(imag(s), Lev);
		return (bit0 << 2) | bit1;
	}
	// QAM-64
	else if (M == 64) {
		vector<double> Lev = {
			-7 / sqrt(42.0),
			-5 / sqrt(42.0),
			-3 / sqrt(42.0),
			-1 / sqrt(42.0),
			 1 / sqrt(42.0),
			 3 / sqrt(42.0),
			 5 / sqrt(42.0),
			 7 / sqrt(42.0)
		};
		int bit0 = LevelDemod(real(s), Lev);
		int bit1 = LevelDemod(imag(s), Lev);
		return (bit0 << 3) | bit1;
	}
	return 0;
}