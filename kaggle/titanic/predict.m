function [Y] = predict(theta, X, t)
    n = size(X, 1);
    out = h(theta, X);
    Y = zeros(n, 1);
    for i=[1:n]
        if out(i) > t
            Y(i) = 1;
        else
            Y(i) = 0;
        end
    end