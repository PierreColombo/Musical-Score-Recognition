#include <algorithm>
#include<selectionUniqueEmpan.h>
//selection d'un unique empan verticale grâce à une fenêtre
Eigen::MatrixXi selectionUniqueEmpan(int interligne_moy,Eigen::MatrixXi cartefinalempans,int &nombre_empans)
{
    int n = cartefinalempans.rows();
    int m = cartefinalempans.cols();
    int largeurfenetre = floor((2 * interligne_moy)/5); // penser à l'arrondi
    for (int y = 0 ; y < m; y++){
        int x = n-1;
        while (x > 0){
            if (cartefinalempans(x,y)==0){
                x=x-1;
            }else{
                int longueur_empan_courant=cartefinalempans(x,y);
                nombre_empans= nombre_empans+1;
                //recherche du maximum du tableau de longueur largeur fenetre et
                //de hauteur longueur_empan_courant
                int indiceRow;
                int indiceCol;
                int valeurmaximale = cartefinalempans.block(x-longueur_empan_courant,y,longueur_empan_courant,std::min((largeurfenetre),m-y)).maxCoeff(&indiceRow,&indiceCol);

                //on selectionne le premier empan maximal qu'on trouve
                if (valeurmaximale==longueur_empan_courant){
                    cartefinalempans.block(x-(longueur_empan_courant),y+1,longueur_empan_courant+1,largeurfenetre-1).setZero();
                    x=x-longueur_empan_courant;

                }else{

                  cartefinalempans.block(x-longueur_empan_courant,y,longueur_empan_courant,0).setZero();
                    x=x-longueur_empan_courant;
                }
            }
        }
    }
    std::cout << "selection unique empan finis" << std::endl;
    return cartefinalempans;
}
