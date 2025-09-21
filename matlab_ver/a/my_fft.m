function after_fft_vectory = my_fft(varargin)
    if length(varargin) == 1
        before_fft_vectory = varargin{1, 1};
        fft_layer = ceil(log2(length(before_fft_vectory)));
        N = 2 ^ fft_layer;
        before_fft_vectory = [before_fft_vectory; zeros(N - length(before_fft_vectory), 1)];
    elseif length(varargin) == 2
        before_fft_vectory = varargin{1, 1};
        N = varargin{1, 2};
        if N < length(before_fft_vectory)
            error('N is less then the length of vector');
        end
        fft_layer = log2(N);
        if fft_layer ~= floor(fft_layer)
            error('N must be a power of 2');
        end
        before_fft_vectory = [before_fft_vectory; zeros(N - length(before_fft_vectory), 1)];
    else
        error('Too much input arguments')
    end

    middle_vectory = before_fft_vectory(bin_rev(fft_layer), 1);

    for i = 1:fft_layer
        gap = 2 ^ (i - 1);
        sub_l = (2 ^ i) - 1;
        for j = 1:(2 * gap):N
            middle_vectory(j:j + sub_l, 1) = subo(middle_vectory(j:j + sub_l, 1), gap);
        end
    end

    after_fft_vectory = middle_vectory;
end