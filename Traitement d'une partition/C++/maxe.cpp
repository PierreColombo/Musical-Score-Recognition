#include <iostream>

using namespace::std;


int maxe(int* t, int length){
    int res = t[0];
    for(int i = 0 ; i < length ; i++){
        if (t[i] > res){
            res = t[i];
        }
    }
    return res;
}


