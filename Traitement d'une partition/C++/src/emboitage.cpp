#include <emboitage.h>

quadInt grow(int x, int y, Eigen::MatrixXi &empans, Eigen::MatrixXi &image, int interligne, int yp){
    image(x,y) = 0;
    empans(x,y) = 0;
    int xh = x;
    int xb = x;
    int yg = y;
    int yd = y;
    Eigen::MatrixXi visite(3,3);
    for(int i = -1 ; i <= 1 ; i++){
        for(int j = -1 ; j <= 1 ; j++){
            if((abs(y+j-yp) <= (3*interligne)/2) && (image(x+i, y+j) == 1){
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
}

std::vector<Eigen::MatrixXi> emboitage(Eigen::MatrixXi image, Eigen::MatrixXi empans, int interligne, int nbrEmpans){
    int x = 0;
    int y = 0;
    int xe = empans.rows();
    int ye = empans.cols();
    std::vector<Eigen::MatrixXi> notes(nbrEmpans);
    int compteur = 0;
    while(x < xe && y < ye){
        if(empans(x,y) == 1){
            quadInt note = grow(x,y,empans,image,interligne,y);
            notes(compteur) = image.block(note.a, note.c, note.b - note.a, note.d - note.c);
            compteur++;
        }if(x == xe){
            x = 0;
            y++;
        }else{
            x++;
        }
    }
    notes.resize(compteur);
    return notes;
}
