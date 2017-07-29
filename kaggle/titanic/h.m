function [out] = h(theta, T)
    m = size(T, 1);
    z = -(T * theta);
    out = ones(m, 1) ./ (ones(m, 1) .+ repmat(e, m, 1) .^ z);