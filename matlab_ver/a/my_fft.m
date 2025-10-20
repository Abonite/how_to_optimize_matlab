% “符号体系”
%个人经验
function after_fft_vectory = my_fft(varargin)
    %需求：
    %   输入的点数为列向量复数
    %   可以输入1或2个参数。第一个参数是列向量，第二个是指定的点数
    %   当仅输入一个参数的时候，不足2的幂次的列向量默认在结尾补0到2的幂次
    %   当输入两个参数的时候，默认将列向量补足到指定点数；要求指定点数必须
    %   是一个大于等于列向量长度的2的幂次数
    if length(varargin) == 1
        before_fft_vectory = varargin{1, 1};
        % fft的点数信息隐含在输入序列中，也就是长度
        N = length(before_fft_vectory);
        % 对长度取log2，向上取整，作为fft层数。fft层数不能是小数，遇到非2的幂次
        % 的数字要补数据所以向上取整
        %如何调用函数？如何使用函数的结果？
        %这里对应了第五条规则
        fft_layer = ceil(log2(N));
        % 重新计算点数N，保证点数足够
        N = 2 ^ fft_layer;
        % 默认不足时补0到2的幂次
        before_fft_vectory = [before_fft_vectory; zeros(N - length(before_fft_vectory), 1)];
    elseif length(varargin) == 2
        before_fft_vectory = varargin{1, 1};
        N = varargin{1, 2};
        %判断长度是否足够
        if N < length(before_fft_vectory)
            error('N is less then the length of vector');
        end
        %计算层数
        fft_layer = log2(N);
        %判断取整后和没有取整的数字是否一致（有没有小数部分）
        %如果有小数部分（也就是等式不成立），就证明数字N不是2的幂次
        if fft_layer ~= floor(fft_layer)
            error('N must be a power of 2');
        end
        %按照需要补0
        before_fft_vectory = [before_fft_vectory; zeros(N - length(before_fft_vectory), 1)];
    else
        %如果输入参数太多，就报错
        error('Too much input arguments')
    end

    %对输入进行比特逆序，对应ppt第二条规则：输入索引要比特逆序
    middle_vectory = before_fft_vectory(bin_rev(N, fft_layer), 1);

    %依层计算
    for i = 1:fft_layer
        %第一个点与第二个点的间隔
        gap = 2 ^ (i - 1);
        %每一层要计算的“子组”长度。
        %索引一组数时，例如：
        %   取出索引1到10的数字，则matlab就会取出1到10的数字。
        %   按照第63行的做法，j本身位置的数字将会被取出，j+sub_l位置的数字也会取出
        %   所以如果sub_l的长度不减去1，去除的数字长度会多1（j到j+sub_l的长度为sub_l+1)
        %sub_l:sub_length
        sub_l = (2 ^ i) - 1;
        %j，我们使用j代表被处理的组的第一个元素在整个数组中的索引，因此j要
        %每次跳一个子组的长度，实际上就是2 * gap或者sub_l + 1
        %subo:sub_operation
        %这里对应了ppt中的第六和第七条规则
        for j = 1:(2 * gap):N
            middle_vectory(j:j + sub_l, 1) = subo(middle_vectory(j:j + sub_l, 1), gap);
        end
    end

    %这里对应了ppt中的第一条规则
    after_fft_vectory = middle_vectory;
end