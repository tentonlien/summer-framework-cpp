#include <string>
#include "sql.h"
#include "../entity/UserEntity.cpp"
using namespace std;

class accountDAO {
  public:
    string registerAccount(UserEntity user) {
      SqlConnector sqlConnector("mysql://localhost:3306/database?user=root&password=xxxxxx");
      return "";
    }
};

