#include <emboitageImage.h>

/*quadInt grow(int x, int y, Eigen::Ref<Eigen::MatrixXi> empans, Eigen::Ref<Eigen::MatrixXi> image, int interligne, int yp){
    image(x,y) = 0;
    empans(x,y) = 0;
    int xh = x;
    int xb = x;
    int yg = y;
    int yd = y;
    Eigen::MatrixXi visite(3,3);
    for(int i = -1 ; i <= 1 ; i++){
        for(int j = -1 ; j <= 1 ; j++){
            if((abs(y+j-yp) <= (3*interligne)/2) && (image(x+i, y+j) == 1)){
                image(x+i, y+j) = 0;
                empans(x+i, y+j) = 0;
                visite(1+i, 1+j) = 1;
            }
        }
    }for(int i = -1 ; i <= 1 ; i++){
        for(int j = -1 ; j <= 1 ; j++){
            if(visite(1+i, 1+j) == 1){
                quadInt resn = grow(x+i, y+j, empans, image, interligne, yp);
                if (resn.a < xh){
                    xh = resn.a;
                }if(resn.b > xb){
                    xb = resn.b;
                }if(resn.c < yg){
                    yg = resn.c;
                }if(resn.d > yd){
                    yd = resn.d;
                }
            }
        }
    }
    quadInt result;
    result.a = xh;
    result.b = xb;
    result.c = yg;
    result.d = yd;
    return result;
}*/

std::vector<quadInt> emboitageImage(Eigen::MatrixXi image, Eigen::MatrixXi empans, int interligne, int nbrEmpans){
    int x = 0;
    int y = 0;
    int xe = empans.rows();
    int ye = empans.cols();
    int yp;
    int xh;
    int xb;
    int yg;
    int yd;
    int xi, yi;
    int ygp = -10;
    int ydp = -10;
    int compteur = 0;
    coupleInt var;
    std::list<quadInt> notes;
    std::stack<coupleInt> pile;
    while(x < xe && y < ye){
        if(empans(x,y) != 0){
        //std::cout << x << " " << y << std::endl;
            xh = x;
            xb = x;
            yg = y;
            yd = y;
            yp = y;
            var.a = x;
            var.b = y;
            pile.push(var);
            while(!(pile.empty())){
                var = pile.top();
                pile.pop();
                xi = var.a;
                yi = var.b;
                if (xi < xh){
                    xh = xi;
                }if(xi > xb){
                    xb = xi;
                }if(yi < yg){
                    yg = yi;
                }if(yi > yd){
                    yd = yi;
                }
                image(xi,yi) = 0;
                empans(xi,yi) = 0;
                for(int i = -1 ; i <= 1 ; i++){
                    for(int j = -1 ; j <= 1 ; j++){
                        if((abs(yi+j-yp) <= (3*interligne)/2) && (image(xi+i, yi+j) == 1)){
                            image(xi+i, yi+j) = 0;
                            empans(xi+i, yi+j) = 0;
                            var.a = xi+i;
                            var.b = yi+j;
                            pile.push(var);
                        }
                    }
                }
            }
            if (xh != xb && yg != yd){
                if ((abs(yg - ygp) > interligne / 3) || (abs(yd - ydp) > interligne/3)){
                    quadInt img;
                    img.a = xh;
                    img.b = xb;
                    img.c = yg;
                    img.d = yd;
                    ygp = yg;
                    ydp = yp;
                    //std::cout << xh << " " << xb << " " << yg << " " << yd << " " << std::endl;
                    notes.push_back(img);
                    compteur++;
                }

            }
        }if(x == xe-1){
            x = 0;
            y++;
        }else{
            x++;
        }
    }
    std::vector<quadInt> resultat(compteur);
    for(int i = 0 ; i < compteur ; i++){
        resultat[i] = notes.front();
        notes.pop_front();
    }
    return resultat;
}
