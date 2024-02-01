#include "rpc.h"
#include "restclient-cpp/restclient.h"
#include <sstream>

namespace fdrpc {

int LoadFlightDataById(long id, std::string &ret_json_str) {
  std::ostringstream oss;
  oss << "http://localhost:8080/query/" << id;
  RestClient::Response r = RestClient::get(oss.str());
  ret_json_str = r.body;
  return r.code;
}

int TestBaidu(std::string &ret_json_str) {
  RestClient::Response r = RestClient::get("http://www.baidu.com");
  ret_json_str = r.body.c_str();
  return r.code;
}

} // namespace fdrpc
