function [Tnorm, move, sigma] = norm(T)
    m = size(T, 2);
    move = mean(T, 1);
    sigma = ones(1, m) ./ (max(T) - min(T));
    Tnorm = (T .- move) .* sigma;