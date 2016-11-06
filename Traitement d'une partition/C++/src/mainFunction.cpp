#include <mainFunction.h>

// version n°(1.0m1.0c)

using namespace std; using namespace cv;

int mainFunction(string imageToRead){
    string adresse = "test/" + imageToRead;
    cv::Mat imageRead = cv::imread(adresse, CV_LOAD_IMAGE_GRAYSCALE);

    Eigen::MatrixXi imageUtilisee = niveauGris(imageRead, 255*50);
    imageRead.release();
    int xh, xb, yg, yd;
    int troisiemeLigne;
    //Eigen::MatrixXi imageCorrigee = imageUtilisee;


    Eigen::MatrixXi imageCorrigee = correction_biais(imageUtilisee); // ON doit changer les matrices : agrandissement.

    int H = imageCorrigee.rows();
    int W = imageCorrigee.cols();

    //   Eigen::MatrixXi imageCorrigee = imageUtilisee;
    intVectXi result = detectionInterligne(imageCorrigee);
    int interligneMoyen = result.i;

    std::cout << "Interligne : " << interligneMoyen << std::endl;
    imashow(imageCorrigee, 1);
    waitKey(0);

    Eigen::VectorXi Py = result.vec;
    Eigen::VectorXi localisation = rechercheDesXis(Py, W, interligneMoyen);

    int epaisseurMoyenne = histogrammeLargeurLigne(imageCorrigee);

    sousImagePorteeRes sousImagesData = sousImagePortee(localisation, imageCorrigee, interligneMoyen);
    std::vector<Eigen::MatrixXi> portees = sousImagesData.portees;
    int nportees = portees.size();
    for(int n = 0 ; n < nportees ; n++){

        //imashow(portees[nportees-1], 564);
        //waitKey(0);
        std::cout << "Nombre Portées : " << nportees << std::endl;
        Eigen::MatrixXi sousPortee = portees[n];
        Eigen::VectorXi abscisseTroisiemeLigne = sousImagesData.abscisseTroisiemeLigne;
        Eigen::VectorXi offsetX = sousImagesData.offsetX;
        Eigen::VectorXi Hprime = sousImagesData.Hprime;
        Eigen::VectorXi localisationN(5);

        for(int j = 0 ; j < 5 ; j++)
        {
            localisationN(j) = localisation(5*n+j) - offsetX(n);
        }
        effacementPortee(sousPortee, Py, interligneMoyen, localisationN,offsetX,Hprime, 0, W, epaisseurMoyenne);

        Eigen::MatrixXi cartedesempans=carteEmpans(sousPortee);
        Eigen::MatrixXf imagesecondephase=sellectionPlusieursEmpans(sousPortee);
        fusionVerticale(sousPortee,cartedesempans);
        Eigen::MatrixXi varcarteFinalDesEmpans=carteFinaleDesEmpans(imagesecondephase,interligneMoyen,cartedesempans);
        int nombre_empans = 0 ; // nombre d'empans dans la carte
        Eigen:: MatrixXi carteterminale=selectionUniqueEmpan(interligneMoyen,varcarteFinalDesEmpans, nombre_empans);
        //imashowcarte(carteterminale, 2);
        std::cout << "emboitage Image" << std::endl;
        //waitKey(0);
        std::vector<quadInt> resultatEmboitage = emboitageImage(sousPortee, carteterminale, interligneMoyen, nombre_empans);
        quadInt noteVue;
        int nnotes = resultatEmboitage.size();

// voir les notes
        for(int i = 0 ; i < nnotes  ; i++)
        {
           // imashownotesancien(resultatEmboitage[i], sousPortee, i);

            noteVue=resultatEmboitage[i];
            troisiemeLigne = sousImagesData.abscisseTroisiemeLigne(n);
            std::cout << "Troisieme Ligne : " << troisiemeLigne << std::endl;
            std::cout << "Offset X : " << offsetX(n) << std::endl;
            xh = noteVue.a;
            xb = noteVue.b;
            yg = noteVue.c;
            yd = noteVue.d;
            Eigen::MatrixXi imageNote = sousPortee.block(xh, yg, xb-xh, yd-yg);
            //imashow(imageNote, 4);
            //waitKey(0);
            note laNote;

            laNote = reconnaissancenotes(imageNote , troisiemeLigne, interligneMoyen, xb, yg, xh, yd, epaisseurMoyenne);

            imashownotes(laNote);
            ecritureNote(laNote,n);
            waitKey(0);
            //waitKey(0);
        }
    }

    waitKey(0);
    std::cout << "Traitement terminé. Bonne lecture !" << std::endl;                                             // Wait for a keystroke in the window
    return 0;
}

