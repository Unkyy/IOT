#include "Bdd.h"

Bdd::Bdd(){
  ifstream fichier("conf.txt", ios::in);  // on ouvre le fichier en lecture

        if(fichier)  // si l'ouverture a réussi
        {
          string ligne;
          for(int i = 0;getline(fichier, ligne); i++)  // tant que l'on peut mettre la ligne dans "contenu"
          {
              tab[i] = ligne;
              //cout << tab[i] << endl;
          }
          fichier.close();  // on ferme le fichier
        }
        else
                cerr << "Impossible d'ouvrir le fichier !" << endl;
}
string * Bdd::getlogin(){
    return tab;
}
