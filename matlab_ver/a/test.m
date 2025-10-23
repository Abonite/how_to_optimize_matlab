clear all;
s = 1:1024;
s = s.';
tic;
result = my_fft(s);
toc;