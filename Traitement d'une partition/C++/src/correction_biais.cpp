#include <correction_biais.h>

// Il faudra créer une classe image qui gêrera les images avec la capacité de read et détruire les images.

/*
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
 /*       std::cout << "Avancement : " << 100*hx/hd << "%" << std::endl;
    }
    data->indMaxC = indMaxC;
    data->maxC = maxC;
    pthread_exit(NULL);
}
*/


/*

\lstset{language=C}
\begin{center}
\lstset{breaklines=true}
\begin{lstlisting}[frame=single]



\end{lstlisting}
\end{center}

*/
void* calculThread(void* fun){
    threadData* thr = (threadData*) fun;
    int nthreads = thr->h;
    int n = thr->xm;
    Eigen::MatrixXi image = thr->image;
    int H = image.rows();
    int W = image.cols();
    int indHmax = 0;
    int valHmax = 0;
    int a = 0;
    int b = 0;
    for(int h = n ; h < H ; h = h+nthreads){
        a = 0;
        b = 0;
        for(int x = 0 ; (x+h) < H ; x++){
            for(int y = 0 ; y <= W/2-1 ; y++){
                a = a + image(x,y)*image(x+h, y+W/2);
            }
        }for(int x = h ; x < H ; x++){
            for(int y = 0 ; y <= W/2-1 ; y++){
                b = b + image(x,y)*image(x-h, y+W/2);
            }
        }
        if(a > valHmax){
            valHmax = a;
            indHmax = h;
        }if(b > valHmax){
            valHmax = b;
            indHmax = -h;
        }
    }
    thr->h = indHmax;
    thr->xm = valHmax;
    pthread_exit(NULL);
}

