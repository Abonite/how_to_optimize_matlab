clear all;

source = 1:1024;
source = source.';

tic;
result = my_fft_cver(source);
toc;