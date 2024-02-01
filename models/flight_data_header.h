#ifndef FDPP_MODELS_FLIGHT_DATA_HEADER_H
#define FDPP_MODELS_FLIGHT_DATA_HEADER_H

#include "serialize_interface.h"

namespace fdmodels {

class FlightDataHeader : SerializeInterface {

public:
  long id_;
  std::string aircraft_number_;
  std::string aircraft_type_;
  std::string fcd_type_;
  long fly_start_time_;
  long fly_end_time_;
  long engine_start_time_;
  long engine_end_time_;

public:
  void SerializeToJsonStr(std::string &out_str) override;
  void DeSerializeFromJsonStr(const std::string jsonStr) override;

  void Print();
};

} // namespace fdmodels

#endif // !FDPP_MODELS_FLIGHT_DATA_HEADER_H
