#ifndef FDPP_QUEUE_FLIGHT_DATA_PARSE_WORKER
#define FDPP_QUEUE_FLIGHT_DATA_PARSE_WORKER

#include "rabbitmq_consumer.h"
namespace fdqueue {

class FlightDataParseWorker : public RmqConsumer {
public:
  FlightDataParseWorker(const std::string server_add, const int port,
                        const std::string vhost_name,
                        const std::string exchange_name,
                        const std::string queue_name,
                        const std::string rmq_user, const std::string rmq_pwd);
  virtual ~FlightDataParseWorker();

protected:
  virtual bool Consume(std::string msg_json) override;
};

} // namespace fdqueue

#endif // !FDPP_QUEUE_FLIGHT_DATA_PARSE_WORKER
