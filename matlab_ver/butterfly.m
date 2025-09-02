function [o1, o2] = butterfly(i1, i2, W)
    o1 = i1 + (W * i2);
    o2 = i1 - (W * i2);
end