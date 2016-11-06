#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED
#include "Eigen/Dense"
#include <vector>
#include <iostream>

struct intVectXi{
    int i;
    Eigen::VectorXi vec;
};

typedef unsigned char byte;
typedef unsigned char BYTE;


struct sousImagePorteeRes{
    Eigen::VectorXi abscisseTroisiemeLigne;
    Eigen::VectorXi offsetX;
    Eigen::VectorXi Hprime;
    std::vector<Eigen::MatrixXi> portees;
};

struct threadData{
    int h;
    Eigen::MatrixXi image;
    int xm;
    int xp;
};

struct threadData2{
    int h;
    Eigen::VectorXi vecteur;
    int xm;
    int xp;
};

struct coupleInt{
    int a;
    int b;
};

struct quadInt{
    int a;
    int b;
    int c;
    int d;
};

struct note{
    int x;
    int y;
    int sound;
    std::string symbole;
    Eigen::MatrixXi imageNote;
};

#endif // STRUCT_H_INCLUDED
