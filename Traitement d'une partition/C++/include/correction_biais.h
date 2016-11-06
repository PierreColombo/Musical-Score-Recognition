#ifndef CORRECTION_BIAIS
#define CORRECTION_BIAIS
#include <iostream>
#include <images.h>
#include <math.h>
#include <Eigen/Dense>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <pthread.h>
#include <struct.h>
#include <thread>
#include <complex.h>
//#include <fftw3.h>

//void *calculAutocorr(void*);

Eigen::MatrixXi correction_biais(Eigen::MatrixXi);

#endif
