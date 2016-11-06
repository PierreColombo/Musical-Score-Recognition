#include <mainFunction.h>
#include <dirent.h>
#include <vector>

// version n°(1.0m1.0c)

// API minimale écrite par Paul Muller le Vendredi 6 Mai 2016.

int main(){

    std::string commande;
    std::string image;
    int nimage;
    std::vector<std::string> images = {};
    int i = 0;
    std::cout << "Bienvenue dans le Programme de Reconnaissance de Partitions écrit par Pierre Colombo et Paul Mueller" << std::endl;
    std::cout << std::endl;
    std::cout << "Pour un guide des différentes commandes utilisables dans ce programme, veuillez entrer \"aide\"." << std::endl << std::endl;

    while(true){
        std::cout << "Commande : ";
        std::cin >> commande;
        std::cout << std::endl;
        if(commande == "lire" || commande == "read"){
            std::cout << "Nom de l'image : ";
            std::cin >> image;
            std::cout << "Debut du Traitement.";
            mainFunction(image);
        }else if(commande == "aide" || commande == "help"){
            std::cout << "Liste des Commandes disponibles :" << std::endl;
            std::cout << "- lire : lance le programme de Lecture d'Image." << std::endl;
            std::cout << "- lister : fournit une liste des images disponibles dans le fichier test." << std::endl;
            std::cout << "- fermer : ferme toutes les fenetres ouvertes par le programme." << std::endl;
            std::cout << "- quitter : quitte le programme." << std::endl;
        }else if (commande == "quitter" || commande == "exit"){
            return 0;
        }/*else if (commande == "fermer" || commande == "close"){
            cvStartWindowThread();
            cv::destroyAllWindows();
        }*/else if (commande == "lister" || commande == "list"){
            images = {};
            i = 0;
            DIR *dir;
            struct dirent *ent;
            if ((dir = opendir ("test/")) != NULL) {
              /* print all the files and directories within directory */
              while ((ent = readdir (dir)) != NULL) {
                std::cout << i << " - ";
                printf ("%s\n", ent->d_name);
                images.push_back(ent->d_name);
                i++;
              }
              closedir (dir);
            } else {
              /* could not open directory */
              perror ("");
              return EXIT_FAILURE;
            }
            std::cout << "Quelle image voulez-vous ouvrir ? ";
            std::cin >> nimage;
            std::cout << std::endl;
            if (nimage >= i || nimage < 0){
                std::cout << "Chiffre incorrect." << std::endl;
            }else{
                std::cout << "Debut du Traitement.";
                mainFunction(images.at(nimage));
            }
        }
    }
    return 0;
}
