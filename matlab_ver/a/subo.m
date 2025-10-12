function out_points = subo(source_points, gap)
    loop_t = length(source_points) / 2;
    out_points = zeros(length(source_points), 1);
    N = 2 * gap;
    for l = 1:loop_t
        k = l - 1;
        W = exp(-1i * 2 * pi * k / N);
        i_a = source_points(l, 1);
        i_b = source_points(l + gap, 1);
        [o_a, o_b] = butterfly(i_a, i_b, W);
        out_points(l, 1) = o_a;
        out_points(l + gap, 1) = o_b;
    end
end