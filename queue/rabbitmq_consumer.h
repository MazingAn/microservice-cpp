#ifndef FDPP_QUEUE_RABBITMQ_CONSUMER_H
#define FDPP_QUEUE_RABBITMQ_CONSUMER_H

#include "rabbitmq-c/amqp.h"
#include <string>

namespace fdqueue {

/** A RabbitMq Consumer is provide to connect rabbitmq and bind queue
 * when receive message from queue auto process the message
 *
 * you can create your own consumer by extend this class
 * then oveeride the run method to do you self logic when consume message
 *
 * question: why divide the productor and comsumer?
 * answer: we use rabbitmq to trans message thought different microservices
 * so we only do productor or only do comsumer
 * we don't product and consume the same queue in single service.
 * **/
class RmqConsumer {

private:
  std::string server_add_;
  int port_;
  std::string vhost_name_;
  std::string exchange_name_;
  std::string queue_name_;
  std::string rmq_user_;
  std::string rmq_pwd_;
  std::string bind_key_;

protected:
  amqp_socket_t *socket = nullptr;
  amqp_connection_state_t conn_;

private:
  void InitConn();
  void Die(const amqp_rpc_reply_t &reply, const std::string exception_info);

protected:
  virtual bool Consume(std::string msg_json) = 0;

public:
  RmqConsumer(const std::string server_add, const int port,
              const std::string vhost_name, const std::string exchange_name,
              const std::string queue_name, const std::string rmq_user,
              const std::string rmq_pwd);
  virtual ~RmqConsumer();
  void Run();
  void Stop();
};

} // namespace fdqueue

#endif // !FDPP_QUEUE_RABBITMQ_CONSUMER_H
