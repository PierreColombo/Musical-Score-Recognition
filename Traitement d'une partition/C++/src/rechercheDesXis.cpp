#include <rechercheDesXis.h>



Eigen::VectorXi rechercheDesXis(Eigen::VectorXi Py, int W, int interligneMoyen){
    int n = Py.rows();
    int seuil = 3;
    bool go = true;
    //  float toleranceInterligneInf = 0.5;
    std::list<int> localisationListeInf;
    for(int i = 1 ; i < n-1 ; i++){
        if(Py(i) >= Py(i-1) && Py(i) >= Py(i+1) && Py(i) > W/seuil && go){
            localisationListeInf.push_back(i);
            go = false;
        }else if(Py(i) <= W/seuil){
            go = true;
        }
    }
    int m = localisationListeInf.size();
    std::cout << "Taille : " << m << std::endl;
    Eigen::VectorXi localisationListe(m);
    for(int i = 0 ; i < m ; i++){
        localisationListe(i) = localisationListeInf.front();
        localisationListeInf.pop_front();
    }
    return localisationListe;
}

// Note : on ne tue pas ici les double maximums.
