#include <sousImagePortee.h>


sousImagePorteeRes sousImagePortee(Eigen::VectorXi localisation, Eigen::MatrixXi imageProces, int interligneMoyen){
    int Np = localisation.rows()/5;
    Eigen::VectorXi xc(Np);
    Eigen::VectorXi ox(Np);
    Eigen::VectorXi Hprime(Np);
    int H = imageProces.rows();
    int W = imageProces.cols();

    xc(0) = 0;
    for(int i = 1 ; i < Np ; i++){
        xc(i) = (localisation(2 + 5*i) + localisation(2+5*(i-1)))/2;
    }
    ox(0) = 0;
    for(int i = 1 ; i < Np ; i++){
        ox(i) = xc(i) - 2*interligneMoyen;
    }
    for(int i = 0 ; i < Np-1 ; i++){
        Hprime(i) = xc(i+1) + 2 * interligneMoyen - ox(i);
    }
    Hprime(Np-1) = H - ox(Np-1);

    // xc donne maintenant la vraie abscisse des 3èmes lignes de portée.
    for(int i = 0 ; i < Np ; i++){
        xc(i) = localisation(2+5*i) - ox(i);
    }

    sousImagePorteeRes resultat;
    resultat.abscisseTroisiemeLigne = xc;
    resultat.offsetX = ox;
    resultat.Hprime = Hprime;
    std::vector<Eigen::MatrixXi> res(Np);
    for(int i = 0 ; i < Np ; i++){
        res[i] = imageProces.block(ox(i), 0, Hprime(i), W);
    }
    resultat.portees = res;
    return resultat;
}
