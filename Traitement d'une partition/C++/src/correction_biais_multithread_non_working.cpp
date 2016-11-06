#include <correction_biais.h>

// Il faudra créer une classe image qui gêrera les images avec la capacité de read et détruire les images.


void *calculAutocorr(void *threadarg){
    int xp = 0;
    int xm = 0;

    threadData *data = (threadData *) threadarg;
    int h = data->h;
    Eigen::MatrixXi img = data->image;
    int indMaxC = data->indMaxC;
    int maxC = data->maxC;
    int nthreads = data->nthreads;

    int H = img.rows();
    int W = img.cols();
    double hd = H;

    int w1 = floor(W/2);
    int w2 = W - w1;
    int a,b;
    for(int hx = h ; hx < H ; hx = hx + nthreads){
        for(int i = 0 ; i < H && i+hx < H; i++){
            for(int j = 0 ; j < w1 && j < w2 ; j++){
                a = img(i,j);
                b = img(i+hx,j+floor(W/2));
                xp += a*b;
            }
        }
        for(int i = (H-hx) ; i < H && (i-(H-hx) < H) ; i++){
            for(int j = 0 ;  j < w1 && j < w2 ; j++){
                a = img(i,j);
                b = img(i-(H-hx),j+floor(W/2));
                xm += a*b;
            }
        }if (xp > maxC){
            indMaxC = hx;
            maxC = xp;
        }if(xm > maxC){
            indMaxC = -(H-hx);
            maxC = xm;
        }
       /* data->xm = xm;
        data->xp = xp;*/
        std::cout << "Avancement : " << 100*hx/hd << "%" << std::endl;
    }
    data->indMaxC = indMaxC;
    data->maxC = maxC;
    pthread_exit(NULL);
}


Eigen::MatrixXi correction_biais(Eigen::MatrixXi img){
    int W = img.cols();
    int H = img.rows();

    int w1 = floor(W/2);
    int w2 = W - w1;
    int indMaxC = 0;
    double maxC = 0;
//    double wd = W;
    double hd = H;
    int xp, xm, a, b;

    int nthreads = std::thread::hardware_concurrency();
    std::cout << nthreads << std::endl;
    if (nthreads == 0){
        nthreads = 1;
    }


/*    for(int i = 0 ; i < H ; i++){
        for(int j = 0 ; j < w1 && j < w2 ; j++){
                a = img(i,j);
                b = img(i,j+floor(W/2));
                maxC += a*b;
        }
    }*/
    pthread_t threads[nthreads];
    threadData datas[nthreads];
    for (int h = 0 ; h < nthreads ; h++){
        /*xp = 0;
        xm = 0;
        for(int i = 0 ; i < H && i+h < H; i++){
            for(int j = 0 ; j < w1 && j < w2 ; j++){
                a = img(i,j);
                b = img(i+h,j+floor(W/2));
                xp += a*b;
            }
        }
        for(int i = (H-h) ; i < H && (i-(H-h) < H) ; i++){
            for(int j = 0 ;  j < w1 && j < w2 ; j++){
                a = img(i,j);
                b = img(i-(H-h),j+floor(W/2));
                xm += a*b;
            }
        }//*/
        threadData data;
        data.h = h;
        data.image = img;
        data.maxC = 0;
        data.indMaxC = 0;
        data.nthreads = nthreads;
        datas[h] = data;
        pthread_create(&threads[h], NULL, calculAutocorr, (void*) (&datas[h]));//*/
    }
    int nuIndMaxC, nuMaxC;
    for(int h = 0 ; h < nthreads ; h++){
        pthread_join(threads[h], NULL);
        nuIndMaxC = datas[h].indMaxC;
        nuMaxC = datas[h].maxC;
        if(nuMaxC > maxC){
            maxC = nuMaxC;
            indMaxC = nuIndMaxC;
        }

    //std::cout << "Avancement : " << 100*h/hd << "%" << std::endl;
    }





    std::cout << indMaxC << " et " << maxC << std::endl; ;
    int hmax = -indMaxC;
    int x, l, n, m;
//  int hmax = 167;
    Eigen::MatrixXi imageCorrigee(H + abs(hmax), W);
    for(int y = 0 ; y < W ; y++){
        x = 0;
        a = x - floor(2*hmax*y/W) + std::min(0,hmax);
        while(a < H && x < H + std::min(0, hmax) + abs(hmax)){
            l = std::min(0, hmax);
            l = x - (2*hmax*y)/W + l;
            n = std::min(H-1, l);
            m = std::max(n, 0);
            imageCorrigee(x,y) = img(m, y);
            x++;
            a++;
       }
    }

    std::cout << "correction_biais fini" << std::endl;
    return imageCorrigee;
}
