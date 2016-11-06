% Test
clear all;
close all;

% %le test n'est pas op il manque les y debuts et y fin et ta poursuite des
% %portées..

% sélection de l'image test 
% im_corr=correction_biais(imread('contre02.bmp'));
% im_corr=correction_biais(imread('hardstuff.bmp'));
im_corr=correction_biais(imread('Jeregrette.bmp'));


%correstion du biais éventuel de l'image
%im_corr=correction_biais(imread('FillesLangast.bmp'));
[H W]=size(im_corr);

%determination des critères géométriques globaux
[Py,interligne_moy] = detectioninterligne(im_corr); %im_corr c'est de 0 (noir et des 1 blanc)
localisation = rechechedesxis(Py, W, interligne_moy);

% découpage en sous images correspondant à chaque portée
[abscisse_troisieme_ligne, offsetX, Hp,ox,cellule_image] = sous_image_portee(localisation, im_corr, interligne_moy);

%Calcul de la largeur des lignes
emoy=floor(HistogrammeLargeurLignes(im_corr));

%Coord debutfin qui sont des vecteurs 
[ydebut,yfinal] = coordDebutFin(Hp, 1-im_corr, W, interligne_moy, ox, localisation,emoy)
Np=floor(length(localisation)/5);
%chagement des coordonnées de localisation pour que ca marche bien
i=1;
H=zeros(1,Np+1);

%mise à jour de localisation
while i<floor(Np)
    for j=1:5
         [H(1,i+1) ~]=size(cell2mat(cellule_image(1,i)));
    localisation(5*i+j)=localisation(5*i+j)-ox(i+1);
%     H(1,i+1);
    end 
    i=i+1;
end


[H(1,Np+1) ~]=size(cell2mat(cellule_image(1,Np)));    

%%%%%commencer à mettre des cells
for i=1:Np
     imageextraite=cell2mat(cellule_image(1,i));
    %effacement des portées de l'image
[imagesansportee] = effacementportee(imageextraite,localisation(5*(i-1)+1:5*i),ydebut(i),yfinal(i),emoy);

imageextraite=imagesansportee;
figure
imshow(imagesansportee);
%localisation des empans -6 phases-
cartedesempans=carteempans(imagesansportee,W,H(1,i+1));

imagesecondephase=selectionempans(imagesansportee,W,H(1,i+1));

[imagesansporteeMAJ,cartedesempansMAJ]=fusionverticale(imagesansportee,W,H(1,i+1),cartedesempans);
[cartefinalempans]=cartefinaledesempans(imagesecondephase,W,H(1,i+1),interligne_moy,cartedesempansMAJ);
[carteterminale]=selectionuniqueempan(interligne_moy,W,H(1,i+1),cartefinalempans);
% 6ème phase pas vraiment indispensable ??? faut voir peut être pour
% consolider l'algo plus tard 




figure
imshow(1-carteterminale)
%Boites englobantes
 cellEmpans = {carteterminale};
  indiceImage = i;
 cellImages = (1 - cell2mat(cellule_image(1, indiceImage)));

 interligne = interligne_moy;
 cellNotes = emboitage(cellImages, indiceImage, cellEmpans, interligne);
for j=1:length(cellNotes(1,:))
figure 
x = (cell2mat(cellNotes(1,j)));
imshow(imagesansportee(x(1):x(2), x(3):x(4)));
end
end

