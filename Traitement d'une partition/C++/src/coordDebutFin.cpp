#include <coordDebutFin.h>


/*
coupleInt coordDebFin(int si, Eigen::MatrixXi image, int emoy, int xportee){
    // Soyons intelligents.
    // Que nous faut-il ?
    // Un tableau à sI places qui tourne. On n'a pas besoin de plus de mémoire.
    int proj_y[si];
    bool valeurs[si];
    int compteFaux;

    int a; int resi;
    int Dx = (emoy/2) + 1;
    bool continuer = false;

    // On remplit le tableau pour la première itération.
    for(int i = 0 ; i < si ; i++){
        resi = 0;
        for(int dxp = -si/2 ; dxp <= si/2 ; dxp++){
            a = 0;
            for(int k = -2 ; k <= 2 ; k++){
                for(int dx = -Dx ; dx <= Dx ; dx++){
                    a+=image(xportee + k*si + dx + dxp, y);
                }
            }
            if (a > resi){
                resi = a;
            }
        }
        proj_y[i] = resi;
        if (resi >= 2.5*emoy){
            valeurs[i] = true;
        }else{
            valeurs[i] = false;
            compteFaux++;
        }
    }
    // On arrête la boucle une fois que le compte est nul. Pour chaque nouvel ajout dans le tableau (on utilisera les modulos si pour ne pas sortir)
    // on retire l'élément suivant, et s'il était false, décrémente le compte, puis insère le nouvel élément, et éventuellement ré-incrémente le compte.
    // Le calcul est dans la thèse de Roussant, et dans l'itinialisation aussi. TU peux faire un copier-coller.
    while(continuer){

    }
}
*/
