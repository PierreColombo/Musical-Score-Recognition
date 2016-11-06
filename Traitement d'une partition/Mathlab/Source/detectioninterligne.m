% Calcul de l'interligne

% Test Commands

% clear all;
% close all;
% imag = imread('Jeregrette.bmp');


function [Py,interligne_moy] = detectioninterligne(imag)


la = 3;
image_corr=imag-1;
Py=(sum(image_corr'));

autocorr=xcorr(Py);

B=-length(autocorr)/2:1:(length(autocorr)/2-1);
[X, Ind] = max(autocorr);

% On écrase l'autocorrélation sur une largeur arbitraire.

for i = 0 : la
    autocorr(Ind - i) = 0;
    autocorr(Ind + i) = 0;
end
    
    
[v i]=min(-autocorr)
interligne_moy=abs(-floor(length(autocorr)/2)+i)

% Création de Fpy

Fpy = zeros(length(Py), 1);
for x = 1 : length(Py)
    for k = -2 : 2
        for i = -1:1
            Fpy(x) = Fpy(x) + Py(min(max(x+k*interligne_moy+i,1), length(Py)));
        end
    end
end
Fpy = - Fpy;


% Test Data

% figure
% plot(B,auto_cor);
% figure
% plot(Fpy);





