function index_bin_rev_seq = bin_rev(N, fft_layer)
    %显然，输入点数数量N就是需要进行比特反序的索引数量
    %只不过比特反序的索引是从0开始的，因此这里也从0开始生成
    org_index_seq = 0:(N - 1);
    
    %要进行比特反序，我们只需考虑最大值占用了多少二进制比特
    %也就是N-1
    %已知N必然是二的幂次，二的幂次使用二进制表示必然是类似10(2^1),100(2^2),1000(2^3),10000(2^4)...
    %的形式，那么N-1必然是1,11,111,1111...的形式，其位宽也就等于对长度N取log2计算结果，也就是表示N时
    %2的幂次。在这里，当然就是fft的层数——fft_layer

    %先创建中间变量，使其行数为层数，列数为反序序列长度，用于将原始的数列
    %拆分成二进制的比特，这样就可以将二进制各个比特位写入各行：
    %   第一行为所有数字的第一比特，第二行为所有数的第二比特，以此类推
    temp_bin_mat = zeros(fft_layer, N);
    %用这个for循环和bitget函数一次取出所有数字的第i比特作为一整行
    for i = 1:fft_layer
        temp_bin_mat(i, :) = bitget(org_index_seq, i);
    end

    %创建输出数列的空数组
    index_bin_rev_seq = zeros(1, N);
    %反序相加。原来的第i行，也就是从低到高数的第i比特
    %要变成现在的从低到高的第fft_layer - i比特。这里的i需要从0开始：
    %   这样的话，移位数为0，则数字为第一位，才可以保证结果正常
    %   这样的话，fft_layer - i 是从1到fft_layer，才能保证正常索引
    %我们需要一次处理一行，用bitshift将这一行内的数字都左移i比特，并将结果
    %与输出的数组相加，这样就可以把数列按比特翻转过来
    for i = 0:(fft_layer - 1)
        index_bin_rev_seq = index_bin_rev_seq + bitshift(temp_bin_mat(fft_layer - i, :), i);
    end
    
    % 由于我们产生的数列是从0开始的，matlab是从1开始的
    % 因此直接加1
    index_bin_rev_seq = index_bin_rev_seq + 1;
end