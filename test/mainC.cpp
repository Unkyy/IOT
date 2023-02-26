#include "Bdd.h"

int main ()
{
  string * tabLog;
  Bdd login;
  tabLog = login.getlogin();

  for (int i = 0; i < 4; i++) {
    cout << tabLog[i] << endl;
  }


  return 0;
}
