enum {enNoDerivative = 0, enFirstPartialDerivativeX, enFirstPartialDerivativeY, enSecondPartialDerivativeX, enSecondPartialDerivativeY};

bool gpuGaussian(CImage& image, CImage& result, float fpSigma, BYTE bFilterSide, BYTE bDerivative);
