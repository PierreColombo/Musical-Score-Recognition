%quatrième phase: recherche de l'empan de longueur maximal elle doit se
%faire sur une seule sous image
% un seul empant par sous image
function [cartefinalempans]=cartefinaledesempans(imagesecondephase,W,H,interligne_moy,cartedesempansMAJ)
x=1;
cartefinalempans=zeros(H,W);
sl=interligne_moy;
for y=1:W
    [lempanmax, indice]= max(cartedesempansMAJ(:,y)); %% faire peter le x !
    if ((lempanmax>1.5*sl) && (abs(sum(imagesecondephase((indice-lempanmax):indice,y)))>lempanmax/4))
        for j=1:lempanmax
            cartefinalempans(indice-j,y)=lempanmax-j;
        end
    end
    
end
% la nouvelle carte contient en case (i,j) la valeur de l'empan qui
% s'étends vers le haut