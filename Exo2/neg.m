function[M] = neg(M)
    M = rgb2gray(M);
    M = double(M)/double(max(max(M)));
    M = 1-M;
end