#include "flight_data_header.h"
#include "flight_data_header_repo.h"
#include "flight_data_parse_worker.h"
#include "rpc.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {

  // TEST001 : Json and Rpc
  std::string ret_json_str;
  fdmodels::FlightDataHeader header;
  if (fdrpc::LoadFlightDataById(1982828281L, ret_json_str) == 200) {
    header.DeSerializeFromJsonStr(ret_json_str);
    header.Print();
    std::string out_json_str;
    header.SerializeToJsonStr(out_json_str);
    std::cout << out_json_str << std::endl;
  } else {
    std::cerr << "Networking Error." << std::endl;
  }

  // TEST002 : RabbitMQClient

  try {
    fdqueue::FlightDataParseWorker worker(
        "127.0.0.1", 5672, "/", "FLIGHT_DATA_PARSE_EXCHANGE",
        "FLIGHT_DATA_PARSE_QUEUE", "admin", "admin");
    worker.Run();
  } catch (const char *msg) {
    std::cerr << msg << std::endl;
  }

  // TEST003 : MariaDb
  fddb::FlightDataHeaderRepo header_repo("jdbc:mariadb://localhost:3306/fdpp",
                                         "root", "123456");
  header_repo.Connect();
  header_repo.CreateOne(header);
  std::cout << "create a header. then query" << std::endl;
  fdmodels::FlightDataHeader myHeader1 = header_repo.QueryById(header.id_);
  myHeader1.Print();

  header.aircraft_number_ = "10752";
  header_repo.UpdateById(header.id_, header);
  std::cout << "Update the header. then query" << std::endl;
  fdmodels::FlightDataHeader myHeader2 = header_repo.QueryById(header.id_);
  myHeader2.Print();

  return 0;
}
