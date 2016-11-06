#ifndef IMAGE_PROC
#define IMAGE_PROC
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <struct.h>
#include <math.h>

Eigen::MatrixXi niveauGris(cv::Mat, byte);

void imashow(Eigen::MatrixXi imageGrise, int num);

void imashowcarte(Eigen::MatrixXi imageGrise, int num);

void imashownotes(note laNote);

void imashownotesancien(quadInt loca, Eigen::MatrixXi imag, int i);

#endif
