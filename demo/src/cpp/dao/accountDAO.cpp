#include <string>
#include "sql.h"
#include "../entity/userEntity.h"
using namespace std;


class accountDAO {
  public:

    string registerAccount(UserEntity);
};

string accountDAO::registerAccount(UserEntity user) {
    Sql sql("summer-demo");
    sql.query("INSERT INTO accounts VALUES(" + user.name + "," + user.gender + ")");
    return "";
}