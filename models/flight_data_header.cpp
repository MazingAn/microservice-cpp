#include "flight_data_header.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

#include <iostream>

namespace fdmodels {

/** convert the modle to json string.
 * the json string use snake_named naming type
 * @std::string& out_str is the jsonStr witch will be setted
 * **/
void FlightDataHeader::SerializeToJsonStr(std::string &out_str) {
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  writer.StartObject();
  writer.String("id");
  writer.Int64(id_);
  writer.String("aircraft_number");
  writer.String(aircraft_number_.c_str());
  writer.String("aircraft_type");
  writer.String(aircraft_type_.c_str());
  writer.String("fcd_type");
  writer.String(fcd_type_.c_str());
  writer.String("fly_start_time");
  writer.Int64(fly_start_time_);
  writer.String("fly_end_time");
  writer.Int64(fly_end_time_);
  writer.String("engine_start_time");
  writer.Int64(engine_start_time_);
  writer.String("engine_end_time");
  writer.Int64(engine_end_time_);
  writer.EndObject();
  out_str = buffer.GetString();
}

/** Setting the fields from a JsonString.
 * the json string may from some server but with the snake_named naming type
 * @std::string& json_str : input json string
 * notice : this method may throw exception when json string is not valid.
 * **/
void FlightDataHeader::DeSerializeFromJsonStr(const std::string json_str) {
  rapidjson::Document document;
  document.Parse(json_str.c_str());
  id_ = document["id"].GetInt64();
  aircraft_number_ = document["aircraft_number"].GetString();
  aircraft_type_ = document["aircraft_type"].GetString();
  fcd_type_ = document["fcd_type"].GetString();
  fly_start_time_ = document["fly_start_time"].GetInt64();
  fly_end_time_ = document["fly_end_time"].GetInt64();
  engine_start_time_ = document["engine_start_time"].GetInt64();
  engine_end_time_ = document["engine_end_time"].GetInt64();
}

void FlightDataHeader::Print() {
  std::cout << "id : " << id_ << std::endl;
  std::cout << "aircraft_number : " << aircraft_number_ << std::endl;
  std::cout << "aircraft_type : " << aircraft_type_ << std::endl;
  std::cout << "fcd_type : " << fcd_type_ << std::endl;
  std::cout << "fly_start_time : " << fly_start_time_ << std::endl;
  std::cout << "fly_end_time : " << fly_end_time_ << std::endl;
  std::cout << "engine_start_time :  " << engine_start_time_ << std::endl;
  std::cout << "engine_end_time : " << engine_end_time_ << std::endl;
}

} // namespace fdmodels
