clear all;

source = 1:1024;
source = source.';

tic;
result = my_mat_fft(source);
toc;