%mise en boite

pour tous les empans verticaux...
    
%traitement d'un empans pour d�terminer :
ensemble=zeros(300,2);
while matricepixel~=0
    x=x+1;
    [coordx,coordy]=matricepixel(x,:);
    matricepixel(x,:)=0;
    if imagecorr(coordx,coordy)==0 %cas d'un pixel blanc
        %on ajoute ses coordonn�e � la matrice qui repr�sente l'ensemble 
        %des points connexe � lempan !
        ensemble(i,:)=[coordx,coordy];
        
        %on ajoue tous ses voisins au tableau
    
    else
    end
end