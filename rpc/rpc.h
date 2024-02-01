#ifndef FDPP_RPC_RPC_H
#define FDPP_RPC_RPC_H

/**
 * This header define the rpc method to load data from server
 * **/

#include <string>

namespace fdrpc {

int LoadFlightDataById(long id, std::string &ret_json_str);

int TestBaidu(std::string &ret_json_str);

} // namespace fdrpc

#endif // !FDPP_RPC_RPC_H