Eigen::MatrixXi correction_biais(Eigen::MatrixXi img){
    int W = img.cols();
    int H = img.rows();
    Eigen::MatrixXi overpass(H,W);
    for(int i = 0 ; i < H ; i++){
        for(int j = 0 ; j < W ; j++){
            overpass(i,j) = img(i,j);
        }
    }
    return overpass;

 /*   int w1 = floor(W/2);
    int w2 = W - w1;
    int wu = std::max(w1,w2);
    int longueur = H * wu;
    int indMaxC = 0;
    double maxC = 0;
//    double wd = W;
    double hd = H;
    int xp, xm, a, b;*/
/*

    int nthreads = std::thread::hardware_concurrency();
    std::cout << nthreads << std::endl;
    if (nthreads == 0){
        nthreads = 1;
    }

//    for(int i = 0 ; i < H ; i++){
//        for(int j = 0 ; j < w1 && j < w2 ; j++){
//                a = img(i,j);
  //              b = img(i,j+floor(W/2));
    //            maxC += a*b;
      //  }
    //}

    pthread_t threads[nthreads];
    threadData datas[nthreads];
    for(int i = 0 ; i < nthreads ; i++){
        threadData newdata;
        newdata.image = img;
        newdata.h = nthreads;
        newdata.xm = i;
        datas[i] = newdata;
        threadData* point = &datas[i];
        pthread_create(&threads[i], NULL, calculThread, (void*) point);
    }
    for(int i = 0 ; i < nthreads ; i++){
        pthread_join(threads[i], NULL);
        threadData res = datas[i];
        xm = res.h;
        a = res.xm;
        if (a > maxC){
            maxC = a;
            indMaxC = xm;
        }
    }
    /*
    for (int h = 1 ; h < H ; h++){
        xp = 0;
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
        }if (xp > maxC){
            indMaxC = h;
            maxC = xp;
        }if(xm > maxC){
            indMaxC = -(H-h);
            maxC = xm;
        }
       /* data->xm = xm;
        data->xp = xp;*/
       /* threadData data;
        data.h = h;
        data.image = img;
        data.maxC = 0;
        data.indMaxC = 0;
        data.nthreads = nthreads;
        datas[h] = data;
        pthread_create(&threads[h], NULL, calculAutocorr, (void*) (&datas[h]));//*/
//        std::cout << "Avancement : " << 100*h/hd << "%" << std::endl;
    //}
    /*
    int nuIndMaxC, nuMaxC;
    for(int h = 0 ; h < nthreads ; h++){
        pthread_join(threads[h], NULL);
        nuIndMaxC = datas[h].indMaxC;
        nuMaxC = datas[h].maxC;
        if(nuMaxC > maxC){
            maxC = nuMaxC;
            indMaxC = nuIndMaxC;
        }*/

    //std::cout << "Avancement : " << 100*h/hd << "%" << std::endl;

    //fftw_complex *in1, *in2, *out1, *out2;
 /*   fftw_complex *out1, *out2;
  //  double *in1;
    fftw_plan p1, p2;
    int longu = 2*longueur;
    double in1[H*wu];
    out1 = (fftw_complex*) fftw_malloc((2 * longueur) * sizeof(fftw_complex));
    out2 = (fftw_complex*) fftw_malloc((2 * longueur) * sizeof(fftw_complex));
    //in2 = (fftw_complex*) fftw_malloc(H*w2 * sizeof(fftw_complex));


    p1 = fftw_plan_dft_r2c_2d(H, 2*wu, in1, out1, FFTW_ESTIMATE);
    p2 = fftw_plan_dft_c2r_2d(H, 2*wu, out1, in1, FFTW_ESTIMATE);

    Eigen::MatrixXi img1 = img.block(0,0,H,w1);
    Eigen::MatrixXi img2 = img.block(0,w1,H,w2);

    // on remplit le tableau avec les valeurs de l'image 1.

    for(int i = 0 ; i < H ; i++){
        for(int j = 0 ; j < 2*wu ; j++){
            if(j < w1){
                in1[i*(2*wu)+j] = (double) img1(i,j);
            }else{
                in1[i*(2*wu)+j] = 0;
            }
        }
    }
    // On fait la transformée de Fourier.
    fftw_execute(p1);

    // ON prépare la deuxième TRans Fourier en recopiant d'abord le résultat 1.
    std::copy(out1, out1 + longueur, out2);

    for(int i = 0 ; i < H ; i++){
        for(int j = 0 ; j < 2*wu ; j++){
            if(j < w2){
                in1[i*2*wu+j] = (double) img2(i,j);
            }else{
                in1[i*2*wu+j] = 0;
            }
        }
    }
    fftw_execute(p1);

    for(int i = 0 ; i < 2*longueur ; i++){
        out1[i][0] = (out1[i][0] * out2[i][0] + out1[i][1] * out2[i][1]);
        out1[i][1] = (out1[i][1] * out2[i][0] - out1[i][0] * out2[i][1]);
    }

    fftw_execute(p2);

  //  Eigen::MatrixXi Resu(H, wu);

    for(int i = floor(W/2) ; i < 2*longueur ; i += wu){
        if(in1[i] > maxC){
            indMaxC = i/(2*wu) - H/2;
            maxC = in1[i];
        }
      //  Resu(i/wu, i%wu) = in1[i];
    }

    std::cout << indMaxC << " et " << maxC << std::endl; ;
    int hmax = -indMaxC;*/
 /*   int x, l, n, m;
  int hmax = 167;
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
    }*/
/*

    int nthreads = std::thread::hardware_concurrency();
    std::cout << nthreads << std::endl;
    if (nthreads == 0){
        nthreads = 1;
    }

    for(int i = 0 ; i < H ; i++){
        for(int j = 0 ; j < w1 && j < w2 ; j++){
                a = imageCorrigee(i,j);
                b = imageCorrigee(i,j+floor(W/2));
                maxC += a*b;
        }
    }

    pthread_t threads[nthreads];
    threadData datas[nthreads];
    for(int i = 0 ; i < nthreads ; i++){
        threadData newdata;
        newdata.image = imageCorrigee;
        newdata.h = nthreads;
        newdata.xm = i;
        datas[i] = newdata;
        threadData* point = &datas[i];
        pthread_create(&threads[i], NULL, calculThread, (void*) point);
    }
    for(int i = 0 ; i < nthreads ; i++){
        pthread_join(threads[i], NULL);
        threadData res = datas[i];
        xm = res.h;
        a = res.xm;
        if (a > maxC){
            maxC = a;
            indMaxC = xm;
        }
    }
    /*
    for (int h = 1 ; h < H ; h++){
        xp = 0;
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
        }if (xp > maxC){
            indMaxC = h;
            maxC = xp;
        }if(xm > maxC){
            indMaxC = -(H-h);
            maxC = xm;
        }
       /* data->xm = xm;
        data->xp = xp;*/
       /* threadData data;
        data.h = h;
        data.image = img;
        data.maxC = 0;
        data.indMaxC = 0;
        data.nthreads = nthreads;
        datas[h] = data;
        pthread_create(&threads[h], NULL, calculAutocorr, (void*) (&datas[h]));//*/
//        std::cout << "Avancement : " << 100*h/hd << "%" << std::endl;
    //}
    /*
    int nuIndMaxC, nuMaxC;
    for(int h = 0 ; h < nthreads ; h++){
        pthread_join(threads[h], NULL);
        nuIndMaxC = datas[h].indMaxC;
        nuMaxC = datas[h].maxC;
        if(nuMaxC > maxC){
            maxC = nuMaxC;
            indMaxC = nuIndMaxC;
        }*/

/*
    hmax = -indMaxC;
//  int hmax = 167;
    Eigen::MatrixXi imageCorrigee2(H + abs(hmax), W);
    for(int y = 0 ; y < W ; y++){
        x = 0;
        a = x - floor(2*hmax*y/W) + std::min(0,hmax);
        while(a < H && x < H + std::min(0, hmax) + abs(hmax)){
            l = std::min(0, hmax);
            l = x - (2*hmax*y)/W + l;
            n = std::min(H-1, l);
            m = std::max(n, 0);
            imageCorrigee2(x,y) = img(m, y);
            x++;
            a++;
       }
    }
*/

    /*std::cout << "Correction du Biais terminée." << std::endl;
    return imageCorrigee;*/
}
