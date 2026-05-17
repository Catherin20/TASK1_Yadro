#include "AWGNChannel.h"
#include <cmath>

AWGNChannel::AWGNChannel(double Var)
	: distribution(0.0, sqrt(Var/2.0))	// Так как шум комплексный для каждой из частей дисперсия в 2 раза меньше
{
}

vector<Complex> AWGNChannel::addNoise(const vector<Complex>& symbols)
{
	vector<Complex> NoiseSym;

	for (auto s : symbols) {
		double NoiseI = distribution(generator);
		double NoiseQ = distribution(generator);
		Complex NSym = s + Complex(NoiseI, NoiseQ);
		NoiseSym.push_back(NSym);
	}
	return NoiseSym;
}