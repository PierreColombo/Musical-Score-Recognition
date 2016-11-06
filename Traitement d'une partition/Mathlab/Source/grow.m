
% Fonction récursive de croissance par région.

function [xh, xb, yg, yd] = grow(x, y, empans, image, interligne, yp)
    image.Value(x,y) = 0;
    empans.Value(x,y) = 0;
    xh = x;
    xb = x;
    yg = y;
    yd = y;
    %x,y
    visite = zeros(3,3);
    for i = -1:1
        for j = -1:1
            if (((abs(y+j - yp)) <= 1.5*interligne) && (image.Value(x+i, y+j) == 1))
                image.Value(x+i, y+j) = 0;
                empans.Value(x+i, y+j) = 0;
                visite(2+i,2+j) = 1;
            end
        end
    end
    for i = -1:1
        for j = -1:1
            if (visite(2+i,2+j) == 1)
                [xhn, xbn, ygn, ydn] = grow(x+i, y+j, empans, image, interligne, yp);
                if xhn < xh;
                    xh = xhn;
                end
                if xbn > xb
                    xb = xbn;
                end
                if ygn < yg
                    yg = ygn;
                end
                if ydn > yd
                    yd = ydn;
                end
            end
        end
    end

