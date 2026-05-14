#include <iostream>
#include <fstream>
#include <vector>
#include <random>

#include "Modulator.h"
#include "Demodulator.h"
#include "AWGNChannel.h"

double calculateBER(
    const vector<int>& txBits,
    const vector<int>& rxBits)
{
    int errors = 0;

    for (size_t i = 0; i < txBits.size(); i++) {
        if (txBits[i] != rxBits[i])
            errors++;
    }

    return (double)errors / txBits.size();
}

using namespace std;
void Model(int M, const string& filename)
{
    cout << "Test for M = " << M << endl;
    int bitsPerSym = static_cast<int>(log2(M));
    // Количество бит
    int NumBits = 1000000 * bitsPerSym;

    vector<int> txBits;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> BitDistrib(0, 1);

    for (int i = 0; i < NumBits; i++) {
        txBits.push_back(BitDistrib(gen));
    }

    Modulator modulator(M);
    Demodulator demodulator(M);

    vector<Complex> txSymbols = modulator.modulate(txBits);
    ofstream file(filename);

    for (double Var = 0.001; Var <= 0.5; Var += 0.02) {
        AWGNChannel channel(Var);
        vector<Complex> rxSymb = channel.addNoise(txSymbols);
        vector<int> rxBits = demodulator.demodulate(rxSymb);
        double BER = calculateBER(txBits, rxBits);

        file << Var << " " << BER << endl;
        cout << "M=" << M
            << " Var=" << Var
            << " BER=" << BER << endl;
    }
    file.close();
}

int main()
{
    Model(4, "QPSK.txt");
    Model(16, "QAM16.txt");
    Model(64, "QAM64.txt");
    return 0;
}