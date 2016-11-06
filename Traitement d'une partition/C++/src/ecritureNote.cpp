#include "ecritureNote.h"

/*
Faut changer les machins rythme et hauteur
*/

int ecritureNote(note laNote,int i ){
    std::ofstream fichier("test.txt", std::ios::app);  // on ouvre le fichier en lecture et on se place à la fin :)
    if(fichier)  // si l'ouverture a réussi
    {
        // instructions
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
        fichier << "Note : " << noteS << " - Rythme : " << type << "numéro de portée " << i <<std::endl;
        fichier.close();  // on ferme le fichier
    }else{
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
    }
    return 0;
}
