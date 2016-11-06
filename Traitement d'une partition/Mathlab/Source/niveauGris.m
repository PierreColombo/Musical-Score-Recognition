% Seuil est en pourcentages ; im est une image à 3 bits de couleurs.

function imageNB = niveauGris(im, seuil)

ima = double(im);
[X,Y,Z] = size(ima);
imageNB = zeros(X,Y);
M = max(max(max(ima)));
m = min(min(min(ima)));
 
for x = 1:X
    for y = 1:Y
        A = 0;
        for z = 1:Z
            A = A + (ima(x,y,z)-m)^2;
        end
        if ((sqrt(A) /(sqrt(3)*M)) < seuil/100)
            imageNB(x,y) = 1;
        end
    end
end
imageNB = 1 - imageNB;