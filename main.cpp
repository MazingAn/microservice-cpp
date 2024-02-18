#include "flight_data_header.h"
#include "flight_data_header_repo.h"
#include "flight_data_parse_worker.h"
#include "rpc.h"
#include "time_utils.h"
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

  /* try { */
  /*   fdqueue::FlightDataParseWorker worker( */
  /*       "127.0.0.1", 5672, "/", "FLIGHT_DATA_PARSE_EXCHANGE", */
  /*       "FLIGHT_DATA_PARSE_QUEUE", "admin", "admin"); */
  /*   worker.Run(); */
  /* } catch (const char *msg) { */
  /*   std::cerr << msg << std::endl; */
  /* } */

  // TEST003 : MariaDb
  fddb::FlightDataHeaderRepo header_repo("jdbc:mariadb://localhost:3306/fdpp",
                                         "root", "123456");
  header_repo.Connect();
  for (long i = 1; i < 10000; i++) {
    fdmodels::FlightDataHeader myHeader;
    myHeader.id_ = i;
    myHeader.aircraft_number_ = "10827";
    myHeader.aircraft_type_ = "F16";
    myHeader.fcd_type_ = "LOCCEED";
    myHeader.fly_start_time_ = fdutils::now_timestamp();
    myHeader.fly_end_time_ = fdutils::get_timestamp(2024, 2, 1, 19, 16, 0);
    myHeader.engine_start_time_ = fdutils::add_now_timestamp(10 * 60);
    myHeader.engine_end_time_ =
        fdutils::add_timestamp(2024, 2, 1, 19, 16, 0, -10 * 60);
    header_repo.CreateOne(myHeader);
  }

  std::cout << "create a header. then query" << std::endl;
  fdmodels::FlightDataHeader myHeader1 = header_repo.QueryById(1L);
  myHeader1.Print();

  myHeader1.aircraft_number_ = "10752";
  header_repo.UpdateById(myHeader1.id_, myHeader1);
  std::cout << "Update the header. then query" << std::endl;
  fdmodels::FlightDataHeader myHeader2 = header_repo.QueryById(1L);
  myHeader2.Print();

  for (int i = 1; i <= 1000; i++) {
    std::vector<fdmodels::FlightDataHeader> headers =
        header_repo.QueryAndOrder(i, 10, "id");
    for (auto item : headers) {
      item.Print();
    }
  }
  return 0;
}
