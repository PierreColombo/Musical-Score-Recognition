#ifndef RECO_NOTES
#define RECO_NOTES
#include <images.h>
#include <Eigen/Dense>
#include <math.h>
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/gpu/gpu.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <struct.h>

note reconnaissancenotes(Eigen::MatrixXi img , int troisiemeLigne, int interligne,int xb,int yb,int xh,int yd, int epaisseur);

note reconnaissanceCroche(Eigen::MatrixXi img, int interligne, note interm, int matchlocx, int matchlocy);

#endif // RECO_NOTES
