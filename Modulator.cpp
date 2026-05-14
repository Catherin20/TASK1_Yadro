#include "Modulator.h"
#include <cmath>

Modulator::Modulator(int modulationOrder) {
	M = modulationOrder;
	BitsPerSymbol = log2(M);
}

vector<Complex> Modulator::modulate(
	const vector<int>& bits)
{
	vector<Complex> symbols;

	for (size_t i = 0;
		i < bits.size();
		i += BitsPerSymbol)
	{
		int value = 0;

		for (int j = 0;
			j < BitsPerSymbol;
			j++)
		{
			value = (value << 1) | bits[i + j];
		}
		symbols.push_back(
			mapToConstellation(value));
	}
	return symbols;
}

Complex Modulator::mapToConstellation(int value) {
	// QPSK
	if (M == 4) {
		double I = (value & 1) ? 1.0 : -1.0;
		double Q = (value & 2) ? 1.0 : -1.0;

		return Complex(I, Q) / sqrt(2.0);
	}

	// QAM-16
	else if (M == 16) {
		int I = value >> 2;
		int Q = value & 0b11;

		double Lev[4] = { -3, -1, 1, 3 };
		return Complex(Lev[I], Lev[Q]) / sqrt(10.0);
	}
	// QAM-64
	else if (M == 64) {
		int I = value >> 3;
		int Q = value & 0b111;

		double Lev[8] = { -7, -5, -3, -1, 1, 3, 5, 7 };
		return Complex(Lev[I], Lev[Q]) / sqrt(42.0);
	}
	return Complex(0, 0);
}