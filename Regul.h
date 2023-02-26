#include "SocketClient.h"
#include "ReqSql.h"
#include <vector>
#include <string>
#include <time.h>
class Regul : public SocketClient
{
  public:
    Regul(int in);
    void commande_chauffage();
    void commande_allum();
    void commande_allum2();

  private:
    ReqSql * requete = new  ReqSql();
    ReqSql * requete2 = new  ReqSql();
    ReqSql * requete3 = new  ReqSql();



};
