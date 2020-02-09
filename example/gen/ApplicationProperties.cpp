#include <org/summerframework/core.h>

void ApplicationContext::loadData() {
    this -> setApplicationProperty("server.port", "1234");

    this -> setApplicationName("DemoApplication");
}