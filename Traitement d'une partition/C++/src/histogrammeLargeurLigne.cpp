#include <histogrammeLargeurLigne.h>



int histogrammeLargeurLigne(Eigen::MatrixXi image){
    int H = image.rows();
    int W = image.cols();
    int x = 0;
    int a, A, B;
    int valMax = 0;
    int indMax = 0;
    Eigen::VectorXi Histo = Eigen::VectorXi::Zero(H);
    for(int y = floor(W/11) ; y < floor(10*W / 11) ; y += floor(W/11)){
        while(x < H){
            a = 0;
            while((x < H) && (image(x,y) == 1)){
                a++;
                x++;
            }
            Histo(a)++;
            x++;
        }
    }
    Histo(0) = 0;
    A = 0;
    B = 0;
    for(int i = 1 ; i < H ; i++){
        if(Histo(i) > valMax){
            indMax = i;
            valMax = Histo(i);
        }
    }
    for(int i = indMax-1 ; i <= indMax+1 ; i++){
        A = A + i*Histo(i);
        B = B + Histo(i);
    }
    return(A/B);
}
