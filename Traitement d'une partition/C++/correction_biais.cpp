#include <correction_biais.h>

// Il faudra créer une classe image qui gêrera les images avec la capacité de read et détruire les images.



Eigen::MatrixXi correction_biais(MatrixXi img){
    int W = img.W;
    int H = img.H;

/*// Non-optimal.

    int** image1 = int*[H];
    int** image2 = int*[H];

    for(int i = 0 ; i < H ; i++){
        image1[i] = int[floor(W/2)];
        image2[i] = int[W-floor(W/2)];
        for(int j = 0 ; j < floor(W/2) ; j++){
            image1[i][j] = img.data[i][j];
        }for(int j = 0 ; j < W - floor(W/2) ; j++){
            image2[i][j] = img.data[i][j + floor(W/2)];
        }
    }
*/
/*
[M,N] = size(X);
m = 1:M;
n = 1:N;

[P,Q] = size(H);
p = 1:P;
q = 1:Q;
*/
/*
Xt = zeros([M+2*(P-1) N+2*(Q-1)]);
Xt(m+P-1,n+Q-1) = X;
C = zeros([M+P-1 N+Q-1]);
*/

int w1 = floor(W/2);
int w2 = W - w1;

Eigen::MatrixXi cor(H, W);


for (int k = 0 ; k < H ; k++){
    for (int l = 0 ; l < W ; l++){
        int x = 0;
        for(int i = k ; i < H ; i++){
            for(int j = l ; j < w1 && (j-l) < w2 ; j++){
                x = x + img(i,j)*img(i-k,j-l);
            }
        }
        cor(k,l) = x;
    }
}

Eigen::VectorXi C(H);
int indMaxC = 0;
int maxC = 0;

for(int i = 0 ; i < H ; i++){
    C(i) = 2/(W*H) * cor(i, floor(W/2));
    if (C(i) > maxC){
        indMaxC = i;
        maxC = C(i);
    }
}

int hmax = indMaxC - floor(W/2);
float theta = atan(hmax/(W/2));

Eigen::MatrixXi imageCorrigee(H + abs(hmax), W);
for(int y = 0 ; y < W ; y++){
    int x = 1;
    int a = x - floor(2*hmax*y/W) + std::min(0,hmax);

    while(a < H & x < H + std::min(0, hmax) + abs(hmax)){
        int l = std::min(0, hmax);
        l = x - floor(2*hmax*y/W) + l;
        int n = std::min(H, l);
        int m = std::max(n, 1);
        imageCorrigee(x,y) = img(m, y);
        x++;
        a++;
   }
}
    return imageCorrigee;
}







