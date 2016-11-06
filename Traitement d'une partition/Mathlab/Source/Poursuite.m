% Algo de Poursuite.
% n est le numéro de la portée que l'on souhaite poursuivre.


% Test Data


function xfo = Poursuite(e0, sI, Hp, imageCorr, ox, W, n, xpa)

    % Récupération de l'image
    
    xp = xpa(n);
    I = zeros(Hp(n), W);
    for x = 1 : Hp(n)
        I(x,:) = imageCorr(x + ox(n), :);
    end


    % Construction du Masque

    H2p = 2*floor(2.5*sI);
    Mp = zeros(H2p, 1);
    deltab = floor(e0/2);
    deltak = e0 - 1 - deltab;
    for k = -2:2
        for i = -deltab:deltak
            Mp(H2p/2 + k*sI + i) = 1;
        end
    end
    
    % Initialisation du Filtrage
    
    C = zeros(2*floor(sI/2)+1, W);
    
    for xd = -floor(sI/2):floor(sI/2)
        for yd = 1 : W
            for k = 0 : Hp - 1
                C(xd, yd) = C(xd, yd) + (1/Hp)*(Mp(x)*I(x+xp-Hp/2+xd, yd));
            end
        end
    end
    
    % Poursuite de la portée
    
    Cfo(:, :) = C(:, :);
    alpha = 0.98;
    for xd = -floor(sI/2):floor(sI/2)
        for yd = 2 : W
            Cfo(xd, yd) = alpha*Cfo(xd, yd-1) + (1-alpha)*C(xd, yd);
        end
    end
    
    
    xfo = zeros(W, 1);
    
    for y = 1 : W
        xdmax = 0;
        for xd = -floor(sI/2):floor(sI/2)
            if Cfo(xd, y) > xdmax
                xdmax = Cfo(xd,y);
            end
        end
        xfo(y) = xp + xdmax;
    end
        
    
    
    
    
    
    
    
    
    
    