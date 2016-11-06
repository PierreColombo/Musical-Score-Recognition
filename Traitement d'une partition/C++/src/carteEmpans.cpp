#include <carteEmpans.h>

Eigen::MatrixXi carteEmpans(Eigen::MatrixXi imagesansportee){

    int n = imagesansportee.rows();
    int m = imagesansportee.cols();
    int x;
    int l;
    Eigen::MatrixXi cartedesempans = Eigen::MatrixXi::Zero(n, m);

    for (int y=0; y < m; y++){
        x=0;
        while (x < n-1){
            l=0;
            if (imagesansportee(x,y) != 1){
                x=x+1;
                cartedesempans(x,y)=0;
            }else{
                while (x < n-1 && imagesansportee(x,y) == 1){
                    l = l + 1;
                    cartedesempans(x,y) = l;
                    x = x + 1;
                }
            }

        }
    }
    std::cout << "carte des empans finie !" << std::endl;
    return cartedesempans;
}
