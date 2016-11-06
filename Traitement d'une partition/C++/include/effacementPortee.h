#ifndef EFFACEMENT_PORTEES
#define EFFACEMENT_PORTEES
#include <stdio.h>
#include <struct.h>
#include <Eigen/Dense>

void effacementPortee(Eigen::MatrixXi & imageCorrigee, Eigen::VectorXi Py, int interligneMoyen, Eigen::VectorXi localisation, Eigen::VectorXi offsetX, Eigen::VectorXi Hprime, int ydebut, int yfin, int emoy);


#endif
