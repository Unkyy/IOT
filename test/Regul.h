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
    bool Xml_Condition(std::string str);
    bool time_range(int *time);
  private:
    ReqSql * requete = new  ReqSql();


};
