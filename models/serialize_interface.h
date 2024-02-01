#ifndef FDPP_MODELS_SERIALIZE_INTERFACE_H
#define FDPP_MODELS_SERIALIZE_INTERFACE_H

#include <string>
namespace fdmodels {

class SerializeInterface {

public:
  virtual void SerializeToJsonStr(std::string &out_str) = 0;
  virtual void DeSerializeFromJsonStr(const std::string jsonStr) = 0;
};

} // namespace fdmodels

#endif // !FDPP_MODELS_SERIALIZE_INTERFACE_H
#define FDPP_MODELS_SERIALIZE_INTERFACE_H
