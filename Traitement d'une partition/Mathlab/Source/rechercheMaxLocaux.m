function res = rechercheMaxLocaux(vecteur)
% intéret de cette fonction ??? findpeak marche aussi ???

    i = 0;
    restemp = zeros(length(vecteur), 1);
    x = 2;
    while x < length(vecteur)
        if vecteur(x-1) < vecteur(x) & vecteur(x) > vecteur(x+1)
            i = i+1;
            res(i) = x;
        end;
    end
