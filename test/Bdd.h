#ifndef BDD_H
#define BDD_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;


class Bdd{
  public:
      Bdd();
      string * getlogin();
    private:
      string tab[4];
};
#endif
