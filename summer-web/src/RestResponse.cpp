/* Created by Tenton Lien on 12/12/2019 */

#include <string>
#include <nlohmann-json/json.hpp>

#include "RestResponse.h"

using json = nlohmann::json;

RestResponse* RestResponse::success() {
	RestResponse* restResponsePointer = new RestResponse();
	restResponsePointer -> code = 0;
	restResponsePointer -> message = "success";
	return restResponsePointer;
}

RestResponse* RestResponse::success(SerializedObject data) {
	RestResponse* restResponsePointer = new RestResponse();
	restResponsePointer -> code = 0;
	restResponsePointer -> message = "success";
	restResponsePointer -> data = data;
	return restResponsePointer;
}

RestResponse* RestResponse::fail(int code, std::string message) {
	RestResponse* restResponsePointer = new RestResponse();
	restResponsePointer -> code = code;
	restResponsePointer -> message  = message;
	return restResponsePointer;
}


int RestResponse::getCode() {
	return this -> code;
}


void RestResponse::setCode(int code) {
	this -> code = code;
}


std::string RestResponse::getMessage() {
	return this -> message;
}


void RestResponse::setMessage(std::string message) {
	this -> message = message;
}


SerializedObject RestResponse::getData() {
	return this -> data;
}


void RestResponse::setData(SerializedObject data) {
	this -> data = data;
}


RestResponse::RestResponse() {
	addDeclaredField("code", &code);
	addDeclaredField("message", &message);
	addDeclaredField("data", &data);
}