%mise en boite

pour tous les empans verticaux...
    
%traitement d'un empans pour déterminer :
ensemble=zeros(300,2);
while matricepixel~=0
    x=x+1;
    [coordx,coordy]=matricepixel(x,:);
    matricepixel(x,:)=0;
    if imagecorr(coordx,coordy)==0 %cas d'un pixel blanc
        %on ajoute ses coordonnée à la matrice qui représente l'ensemble 
        %des points connexe à lempan !
        ensemble(i,:)=[coordx,coordy];
        
        %on ajoue tous ses voisins au tableau
    
    else
    end
end