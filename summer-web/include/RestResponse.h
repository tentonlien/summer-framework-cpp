// Created by Tenton Lien on 12/12/2019

#ifndef REST_RESPONSE_H
#define REST_RESPONSE_H

#include <org/summerframework/core.h>
#include <string>

class RestResponse: public SerializedObject {
	public:
    RestResponse();
    std::string toString();

		static RestResponse* success();
    static RestResponse* success(SerializedObject);
    static RestResponse* fail(int, std::string);

    int getCode();
    void setCode(int);

    std::string getMessage();
    void setMessage(std::string);

    SerializedObject getData();
    void setData(SerializedObject);
	
  private:
		int code;
		std::string message;
    SerializedObject data;
};

#endif