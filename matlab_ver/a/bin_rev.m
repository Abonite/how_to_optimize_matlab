function index_bin_rev_seq = bin_rev(fft_layer)
    org_index_seq = 0:(2 ^ fft_layer) - 1;
    
    % The maximum number of bits of binary sequence
    % is the fft_layer
    temp_bin_mat = zeros(fft_layer, 2 ^ fft_layer);
    for i = 1:fft_layer
        temp_bin_mat(i, :) = bitget(org_index_seq, i);
    end

    index_bin_rev_seq = zeros(1, (2 ^ fft_layer));
    for i = 1:fft_layer
        index_bin_rev_seq = index_bin_rev_seq + (2 ^ (i - 1)) * temp_bin_mat(fft_layer - i + 1, :);
    end
    
    % The original index starts from 0
    % but in matlab, index is start from 1
    index_bin_rev_seq = index_bin_rev_seq + 1;
end