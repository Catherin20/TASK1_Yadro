#include "AWGNChannel.h"
#include <cmath>

AWGNChannel::AWGNChannel(double Var)
	: distribution(0.0, sqrt(Var))
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