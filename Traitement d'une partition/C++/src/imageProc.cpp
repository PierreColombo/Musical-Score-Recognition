#include <imageProc.h>

Eigen::MatrixXi niveauGris(cv::Mat imgData, byte seuil){
    int n = imgData.rows;
    int m = imgData.cols;
    Eigen::MatrixXi result(n, m);

    // recherche max et min.
    /*int ma = imgData.at<int>(0,0);
    int mi = imgData.at<int>(0,0);
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++){
            int x = imgData.at<int>(i,j);
            if (x > ma){
                ma = x;
            }if(x < mi){
                mi = x;
            }
        }
    }*/

    cv::Mat binaryMat(imgData.size(), imgData.type());
    cv::threshold(imgData, binaryMat, seuil, 1, cv::THRESH_BINARY_INV);

//    std::cout << binaryMat.depth() << std::endl << binaryMat.channels() << std::endl;

/*    namedWindow( "Display window 564", cv::WINDOW_AUTOSIZE );       // Create a window for display.
    imshow( "Display window 564", binaryMat );*/
    // A optimiser.
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++){
            result(i,j) = binaryMat.at<uchar>(i,j);
        }

    }


   /* for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++){
            std::cout << result(i,j) <<
        }
    }*/
    return result;
}

// NOt working very well.
void imashow(Eigen::MatrixXi imageGrise, int num){
    int n = imageGrise.rows();
    int m = imageGrise.cols();
    cv::Mat result = cv::Mat::zeros(n, m, CV_8UC1);
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++){
            result.at<uchar>(i,j) = (255*imageGrise(i,j));
        }
    }
    std::string window = "Display Window " + num;
    namedWindow( window, cv::WINDOW_AUTOSIZE );       // Create a window for display.
    imshow( window, result );
}

void imashowcarte(Eigen::MatrixXi imageGrise, int num){
    int n = imageGrise.rows();
    int m = imageGrise.cols();
    cv::Mat result = cv::Mat::zeros(n, m, CV_8UC1);
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++){
            result.at<uchar>(i,j) = (10*imageGrise(i,j));
        }
    }
    std::string window = "Display Window " + num;
    namedWindow( window, cv::WINDOW_AUTOSIZE );       // Create a window for display.
    imshow( window, result );
}

void imashownotes(note laNote){
    Eigen::MatrixXi imageNote = laNote.imageNote;
    int H = imageNote.rows();
    int W = imageNote.cols();
    int sound = laNote.sound;
    std::string type = laNote.symbole;
    std::string noteS, texteFinal;
    if (sound > 11 || sound < 0){
        noteS = "";
    }else{
        switch(sound){
            case 0: noteS = "Do"; break;
            case 1: noteS = "Do diese"; break;
            case 2: noteS = "Re"; break;
            case 3: noteS = "Re diese"; break;
            case 4: noteS = "Mi"; break;
            case 5: noteS = "Fa"; break;
            case 6: noteS = "Fa diese"; break;
            case 7: noteS = "Sol"; break;
            case 8: noteS = "Sol diese"; break;
            case 9: noteS = "La"; break;
            case 10:noteS = "La diese"; break;
            case 11:noteS = "Si"; break;
        }
    }
    texteFinal = noteS + " - " + type;
    std::cout << texteFinal << std::endl;

    int fontFace = cv::FONT_HERSHEY_SCRIPT_SIMPLEX;
    double fontScale = 2;
    int thickness = 2;
    int baseline = H;
    cv::Size textSize = cv::getTextSize(texteFinal, fontFace, fontScale, thickness, &baseline);
    baseline += thickness;
    int N = textSize.width;
    N = (N * 2) / 3;
    int M = textSize.height;

    cv::Point org;
    org.x = 0; org.y = H+M-3;
    int Wp = std::max(W, N + 4);

    cv::Mat res(H+M, Wp, CV_32F);
    for(int i = 0 ; i < H ; i++){
        for(int j = 0 ; j < W ; j++){
            res.at<float>(i,j) = (255*imageNote(i,j));
        }
    }for(int i = H ; i < H+M ; i++){
        for(int j = 0 ; j < Wp ; j++){
            res.at<float>(i,j) = 0;
        }
    }for(int i = 0 ; i < H+M ; i++){
        for(int j = W ; j < Wp ; j++){
            res.at<float>(i,j) = 0;
        }
    }

    cv::putText(res, texteFinal, org, cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar::all(255), 1, 8, false);
    imshow("Note", res);
}


void imashownotesancien(quadInt loca, Eigen::MatrixXi imag, int i){
    Eigen::MatrixXi imanote;
    int xh = loca.a;
    int xb = loca.b;
    int yg = loca.c;
    int yd = loca.d;
    imanote = imag.block(xh, yg, xb-xh, yd-yg);
    imashow(imanote, i);
}

