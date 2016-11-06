



function n = eraseEmpans(x, y, empans)
    empans(x,y) = 0;
    visite = zeros(3,3);
    for i = -1:1
        for j = -1:1
            if ((abs(y+j - yp)) <= 1.5*interligne && (empans(x+i, y+j) == 1))
                empans(x+j, y+j) = 0;
                visite(2+i,2+j) = 1;
            end
        end
    end
    for i = -1:1
        for j = -1:1
            if (visite(2+i,2+j) == 1)
                eraseEmpans(x+i, y+j, empans, empans, interligne, yp);                
            end
        end
    end