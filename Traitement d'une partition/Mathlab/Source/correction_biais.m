% fonction qui permet de corriger le biais d'une image


% Test Lines

% close all
% clear all
% imag=double(imread('test-15.bmp'));
% imag=double(imread('contre02.JPG'));

 



function res = correction_biais(imag)

[H, W]=size(imag);
imag1 = niveauGris(imag, 50);
 
% On donnne plein de poids au noir
imag=imag1-1;
[H, W]=size(imag);

image_un=imag(:,1:floor(W/2));
image_deux=imag(:,floor(W/2)+1:W);

% trace de l'image
% imshow(image_un);
   auto_cor = xcorr2(image_un,image_deux);
   C = 2 / (W*H) * auto_cor(:,floor(W/2));
  
   B= (-length(C) / 2 : 1 : length(C)/2 - 1);
   
  % plot(B,C)
  %xlim([-200 200])
  [valeur, indice] = max(C);
  hmax = (indice - floor(length(C)/2) );
  theta=atand(hmax/((W/2)));
 
  image_corr=zeros(H+abs(hmax),W);
  image_corr(image_corr==0)=1; 
   for y=1:W
       x = 1;
       a = x - floor(2*hmax*y/W) + min(0,hmax);
       while(a < H & x < H + min(0, hmax) + abs(hmax))
       % for x=1 : (H+abs(hmax)+ min(0, hmax))
       % Ancienne boucle for pour comprendre what's happening. Il y a une
       % façons plus intelligente de résoudre ce problème, avec un seul
       % test calibré sur la valeur de a qui n'est en fait qu'un offset de
       % x, mais on veut AVANCER, donc ça suffira pour le moment.
          image_corr(x,y) = imag1(max(min(H, x - floor(2*hmax*y/W) + min(0,hmax)), 1) , y);
          x = x+1;
          a = a+1;
       end 
   end
  res = image_corr;
 
  % imshow(res);
