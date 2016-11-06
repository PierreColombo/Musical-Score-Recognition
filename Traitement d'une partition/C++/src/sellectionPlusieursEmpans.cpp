// seconde phase : extraction des empans
#include <sellectionPlusieursEmpans.h>
Eigen::MatrixXf sellectionPlusieursEmpans(Eigen::MatrixXi varimagesansportee){
    int n = varimagesansportee.rows();
    int m = varimagesansportee.cols();
    Eigen::MatrixXf imagesansportee = varimagesansportee.cast<float>();
    Eigen::MatrixXf imagesecondephase(n, m);
    Eigen::MatrixXf filtre(1,9);
    filtre(0,0)=0.25;
    filtre(0,1)=0.25;
    filtre(0,2)=0;
    filtre(0,3)=0;
    filtre(0,4)=0;
    filtre(0,5)=0;
    filtre(0,6)=0;
    filtre(0,7)=0.25;
    filtre(0,8)=0.25;

     std::cout << filtre << std::endl;

    for(int x = 4; x < n-4 ; x++)    {
        for(int y = 0; y < m ; y++){
            for(int j = -4 ; j <= 4 ; j++){
                float a = imagesansportee(x,y);
                float b = -imagesansportee(x+j,y);
                imagesecondephase(x,y) = imagesecondephase(x,y)+(a*b*filtre(0,j+4));
            }
         //   std::cout << imagesecondephase(x,y);
        }
        //std::cout << std::endl;
    }
    std::cout << "image seconde phase finie !" << std::endl;
    return imagesecondephase;
}

