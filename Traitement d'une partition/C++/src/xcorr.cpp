#include <iostream>
#include "Eigen/Dense"

using namespace std;


Eigen::VectorXi xcorr(Eigen::VectorXi corr){
    int n = corr.rows();
    Eigen::VectorXi res(n);
    for(int i = 0 ; i < n ; i++){
        int x = 0;
        for(int j = 0 ; (i+j) < n && j < n; j++){
            x = x + corr(j)*corr(i+j);
        }
        res(i) = x;
    }
    return res;
}
