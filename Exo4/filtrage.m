function[MTFI] = filtrage(M)

    [w,h] = size(M);
    r = 100;

    F = zeros(w,h);
    
    MTF = fft2(M);
    
    for i=1:w
        for j=1:h
            if((sqrt(i*i+j*j))>r)
                F(i,j) = 1;
            end
        end
    end
    figure;
    imshow(F);
    
    MP = MTF.*F;
    MTFI = ifft2(MP);

end
