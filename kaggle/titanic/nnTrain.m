function [Theta1, Theta2, Theta3] = nnTrain(X, y, hidden_layer_size_1, hidden_layer_size_2, maxIter)
lambda = 0.2;

input_layer_size = size(X, 2);
num_labels = size(y, 2);

Theta1 = randInitializeWeights(input_layer_size, hidden_layer_size_1);
Theta2 = randInitializeWeights(hidden_layer_size_1, hidden_layer_size_2);
Theta3 = randInitializeWeights(hidden_layer_size_2, num_labels);

initial_nn_params = [Theta1(:); Theta2(:); Theta3(:)];


% Create "short hand" for the cost function to be minimized
costFunction = @(p) nnCostFunction(p, ...
                                   input_layer_size, ...
                                   hidden_layer_size_1, ...
                                   hidden_layer_size_2, ...
                                   num_labels, X, y, lambda);

options = optimset('MaxIter', maxIter);
% Now, costFunction is a function that takes in only one argument (the
% neural network parameters)
[nn_params, cost] = fmincg(costFunction, initial_nn_params, options);

% Obtain Theta1 and Theta2 back from nn_params
Theta1_size = hidden_layer_size_1 * (input_layer_size + 1);
Theta2_size = hidden_layer_size_2 * (hidden_layer_size_1 + 1);
Theta3_size = num_labels * (hidden_layer_size_2 + 1);

Theta1 = reshape(nn_params(1:Theta1_size), ...
                 hidden_layer_size_1, (input_layer_size + 1));

Theta2 = reshape(nn_params((1 + Theta1_size):(Theta1_size + Theta2_size)), ...
                 hidden_layer_size_2, (hidden_layer_size_1 + 1));

Theta3 = reshape(nn_params((1 + Theta1_size + Theta2_size):end), ...
                 num_labels, (hidden_layer_size_2 + 1));
end