function [theta_best] = J(theta, alpha, iterations, X, Y)
    m = size(X, 1);
    n = size(X, 2);
    theta_best = theta;
    for i=[1:iterations]
        p = h(theta_best, X) .- Y;
        theta_best -= repmat(alpha / m, n, 1) .* X' * p;
    end