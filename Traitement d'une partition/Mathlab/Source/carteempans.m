%premiere phase : carte codant la longueur de empans verticaux noirs
function [cartedesempans]=carteempans(imagesansportee,W,H)

%les portée doivent être à un !


cartedesempans=zeros(H,W);
%parcours de l'image selon les x croissants ! les empants seront donnés
%vers le haut !

for y=1:W
x=1;
    while x<H
        l=0;
        if (imagesansportee(x,y))~=1
            x=x+1;
        else
            while ((imagesansportee(x,y))==1 && x<H)
                l=l+1;
               cartedesempans(x,y)=l;
               x=x+1; 
             end
        end
    end
end

