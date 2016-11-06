% %seconde phase: extraction des empans
function [imagesecondephase]=selectionempans(imagesansportee,W,H)
N=1/4*[1 1 0 0 0 0 0 1 1];

imagesecondephase=zeros(H,W);
for x=5:H-4
    for y=1:W
    for j=-4:4
        imagesecondephase(x,y)=imagesecondephase(x,y)+(imagesansportee(x,y))*((-imagesansportee(x+j,y))*N(j+5));
    end
    end
end