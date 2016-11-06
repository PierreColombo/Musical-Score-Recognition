%troisièmephase fusion verticale des empans coupés et mise à jour de la
%carte des empans
function [imagesansportee,cartedesempans]=fusionverticale(imagesansportee,W,H,cartedesempans)
for y=1:W
    x=1;
    while x<H
        if cartedesempans(x,y)~=0
            % cas trou de deux pixels
            if (x+3<H && cartedesempans(x+1,y)==0 && cartedesempans(x+2,y)==0 && cartedesempans(x+3,y)~=0 )
                %mise à jour de l'image et de la carte des empans
                l=cartedesempans(x,y);
                imagesansportee(x+1,y)=1;
                cartedesempans(x+1,y)=l;
                l=l+1;
                imagesansportee(x+2,y)=1;
                cartedesempans(x,y)=l;
                l=l+1;
                x=x+2;
                while ((imagesansportee(x,y))==1 && x<H)
                    l=l+1;
                    cartedesempans(x,y)=l;
                    x=x+1;
                end
                % cas trou d'un pixel
            elseif (x+3<H && cartedesempans(x+1,y)==0 &&  (cartedesempans(x+2,y)~=0) )
                %mise à jour de l'image et de la carte des empans
                l=cartedesempans(x,y);
                imagesansportee(x+1,y)=1;
                cartedesempans(x+1,y)=l+1;
                l=l+1;
                x=x+1;
                while ((imagesansportee(x,y))==1 && x<H)
                    l=l+1;
                    cartedesempans(x,y)=l;
                    x=x+1;
                end
                %rien à faire
            else
                x=x+1;
                
            end
        else
            x=x+1;
        end
        
    end
end