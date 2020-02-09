#include <org/summerframework/core.h>
#include <org/summerframework/web.h>
//#include "../model/User.cpp"

///RestController
class LoginController : public Controller {
  public:
    ///RequestMapping("/login")
    RestResponse login() {
        // Login
        RestResponse restResponse;
        if (request -> method == HttpRequestMethod.POST) {
            // User user;
            // user.setUsername("new user");
            // user.password = "123456";
            // restResponse.setData(user);
            // std::string sessionId = "afsgasgafadsfawefrfgasgasfa";
            std::cout << json::parse(request -> body)["id"] << std::endl;
            return *(RestResponse::success());
        }
            
        // Check login status
        else if (request -> method == HttpRequestMethod.GET) {
            
        }
        return restResponse;
    }       
};