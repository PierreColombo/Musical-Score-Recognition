% Histogramme largeur Lignes


% Test Commands 

% close all
% clear all
% imag=double(imread('contre02.JPG'));
% imag = niveauGris(imag, 60);
% 
 function res = HistogrammeLargeurLignes(imag)

[H, W]=size(imag);
histo = zeros(H,1);

% On remplit l'histogramme. Je suis assez fier de cette seconde boucle
% while :D

x = 1;
for y =  floor(W/11) : floor(W/11) : floor(10*W/11)
    while x <= H
        a = 0;
        while ((x <= H) & (imag(x,y) == 0))
            a = a+1;
            x = x+1;
        end
        histo(a+1) = histo(a+1) + 1;
        x = x + 1;
    end
end
histo(1) = 0;
[X,indMax] = max(histo);
A = 0;
B = 0;
for i = indMax-1 : indMax + 1
    A = (i-1) * histo(i) + A;
    B = histo(i) + B;
end
res = A/B;
