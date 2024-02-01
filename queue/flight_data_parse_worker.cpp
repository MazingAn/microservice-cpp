#include "flight_data_parse_worker.h"
#include "flight_data_header.h"
#include "rabbitmq_consumer.h"
#include <iostream>

namespace fdqueue {

FlightDataParseWorker::FlightDataParseWorker(
    const std::string server_add, const int port, const std::string vhost_name,
    const std::string exchange_name, const std::string queue_name,
    const std::string rmq_user, const std::string rmq_pwd)
    : RmqConsumer(server_add, port, vhost_name, exchange_name, queue_name,
                  rmq_user, rmq_pwd) {}

bool FlightDataParseWorker::Consume(std::string msg_json) {
  std::cout << "get msg from server: " << msg_json << std::endl;
  fdmodels::FlightDataHeader header;
  header.DeSerializeFromJsonStr(msg_json);
  header.Print();
  return true;
}

FlightDataParseWorker::~FlightDataParseWorker() {
  // TODO : Clear others except amqp
}

} // namespace fdqueue
