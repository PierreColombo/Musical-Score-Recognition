#ifndef MAIN_FUNCTION
#define MAIN_FUNCTION

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <Eigen/Dense>
#include <imageProc.h>
#include <struct.h>
#include <correction_biais.h>
#include <detectionInterligne.h>
#include <rechercheDesXis.h>
#include <sousImagePortee.h>
#include <effacementPortee.h>
#include <histogrammeLargeurLigne.h>
#include <emboitage.h>
#include <fusionVerticale.h>
#include <carteEmpans.h>
#include <carteFinaleDesEmpans.h>
#include <selectionUniqueEmpan.h>
#include <sellectionPlusieursEmpans.h>
#include <emboitageImage.h>
#include <reconnaissancenotes.h>
#include <ecritureNote.h>

int mainFunction(std::string imageToRead);

#endif // MAIN_FUNCTION
