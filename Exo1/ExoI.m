I = imread('default.jpg')
J = rgb2gray(I)
K = double(J)/double(max(max(J)))
imshow(K)
F = [-1 -1 -1,-1 8 -1,-1 -1 -1]
B = [1 1 1, 1 4 1,1 1 1]
Q = filter2(B,K);
Q = double(Q)/double(max(max(Q)))
imshow(Q);


