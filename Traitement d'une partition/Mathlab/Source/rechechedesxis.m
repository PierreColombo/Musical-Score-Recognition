%recherche des xi

function localisation = rechechedesxis(Py, W, interligne_moy)

seuil=3;
%toleranceinterlignesup=1.5;
toleranceinterligneinf=0.5;

%on cr�e le vecteur et on l'�pure un peu
[a, localisation]=findpeaks(-Py,'MinPeakHeight',W/seuil);

%tentative pour avoir la quatri�me port�e
  for j=1:length(localisation)-1
  %faut tuer les doubles maximum si epaisseur>1 necessaire ? ou les
  %parasites ? faudrait peut �tre rendre la m�thode plus robuste. .... 
      if abs(localisation(j)-localisation(j+1))<interligne_moy*toleranceinterligneinf
          localisation(j)=[];
     else
          
      end
  end
