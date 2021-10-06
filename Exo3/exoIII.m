function[ME] = exoIII(ME)
    ME = rgb2gray(ME);
    ME = double(ME)/double(max(max(ME)));
    for i = 1:size(ME,1)
        for j = 1:size(ME,2)
            if ME(i,j) > 0.3 && ME(i,j) < 0.7
                ME(i,j) = 0.5;
            end
        end
    end
end