%selection d'un unique empan verticale grâce à une fenêtre
function [cartefinalempans]=selectionuniqueempan(interligne_moy,W,H,cartefinalempans)

largeurfenetre=2*floor(interligne_moy/5);
for y=1:W
    x=H;
    while x>1
        if cartefinalempans(x,y)==0
            x=x-1;
        else
            longueur_empan_courant=cartefinalempans(x,y);
            %recherche du maximum du tableau de longueur largeur fenetre et
            %de hauteur longueur_empan_courant
            Vx=(x-longueur_empan_courant):x;
            Vy=(y):min((y+largeurfenetre),W);
            Tableau=cartefinalempans(Vx,Vy);
            [valeur ,xindicerelatif] =max(Tableau);
            xindiceabsolu=xindicerelatif+x-1;
            [valeurmaximale ,yindicerelatif]=max(valeur);
            %on selectionne le premier empan maximal qu'on trouve
            if valeurmaximale==longueur_empan_courant
                cartefinalempans(x-(longueur_empan_courant):x+1,y+1:y+largeurfenetre)=0;
                x=x-longueur_empan_courant;
             else
                cartefinalempans(x-longueur_empan_courant:x,y)=0;
                x=x-longueur_empan_courant;
                
            end
        end
    end
end
