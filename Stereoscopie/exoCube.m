IG = rgb2gray(imread('cubeG.jpg'));
ID = rgb2gray(imread('cubeD.jpg'));

[h,w] = size(IG);

depth = zeros(h-2,w-2);

disp('début de la boucle');

for y = 2:(h-1)                             % y = indice de ligne
    for xG = 2:(w-1)
        coefMin = -1;                 % lstCoef = stockage des coefficients
        for xD = 2:(w-1)                    % x = indice de colonne
            coef = 0;                       % coef = distance euclidienne du voisinnage 3x3
            for j = -1:1                    % j = indice de ligne dans le voisinnage 3x3
                for i = -1:1                % i = indice de colonne dans le voisinnage 3x3
                    coef = coef + (IG(y+j,xG+i) - ID(y+j,xD+i))^2;      % Calcul de la distance euclidienne : somme des ( xG - xD )^2 
                end
            end
            
            if(coef < coefMin || coefMin < 0)
                coefMin = coef;
                xDMin = xD;
            end
        end
        depth(y-1,xG-1) = (xG - xDMin) ;
    end
end

disp('depth prêt');