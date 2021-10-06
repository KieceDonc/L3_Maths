function[M] = recadrage(M,a,b)
    a = double(a)/255;
    b = double(b)/255;
    
    MaxM = double(max(max(M)));
    MinM = double(min(min(M)));
   

    M = ((M-MinM)/(MaxM-MinM))*(b-a)+a
end