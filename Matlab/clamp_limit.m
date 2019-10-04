function x = clamp_limit(x, x_min, x_max)
%LIMIT Returns values of x limited to range [val_min, val_max]
%   x = Input
%   x_min = Minimum value
%   x_max = Maximum value
    x = min(max(x_min, x), x_max);
end