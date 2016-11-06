% Calcul des ordonnées de début et de fin de la portée
% Test Commands
clear all;
close all;
im_corr=correction_biais(imread('Jeregretteun.bmp'));
[H, W]=size(im_corr);
[Py,interligne_moy] = detectioninterligne(im_corr); %im_corr c'est de 0 (noir et des 1 blanc)
localisation = rechechedesxis(Py, W, interligne_moy);
[abscisse_troisieme_ligne, offsetX, Hp, ox] = sous_image_portee(localisation, im_corr, interligne_moy);

H_prime=Hp;
image_corr=im_corr;

%function  Proj_l_final = coordonne_debut_fin(H_prime, abscisse_troisieme_ligne, image_corr, W,interligne_moy,ox,localisation)

% Recherche du premier y tel que proj_l(y)<2. Je propose une dichotomie :
% Partir de la moitié et de 0

sl=interligne_moy;
e0=1;
n=1;

% Précision : arbitraire.
precision=15;
i=1; % on traite la première image
delta_x = floor(e0/2)+1; % on en aura besoin dans les boucles
a=1;
b=H_prime(n);

%définition de I
I = zeros(H_prime(n),W);
for x_cord=1:H_prime(n)
    I(x_cord,:)=1-image_corr(x_cord+ox(n),:);
end
imshow(I);

y_final=zeros(1,1);
Proj_l_final=zeros(1,sl);
Proj_l=zeros(1,2*floor(sl/2));
y=0;
index = 0;

while (abs(a-b)>precision & index < 2001)
    index=index+1;
    %calcul pour y sur sl
    y=floor((a+b)/2);
    Proj_l_final=zeros(1,sl);

    for m=0:sl-1
        yi=y+m;
        Proj_l=zeros(1,2*floor(sl/2)+1);
        %calcul pour y donné
        for delta_xp=-floor(sl/2):floor(sl/2)
            for k=-2:2
                for deltarond_x=-delta_x:delta_x
                    Proj_l(delta_xp+floor(sl/2)+1)=Proj_l(delta_xp+floor(sl/2)+1)+I(localisation(3+5*(i-1))-1+k*sl+deltarond_x+delta_xp,yi)
                end
            end
        end
        Proj_l_final(m+1)=max(Proj_l);
    end
    boolean=true(1);
    for j=1:sl
        if (Proj_l_final(j)-2.5*e0)<0
            boolean=false(1);
        end
    end
    if boolean
        a=y-sl+1;
    else b=y-sl+1;
    end
    y_final=y-sl+1;
end
