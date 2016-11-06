#ifndef IMAGES_H
#define IMAGES_H


#ifndef IMAGE_H
#define IMAGE_H
#include <Eigen/Dense>

class images
{
    public:
        Eigen::MatrixXi data;
        int W;
        int H;
        images(Eigen::MatrixXi, int, int);
        virtual ~images();
    protected:
    private:
};

#endif // IMAGE_H

#endif // IMAGES_H
