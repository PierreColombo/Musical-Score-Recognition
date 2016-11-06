% emboitage


% cellImages est la cellule contenant les diff�rentes sous port�es.
% indiceImage est l'indice de l'image dans la cellule que l'on traitera.
% cellEmpans est la cellule des empans de chaque image.
% cellNotes est la cellule des 7 coordonn�es de chaque note.
% Attention : les notes sont effac�es de l'image une fois r�pertori�es.
% ==> Copie de l'image auparavant. (En terme de complexit� spatiale, sans 
% utiliser un algorithme horrible, c'est in�vitable)

function cellNotes = emboitagePrealloc(cellImages, indiceImage, cellEmpans, interligne)
    x = 1;
    y = 1;
    
    cellNotes = cell(n);
    image = cellImages(indiceImage);
    empans = cellEmpans(indiceImage);
    [xe,ye] = size(empans);
    while (x <= xe && y <= ye)
        if(empans(x,y) == 1)
            [xh, xb, yg, yd] = grow(x, y, empans, image, interligne, y);
            cellNotes = {cellNotes, {[xh, xb, yg, yd]}};
        end
        if (x == xe)
            x = 1;
            y = y+1;
        else
            x = x+1;
        end
    end    
