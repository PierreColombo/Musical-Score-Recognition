#include <detectionInterligne.h>




void* calculPy(void* data){
    threadData2* point = (threadData2*) data;
    int h = point->h;
    int nthreads = point->xm;
    int n = point->xp;
    Eigen::VectorXi Py = point->vecteur;
    int maxPy = 0;
    int indMaxPy = 0;
    for(int i = (1+h) ; i < n ; i+= nthreads){
        int x = 0;
        for(int j = 0 ; (i+j) < n && j < n; j++){
            x += Py(j)*Py(i+j);
        }
        if(x > maxPy){
            maxPy = x;
            indMaxPy = i;
        }
    }
    point->h = indMaxPy;
    point->xm = maxPy;
    pthread_exit(NULL);
}



// Py est modifié par la fonction, mais on ne peut pas renvoyer plusieurs résultats en même temps :'(

intVectXi detectionInterligne(Eigen::MatrixXi data){
    int n = data.rows();
    int m = data.cols();
    int a;
    Eigen::VectorXi Py(n);
    for(int x = 0 ; x < n ; x++){
        a = 0;
        for(int y = 0 ; y < m ; y++){
            a += data(x,y);
        }
        Py(x) = a;
    }
    int maxPy = 0;
    int indMaxPy = 0;

    // Non-threadé :
    /*
    for(int i = 1 ; i < n ; i++){
        int x = 0;
        for(int j = 0 ; (i+j) < n && j < n; j++){
            x += Py(j)*Py(i+j);
        }
        if(x > maxPy){
            maxPy = x;
            indMaxPy = i;
        }
    }
*/

    // Threadé :

    int nthreads = std::thread::hardware_concurrency();
    if (nthreads == 0){
        nthreads = 1;
    }

    pthread_t threads[nthreads];
    threadData2 datas[nthreads];
    int numax = 0; int nuindmax = 0;

    for(int i = 0 ; i < nthreads ; i++){
        datas[i].h = i;
        datas[i].xm = nthreads;
        datas[i].xp = n;
        datas[i].vecteur = Py;
        threadData2* point = &datas[i];
        pthread_create(&threads[i], NULL, calculPy, (void*) point);
    }for(int i = 0 ; i < nthreads ; i++){
        pthread_join(threads[i], NULL);
        nuindmax = datas[i].h;
        numax = datas[i].xm;
        if (numax > maxPy){
            maxPy = numax;
            indMaxPy = nuindmax;
        }
    }

    std::cout << indMaxPy << std::endl;

    int interligneMoyen = indMaxPy;
    intVectXi res;
    res.i = interligneMoyen;
    res.vec = Py;
    return res;
}
