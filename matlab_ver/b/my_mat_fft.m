function after_fft_vectory = my_mat_fft(source_point)
    N = length(source_point);
    N = 2 ^ ceil(log2(N));
    source_point = [source_point; zeros(N - length(source_point), 1)];

    fft_mat = zeros(N, N);
    for row = 1:N
        for col = 1:N
            fft_mat(row, col) = exp((row - 1) * (col - 1) * -2 * pi * 1i / N);
        end
    end

    after_fft_vectory = fft_mat * source_point;
end