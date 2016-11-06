#include<reconnaissancenotes.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/gpu/gpu.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <imageProc.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

//j'ai mis le retour avec des strings do, ré, mi,fa
// dans le pgr on fait les opés dans cet ordre
// création du template
//creation de la matrice résultat du template
//localisation du cercle
// en fonction du cercle on saura la note


note reconnaissancenotes(Eigen::MatrixXi img , int troisiemeLigne, int interligne, int xb, int yb, int xh, int yd, int epaisseur){
        // si c'est assez large
    if(img.rows()>interligne && img.cols()>interligne){
        // définition du template
        // initialisation
        int milieu;
        cv::Mat templ;
        if (interligne&1){
            templ.create(interligne,interligne, CV_32FC1);
            milieu = (interligne-1)/2;
        }else{
            templ.create(interligne+1,interligne+1, CV_32FC1);
            milieu = (interligne)/2+1;
        }
//remplissage avec des 0 et des 1
        int i;
        int j;
        for(i=0; i<templ.rows; i++){
            for (j=0; j<templ.cols; j++){
                if ((i-milieu)*(i-milieu)+(j-milieu)*(j-milieu)<interligne*interligne/4){
                    templ.at<float>(i,j)= ((float) 1);
                }else{
                    templ.at<float>(i,j)= ((float) 0);
                }
            }
        }
        // Create the result matrix
        int resultcols =  abs(img.cols() - templ.cols) + 1;
        int resultrows = abs(img.rows() - templ.rows) + 1;

        Eigen::MatrixXi toto(resultrows,resultcols);
        cv::Mat result(toto.rows(), toto.cols(), CV_32FC1, toto.data());

        int match_method = CV_TM_CCORR;

// Faut convertir le eigen vers le opencv

        cv::Mat img_OpenCV = cv::Mat::ones(img.rows(), img.cols(), CV_32FC1);
        for(int i=0 ; i < img.rows() ; i++){
            for(int j=0; j < img.cols() ; j++){
                img_OpenCV.at<float>(i,j)=((float) img(i,j));
            }
        }

// Do the Matching and Normalize
        cv::matchTemplate( img_OpenCV, templ, result, match_method );
        // cv::normalize( result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat() );

// Localizing the best match with minMaxLoc
        double minVal;
        double maxVal;
        cv::Point minLoc;
        cv::Point maxLoc;
        cv::Point matchLoc;

        cv::minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc,cv::Mat() );
// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
        {
            matchLoc = maxLoc;
        }
        int n=img.rows();

// Show me what you got ca sert a rien XD enfin je crois  :p
//   cv::rectangle( img_OpenCV, matchLoc, cv::Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ),255 , 2, 8, 0 );
        // cv::rectangle( result, matchLoc, cv::Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), 255, 2, 8, 0 );


        int milieuNote  = matchLoc.y + templ.cols / 2 + xh ;
        //int milieu_de_la_note=52;
// en fonction de la note on place: seuil simple le 1/8 est arbitraire en fait (c'est une tolérance) émoticône smile un offset a rajouter si ca marche pas essaye premiere_ligne=première_ligne-le coin superieur
//gauchedelaboitedelanote ?
// On peut forcer cette tolérance à interligne/4 de façon à paver le plan d'une manière uniforme.

        float seuil = interligne/4;
        float pas = interligne/2;
        note retour;
        retour.imageNote = img;
        retour.sound = -1;
        if(maxVal > epaisseur*3*(interligne-epaisseur)){

                std::cout << milieuNote << std::endl;

            if (troisiemeLigne - interligne + seuil > milieuNote && troisiemeLigne - interligne - seuil < milieuNote)
            {
                std::cout << "Ré" << std::endl;
                retour.sound=2;
            }
            else if ((troisiemeLigne - (3*interligne)/2 + seuil > milieuNote && troisiemeLigne - (3*interligne)/2 - seuil < milieuNote) || (troisiemeLigne + 2*interligne + seuil > milieuNote && troisiemeLigne + 2*interligne - seuil < milieuNote))
            {
                std::cout << "mi" << std::endl;
                retour.sound=4;
            }
            else if ((troisiemeLigne - 2*interligne + seuil > milieuNote && troisiemeLigne - 2*interligne - seuil < milieuNote) || (troisiemeLigne + (3*interligne)/2 + seuil > milieuNote && troisiemeLigne + (3*interligne)/2 - seuil < milieuNote))
            {
                std::cout << "fa" << std::endl;
                retour.sound=5;
            }
            else if (troisiemeLigne + interligne + seuil > milieuNote && troisiemeLigne + interligne - seuil < milieuNote)
            {
                std::cout << "sol" << std::endl;
                retour.sound=7;
            }
            else if (troisiemeLigne + interligne/2 + seuil > milieuNote && troisiemeLigne + interligne/2 - seuil < milieuNote)
            {
                std::cout << "la" << std::endl;
                retour.sound=9;
            }
            else if (troisiemeLigne + seuil > milieuNote && troisiemeLigne - seuil < milieuNote)
            {
                std::cout << "si" << std::endl;
                retour.sound=11;
            }
            else if (troisiemeLigne - interligne/2 + seuil > milieuNote && troisiemeLigne - interligne/2 - seuil < milieuNote)
            {
                std::cout << "do" << std::endl;
                retour.sound=0;
            }
            /*else if ()
            {
                std::cout << "Ré haut" << std::endl;
                retour.sound=2;
            }
            else if ()
            {
                std::cout << "mi  haut" << std::endl;
                retour.sound=4;
            }
            else if ()
            {
                std::cout << "fa  haut" << std::endl;
                retour.sound=5;
            }
            else if ()
            {
                std::cout << "sol  haut" << std::endl;
                retour.sound=7;
            }*/
            else
            {
                std::cout << "Inconnue" << std::endl;

            }

            std::cout << "Fin de la reconnaissance de la note " << std::endl;

            int abscissedurond = matchLoc.y + yb ;
            std::cout << "c'est une note" << std::endl;
            std::cout<<"matchloc.x"<< abscissedurond<<std::endl;
            std::cout<<"matchloc.y"<< matchLoc.y+yb<<std::endl;

            std::cout<<"milieu de la note"<< milieuNote <<std::endl;

            retour.x=abscissedurond;
            retour.y=milieuNote;
            //float epsilon = 0.01;
            //int val;
            Eigen::MatrixXi image = Eigen::MatrixXi::Zero(img.rows(), img.cols());
            for(int i = 0 ; i < img.rows() ; i++){
                for(int j = 0 ; j < img.cols() ; j++){
                    image(i,j) = img(i,j);
                }
            }
            for(int i = matchLoc.y ; ((i < img.rows()) && (i < templ.rows+matchLoc.y)) ; i++){
                for(int j = matchLoc.x ; ((j < img.cols()) && (j < templ.cols+matchLoc.x)) ; j++){
                    image(i, j) = 0;
                }
            }
            retour = reconnaissanceCroche(image, interligne, retour, matchLoc.x, matchLoc.y);
            return retour;
        }

        else
            //si modif modifier la suite too
        {
            std::cout << "ceci n'est pas une note" << std::endl;
            // dièse ? bémol ? barre de mesure ? clef de sol (ydébut )? profil horizontal
            Eigen::MatrixXi somme = Eigen::MatrixXi::Zero(img.rows(),1);
            for(int i=0; i<img.rows() ; i++)
            {
                for(int j=0; j<img.cols(); j++)
                {
                    somme(i,0)=img(i,j)+somme(i,0);
                }
            }
            std::cout << img<<std::endl;
            std::cout<<" somme       " <<somme<<std::endl;

            if (somme.maxCoeff()< 2 * epaisseur)
            {
                std::cout << "ceci est une barre de mesure" << std::endl;
                retour.symbole="barre de mesure";

            }

            else
            {
                std::cout << "ceci est autre chose" << std::endl;

            }
            retour.x=-1;
            retour.y=-1;

            return retour;
        }

    }
    else

        //si modif modifier la suite too
    {

        {
            std::cout << "ceci n'est pas une note" << std::endl;
            // dièse ? bémol ? barre de mesure ? clef de sol (ydébut )? profil horizontal
            Eigen::MatrixXi somme = Eigen::MatrixXi::Zero(img.rows(),1);
            for(int i=0; i<img.rows() ; i++)
            {
                for(int j=0; j<img.cols(); j++)
                {
                    somme(i,0)=img(i,j)+somme(i,0);
                }
            }
            std::cout << img<<std::endl;
            std::cout<<" somme       " <<somme<<std::endl;
            int epaisseur = floor(interligne/5);
            note retour;
            if (somme.maxCoeff()< 2 * epaisseur)
            {
                std::cout << "ceci est une barre de mesure" << std::endl;
                retour.symbole="barre de mesure";

            }

            else
            {
                std::cout << "ceci est autre chose" << std::endl;

            }
            retour.x=-1;
            retour.y=-1;

            return retour;
        }
    }
}


