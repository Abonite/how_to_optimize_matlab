function out_points = subo(source_points, gap)
    %gap同时用来索引蝶形运算第二个点与第一个点的间隔
    %每一个子组内，要进行的蝶形运算数量为本组点数长度的一半
    %这里也对应了第六和第七条规则
    loop_t = length(source_points) / 2;
    %输出点数则与输入点数相同
    out_points = zeros(length(source_points), 1);
    %本次计算的点数？
    N = length(source_points);
    for l = 1:loop_t
        %按图索骥，k应该从0开始，这里是从1开始的，要减去1
        k = l - 1;
        %这里对应了ppt中的第四条规则
        %exp就是e的某次方，1i就是虚数单位i
        W = exp(-1i * 2 * pi * k / N);
        %如图所示，不管在哪一层，蝶形运算的第一个点都是从本组的第一个点开始，依次计算到
        %本组的一半的
        i_a = source_points(l, 1);
        i_b = source_points(l + gap, 1);
        %这里对应了ppt中的第三条规则
        [o_a, o_b] = butterfly(i_a, i_b, W);
        %从哪里取得的数据，就放回哪里。对应
        out_points(l, 1) = o_a;
        out_points(l + gap, 1) = o_b;
    end
end