clc;
clear;
close all;

ResQPSK  = load('QPSK.txt');
ResQAM16 = load('QAM16.txt');
ResQAM64 = load('QAM64.txt');

% QPSK
VAR_QPSK = ResQPSK(:,1);
BER_QPSK = ResQPSK(:,2);
% QAM-16
VAR_QAM16 = ResQAM16(:,1);
BER_QAM16 = ResQAM16(:,2);
% QAM-64
VAR_QAM64 = ResQAM64(:,1);
BER_QAM64 = ResQAM64(:,2);

% Рисунки
figure("Name", "Зависимость BER от VAR");
semilogy(VAR_QPSK, BER_QPSK, '-or');
hold on;
semilogy(VAR_QAM16, BER_QAM16, '-ob');
semilogy(VAR_QAM64, BER_QAM64, '-og');
grid minor;
xlabel('VAR');
ylabel('BER');
legend('QPSK', 'QAM16', 'QAM64');
