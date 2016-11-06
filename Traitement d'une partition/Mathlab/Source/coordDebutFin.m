% coordonnees debut fin


% Test Commands

% clear all;
% close all;
% % 
% epaisseurMoy = 1;
% imageCorr = correction_biais(imread('Jeregretteun.bmp'));
% [H, W]=size(imageCorr);
% [Py,interligneMoy] = detectioninterligne(imageCorr); 
% localisation = rechechedesxis(Py, W, interligneMoy);
% [abscisse_troisieme_ligne, offsetX, Hp, ox] = sous_image_portee(localisation, imageCorr, interligneMoy);
% imageCorr = 1 - imageCorr;
function [ydebut,yfinal] = coordDebutFin(Hp, imageCorr, W, interligneMoy, ox, localisation, epaisseurMoy)

% Initialisation des bornes de sommmation.
e0 = 1;
Np = floor(length(localisation)/5);
boundx = floor(interligneMoy / 2);
gdx = floor(e0 / 2) + 1;
ydebut=zeros(1,Np);
yfinal=zeros(1,Np);
for n=1:Np
    
% Créons tout d'abord l'image que l'on souhaite utiliser.
I = zeros(Hp(n), W);
for x = 1 : Hp(n)
    I(x,:) = imageCorr(x + ox(n), :);
end


% Initialisation du résultat.
Proj_l = zeros(W, 1);


% Génération des xi.

xp = zeros(Np,1);
for j = 0 : Np-1
    xp(j+1) = localisation(3+5*j);
end


% Remplissage du résultat.
y = 1;
yd = 0;
yf = 0;
while (y <= W)
    for dxp = -boundx : boundx
        alpha = 0;
        for k = -2 : 2
            for dx = -gdx : gdx
                alpha = alpha + I(xp(n) + k*interligneMoy + dx + dxp - ox(n), y);
            end
        end
        if alpha > Proj_l(y)
            Proj_l(y) = alpha;
        end
    end
    if (Proj_l(y) > 5 / 2 * epaisseurMoy)
        yf = y;
        if (yd == 0)
            yd = y;
        end
    end
    y = y + 1;
end
ydebut(n)=yd;
yfinal(n)=yf;
end   
                
                
                
                
                
                
