function[ME] = tatouage(M)

    T = [ 0 0 0 0 0 0 0 ; 0 0 0 0 0 0 0 ; 0 0 0 0 0 0 0 ; 0 0 0 0 0 0 0 ; 0 0 0 0 0 0 0; 0 0 0 0 0 0 0; 0 0 0 0 0 0 0];

    [w,h] = size(M);
    [wm,hm] = size(T);

    ME = fft2(M);

    for i=1:wm
        for j=1:hm
            ME(w-wm+i,h-hm+j) = T(i,j);
        end
    end


end
