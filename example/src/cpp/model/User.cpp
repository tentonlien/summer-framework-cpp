#include <string>
#include <org/summerframework/core.h>

class User: public SerializedObject {
    public:
        int getUserId() {
            return this -> userId;
        }

        void setUserId(int userId) {
            this -> userId = userId;
        }

        void setUsername(std::string username) {
            this -> username = username;
        }

        User() {
            addDeclaredField("userId", &userId);
            addDeclaredField("username", &username);
            addDeclaredField("password", &password);
        }

        int userId;
        std::string username;
        std::string password;
};