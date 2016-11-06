#include<fusionVerticale.h>
//troisièmephase fusion verticale des empans coupés et mise à jour de la
//carte des empans

void fusionVerticale(Eigen::MatrixXi imagesansportee,Eigen::MatrixXi& cartedesempans){
    int n = cartedesempans.rows();
    int m = cartedesempans.cols();
        std::cout << "STep 1" << std::endl;

    for(int y = 0 ; y < m-1 ; y++){
        int x = 0;
        while(x < n-3){
            if(cartedesempans(x,y) != 0){
                // cas trou de deux pixels
                if(cartedesempans(x+1,y)==0 && cartedesempans(x+2,y)==0 && cartedesempans(x+3,y)!=0){
                    //mise à jour de l'image et de la carte des empans
                    int l=cartedesempans(x,y);
                    imagesansportee(x+1,y)=1;
                    cartedesempans(x+1,y)=l;
                    l++;
                    imagesansportee(x+2,y)=1;
                    cartedesempans(x,y)=l;
                    l++;
                    x=x+2;
                    while (x < n-1 && (imagesansportee(x,y))==1){
                        l++;
                        cartedesempans(x,y)=l;
                        x++;
                    }
                }
                // cas trou d'un pixel
                else if(cartedesempans(x+1,y) == 0 &&  (cartedesempans(x+2,y)!=0))
                {
                    //mise à jour de l'image et de la carte des empans
                    int l=cartedesempans(x,y);
                    imagesansportee(x+1,y)=1;
                    cartedesempans(x+1,y)=l+1;
                    l++;
                    x++;
                    while (x < n-1 && (imagesansportee(x,y))==1)
                    {
                        l++;
                        cartedesempans(x,y)=l;
                        x++;
                    }
                }

                //rien à faire
                else
                {
                    x++;
                }
                //l'élement n'est pas noir
            }
            else
            {
                x++;
            }



        }
    }
    std::cout << "fusion verticale finie !" << std::endl;

}
