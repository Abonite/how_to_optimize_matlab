clear all;
javaaddpath("./fft_a.jar");

java_complex_vector = [];
for i = 1:1024
    java_complex_vector = [java_complex_vector; Complex(i, 0, true)];
end
tic;
my_fft_javaver_in_matlab = my_fft_javaver(java_complex_vector);
result = my_fft_javaver_in_matlab.do_fft();
toc;
matlab_result = zeros(length(result), 1);
for i = 1:length(result)
    matlab_result(i, 1) = result(i, 1).getReal() + 1i * result(i, 1).getImag();
end
