function x = clamp_limit(x, x_min, x_max)
%x = CLAMP_LIMIT(x, x_min, x_max) Limits x to range [x_min, x_max]
    x = min(max(x_min, x), x_max);
end