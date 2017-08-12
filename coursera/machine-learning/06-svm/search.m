function [modelBest, predictionBest, Cbest, sigmaBest, Cvals, sigmaVals, scores] = search(X, y, Xval, yval, Cstart, Cstep, Csteps, sigmaStart, ...
                                     sigmaStep, sigmaSteps)

Cvals = Cstart .* (Cstep .^ [0:Csteps-1]);
sigmaVals = sigmaStart .* (sigmaStep .^ [0:sigmaSteps-1]);
scores = ones(Csteps, sigmaSteps);
predictionBest = 1.1;
for i = 1:Csteps
    for j = 1:sigmaSteps
        model = svmTrain(X, y, Cvals(i), @(x1, x2) gaussianKernel(x1, ...
                                                          x2, sigmaVals(j)));
        prediction = mean(double(yval ~= svmPredict(model, Xval)));
        scores(i, j) = prediction;
        if prediction < predictionBest
            predictionBest = prediction;
            modelBest = model;
            Cbest = Cvals(i);
            sigmaBest = sigmaVals(j);
        end
    end
end
end