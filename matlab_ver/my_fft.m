function after_fft_vectory = my_fft(after_fft_vectory, N)
    t = log2(N);
    if t ~= floor(t)
        error('N must be a power of 2');
    end

    for i = 1:t
    end
end