/*

CODES STRING pour CLASSIFICATION CARACTERES :
"Ronde" - "Blanche" - "Croche0" (noire) - "Croche1" (croche simple) - "Croche2" - "Croche3" - "Croche..."
"BarreMesure" - "Soupir" - "Dièse" - "Bémol" - [les autres trucs]




CODES INT pour CLASSIFICATION NOTES :
0 : do.
1 : do dièse.
2 : ré.
3 : ré dièse.
4 : mi.
5 : fa.
6 : fa dièse.
7 : sol.
8 : sol dièse.
9 : la.
10: la dièse.
11: si.

De cette manière, on peut faire des modifications rapides de la hauteur des notes via une addition modulo 12.

*/

// interm : la note reconnue : do, ré, mi...

note reconnaissanceCroche(Eigen::MatrixXi img, int interligne, note interm, int matchlocx, int matchlocy){
    int W = img.cols();
    int H = img.rows();
    int Hp= interligne/4;
  /*  imashow(img, 3);
    cv::waitKey(0);*/
    cv::Mat templ, imag, result;
    templ.create(Hp, W/2, CV_32FC1);
    imag.create(H, W, CV_32FC1);

    for(int i = 0 ; i < Hp ; i++){
        for(int j = 0 ; j < W/2 ; j++){
            templ.at<float>(i,j) = (float) 1;
        }
    }for(int i = 0 ; i < H ; i++){
        for(int j = 0 ; j < W ; j++){
            imag.at<float>(i,j) = (float) img(i,j);
        }
    }
    int resultcols = img.cols() - templ.cols + 1;
    int resultrows = img.rows() - templ.rows + 1;
    double minVal, maxVal;
    cv::Point minLoc;
    cv::Point maxLoc;
    cv::Point matchLoc;
    result.create(resultrows, resultcols, CV_32FC1);

    cv::matchTemplate(imag, templ, result, CV_TM_CCORR);
    cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());
    matchLoc = maxLoc;
    // La croche est-elle simple, double, ...?
    int nombreCroche = 0;
    int seuil = 0.01;
    int i = 0;
    int j = 0;
    int ymin = 0;
    int ymax = 0;
    while (maxVal > (interligne * W) / 9){
        nombreCroche++;

        // Effacement en Croissance de Région. On repère tout d'abord tout ce qui est à gauche et à droite; puis efface tout ce qui se situe en dessous et au dessus..

        // On repère jusqu'où effacera.

        for(int i = maxLoc.y ; i < maxLoc.y+Hp && i < H ; i++){
            j = matchLoc.x;
            // Tant qu'on a un truc non-différent de 0.
            while(j >= 0 && imag.at<float>(i,j) > seuil){
                j--;
            }if (j < ymin){
                ymin = j;
            }
            j = matchLoc.x;
            while(j < W && imag.at<float>(i,j) > seuil){
                j++;
            }if (j > ymax){
                ymax = j;
            }
        }

        // On efface ce qui se situe directement au dessus SANS effacer la première ligne du template matching.

        for(int j = ymin ; j <= ymax ; j++){
            i = matchLoc.y - 1;
            while(i >= 0 && imag.at<float>(i,j) > seuil){
                imag.at<float>(i,j) = 0;
                i--;
            }
        }

        for(int j = ymin ; j <= ymax ; j++){
            i = matchLoc.y;
            while(i < H && imag.at<float>(i,j) > seuil){
                imag.at<float>(i,j) = 0;
                i++;
            }
        }
        // On efface tout ce qui est en dessous.
        /*
        for(int y = matchLoc.x ; y < matchLoc.x + W/2 && y < W ; y++){
            x = matchLoc.y;
            while
        }
        */

     /*   imshow("Test Test Test", imag);
        cv::waitKey(0);*/

        cv::matchTemplate(imag, templ, result, CV_TM_CCORR);
        cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());
        matchLoc = maxLoc;
    }
    if (nombreCroche == 0){
        // Il pense que c'est une noire. Mais en est-ce vraiment une ?
        int xnote = interligne/2 + matchlocy;
        int ynote = interligne/2 + matchlocx;
        int xmin, xmax;
        int ymax = 0;
        // ON ne regarde que le côté opposé par la ligne de milieu de l'image pour trouver l'écart..
        if (xnote < H/2){
            xmin = H/2; xmax = H;
        }else{
            xmin = 0; xmax = H/2;
        }
        for(int y = 0 ; y < W ; y++){
            for(int x = xmin ; x < xmax ; x++){
                if (interm.imageNote(x,y) != 0 && y > ymax){
                    ymax = y;
                }
            }
        }if(ymax > (interligne*2)/3){
            interm.symbole = "croche";
        }else{
            interm.symbole = "noire";
        }
    }else if (nombreCroche == 1){
        interm.symbole = "croche";
    }else{
        interm.symbole = "croche" + std::to_string(nombreCroche);
    }std::cout << interm.symbole << std::endl;
    return interm;
}









