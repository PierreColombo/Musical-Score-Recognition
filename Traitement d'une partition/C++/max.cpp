#include <iostream>

using namespace::std;

int maxe(int[]);
int maxe(int*, int);


int maxe(int[] t){
    int n = t.size();
    int res = t[0];
    for(int i = 0 ; i < n ; i++){
        if (t[i] > res){
            res = t[i];
        }
    }
    return res;
}

int maxe(int* t, int length){
    int res = t[0];
    for(int i = 0 ; i < length ; i++){
        if (t[i] > res){
            res = t[i];
        }
    }
    return res;
}

}

