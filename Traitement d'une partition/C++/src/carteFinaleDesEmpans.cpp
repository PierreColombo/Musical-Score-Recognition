#include<carteFinaleDesEmpans.h>
#include<cmath>

//quatrième phase: recherche de l'empan de longueur maximal elle doit se

// la nouvelle carte contient en case (i,j) la valeur de l'empan qui
// s'étends vers le haut
//sl =interligne_moy

Eigen::MatrixXi carteFinaleDesEmpans(Eigen::MatrixXf imagesecondephase, int sl, Eigen::MatrixXi cartedesempansMAJ)
{
    int n = cartedesempansMAJ.rows();
    int m = cartedesempansMAJ.cols();


    Eigen::MatrixXi cartefinalempans= Eigen::MatrixXi::Zero(n,m);

    for (int y=0; y<m-1; y++)

    {
        int indiceRow;
        int indiceCol;
        int lempanmax = floor(cartedesempansMAJ.col(y).maxCoeff(&indiceRow,&indiceCol));

       if ((lempanmax>1.5*sl) and (((imagesecondephase.block((indiceRow-lempanmax),y,lempanmax,1)).cwiseAbs().sum())>lempanmax/4)) // attention truc bizarre
        {
            for (int j=0; j<lempanmax; j++)
            {

            cartefinalempans(indiceRow-j,y)=lempanmax-j+1;;
            }
        }

    }
    std::cout << "carteFinaleDesEmpans finie !" << std::endl;

    return cartefinalempans;

}
