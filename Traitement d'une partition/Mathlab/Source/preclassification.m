%fonction de pr�classification des classes ont commence 

function[a]=preclassification(yg,yd,xh,xb,sl,xtroisiemeligne,xpb)
%%entr�es
%ygauche
%ydroite
%xhaut
%xbas
%yp = ydel'empans
%sl = interligne
%xtroisiemeligne = ordonn�e de la troisi�me port�e

xp5=xtroisiemeligne-2*sl;
xpl=xtroisiemeligne+2*sl;
xph=xh;
%Classe: barres de mesure
i=0;
if (abs(xpb-xpl)<0.2*sl)
   i=i+1;
end
if  abs(xph-xp5)<0.2*sl 
i=i+1;
end
if abs(yd-yg)<0.2*sl
    i=i+1;
end
if abs(xh-xp5)<0.2*sl
    i=i+1;
end
if abs(xb-xpl)<0.2*sl
    i=i+1;
end
if i>2
   a='c est bien une barre de mesure' 
end