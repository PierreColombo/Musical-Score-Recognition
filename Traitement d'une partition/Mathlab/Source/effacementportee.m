% effacement des portées
% 
 function[imagesansportee] = effacementportee(im_corr,localisation,ydebut,yfin,emoy)

% %données tests
% close all
% clear all
% im_corr=correction_biais(imread('Jeregretteun.bmp'));
% [H, W]=size(im_corr);
% [Py,interligne_moy] = detectioninterligne(im_corr); %im_corr c'est de 0 (noir et des 1 blanc)
% localisation = rechechedesxis(Py, W, interligne_moy);
% [abscisse_troisieme_ligne, offsetX, Hp, ox] = sous_image_portee(localisation, im_corr, interligne_moy);

image_corr=1-im_corr;


se=floor(emoy)+3;
x=0;
[C B]=size(image_corr)
for y=ydebut:yfin
    for x=localisation
        xh=x;
        xb=x;
                %détermination de xb
                while (image_corr(xb,y)==1 && xb<C)
                    xb=xb+1;
                end
                %détermination de xh
                while (image_corr(xh,y)==1 && xh<C)
                    xh=xh-1;
                end
                A=(se>= (xb-xh+1)) && (xb < (x+se)) && (xh>(x-se));
        if (A)
            image_corr(xh-1:xb+1,y)=0;
        end
    end
end
imagesansportee=image_corr;
% imshow(1-image_corr)
% title('image corrigée')