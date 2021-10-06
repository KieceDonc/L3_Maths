function[R] = dilat(M)
    a = 30 ;
    b = 80 ;
    c = 120 ;
    [w,h] = size(M);
    
    R = M;
    

    
    slope1 = (c-a)/(b-a);
    yInter1 = a-slope1*a;
    
    slope2 = (255-c)/(255-b);
    yInter2 = c-slope2*b;
    
    for i=1:w
        for j=1:h
            if M(i,j) >= a && M(i,j) < c
                R(i,j) = slope1*M(i,j)+yInter1;
            elseif M(i,j) >= c
                R(i,j) = slope2*M(i,j)+yInter2;
            end
        end
    end

end