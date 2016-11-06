% Extraction des sous images correspondant à une portée 


% clear all
% close all
% rechechedesxis;


function [abscisse_troisieme_ligne, offsetX, H_prime, ox,cellule_image] = sous_image_portee(localisation, image_corr, interligne_moy)

    Np = floor(length(localisation)/5);
    xc = zeros(Np,1);
    ox = zeros(Np,1);
    H_prime = zeros(Np,1);
    [H, W]=size(image_corr);

    
% Il faut déterminer les x(i)
    x = zeros(Np,1);
    for j = 0 : Np-1
        x(j+1) = localisation(3+5*j);
    end


% Les Pixels sont des entiers.
    sl=floor(interligne_moy);

    
% Initialisation du découpage.

    xc(1)=0;
    for i=2:Np
        xc(i)=floor((x(i-1)+x(i))/2);       % Découpage naif
        ox(i)=xc(i)-2*sl;                   % Définition de l'origine
        H_prime(i-1)=xc(i)+2*sl-ox(i-1);    % Définition de la hauteur
    end
    H_prime(Np)=H-ox(Np); 
% 
% %   On construit la famille d'image qui correspond donc à I(x+ox(i),y) pour 0<x<H(i)
 
cellule_image=cell(1,Np);
for i=1:Np
          I=zeros(H_prime(i),W);
          for x_cord=1:H_prime(i)
              I(x_cord,:)=image_corr(x_cord+ox(i),:);
          end
          cellule_image(1,i)=mat2cell(I);
       figure
       imshow(I)
end

% offsetX comportera en fait l'offset. Hprime comporte la longueur de
% chaque portion.

    offsetX = ox;

    % Underscore le retour ! - Paul dit : "C'est insupportable."
    abscisse_troisieme_ligne=zeros(Np,1);
    for i=1:Np
        abscisse_troisieme_ligne(i)=x(i)-ox(i);
    end


