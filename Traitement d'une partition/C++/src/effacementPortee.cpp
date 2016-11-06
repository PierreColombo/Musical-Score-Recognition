#include <effacementPortee.h>

void effacementPortee(Eigen::MatrixXi & imageCorrigee, Eigen::VectorXi Py, int interligneMoyen, Eigen::VectorXi localisation,
Eigen::VectorXi offsetX, Eigen::VectorXi Hprime, int ydebut, int yfin, int emoy){
    int N = localisation.rows();
    int se = emoy + 3;
    for(int y = ydebut ; y < yfin ; y++){
        for(int i = 0 ; i < N ; i++){
            int xh = localisation(i);
            int xb = localisation(i);
            int x = localisation(i);
            while(imageCorrigee(xb, y) == 1){
                xb++;
            }while(imageCorrigee(xh, y) == 1){
                xh--;
            }if((se>= (xb-xh+1)) && (xb < (x+se)) && (xh>(x-se))){
                for(int i = xh-2 ; i <= xb ; i++)
                imageCorrigee(i, y) = 0;
            }
        }
    }/*
    int xm = imageCorrigee.rows();
    int ym = imageCorrigee.cols();
    for(int x = 0 ; x < xm ; x++){
        for(int y = 0 ; y < ym ; y++){
            imageCorrigee(x,y) = 0;
        }
    }*/
}
