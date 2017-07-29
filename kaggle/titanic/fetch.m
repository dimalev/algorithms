function [out] = fetch(T, V, v)
  m = length(V);
  out = [];
  for i=[1:m]
      if V(i) == v
          out = vertcat(out, T(i, :));
      end
  end    