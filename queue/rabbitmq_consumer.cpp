#include "rabbitmq_consumer.h"
#include "rabbitmq-c/framing.h"
#include "rabbitmq-c/tcp_socket.h"
#include <string>

namespace fdqueue {

RmqConsumer::RmqConsumer(const std::string server_add, const int port,
                         const std::string vhost_name,
                         const std::string exchange_name,
                         const std::string queue_name,
                         const std::string rmq_user,
                         const std::string rmq_pwd) {
  server_add_ = server_add;
  port_ = port;
  vhost_name_ = vhost_name;
  exchange_name_ = exchange_name;
  queue_name_ = queue_name;
  rmq_user_ = rmq_user;
  rmq_pwd_ = rmq_pwd;
  bind_key_ = queue_name;
  InitConn();
}

/** Create connection to rabbitmq server
 * this function may throw exceptions
 * **/
void RmqConsumer::InitConn() {
  /*******
   *   CONN ->  (channel]) ->  {Queue}   -> [Exchange]
   * *******/

  // 1. create connection
  conn_ = amqp_new_connection();

  // 2. init socket
  socket = amqp_tcp_socket_new(conn_);
  if (!socket) {
    throw "create rabbitmq socket error.";
  }

  // 3. connect to server
  int ret = amqp_socket_open(socket, server_add_.c_str(), port_);
  if (ret) {
    throw "Connect Rabbitmq Server Error.";
  }

  // 4. longin to server
  Die(amqp_login(conn_, vhost_name_.c_str(), 1, 131072, 10,
                 AMQP_SASL_METHOD_PLAIN, rmq_user_.c_str(), rmq_pwd_.c_str()),
      "login rabbitmq server error");

  // 5. open one channel
  amqp_channel_open(conn_, 1);
  Die(amqp_get_rpc_reply(conn_), "Open Channel Error.");

  // 6. declare exchange
  amqp_exchange_declare(conn_, 1, amqp_cstring_bytes(exchange_name_.c_str()),
                        amqp_cstring_bytes("fanout"), 0, 0, 0, 0,
                        amqp_empty_table);
  Die(amqp_get_rpc_reply(conn_), "Declare Exchange Error.");

  // 7. declare queue
  amqp_queue_declare(conn_, 1, amqp_cstring_bytes(queue_name_.c_str()), 0, 0, 0,
                     0, amqp_empty_table);
  Die(amqp_get_rpc_reply(conn_), "Declare Queue Error.");

  // 8. bind exchange and queue
  amqp_queue_bind(conn_, 1, amqp_cstring_bytes(queue_name_.c_str()),
                  amqp_cstring_bytes(exchange_name_.c_str()),
                  amqp_cstring_bytes(bind_key_.c_str()), amqp_empty_table);
  Die(amqp_get_rpc_reply(conn_), "Bind Queue Error.");

  amqp_basic_consume(conn_, 1, amqp_cstring_bytes(queue_name_.c_str()),
                     amqp_empty_bytes, 0, 0, 0, amqp_empty_table);
  Die(amqp_get_rpc_reply(conn_), "Begine Consume Error.");
}

/** Create a loop to consume message
 * this is a structed method
 * the real consume must be overrided
 **/
void RmqConsumer::Run() {
  amqp_frame_t frame;
  while (true) {
    amqp_rpc_reply_t ret;
    amqp_envelope_t envelope;
    amqp_maybe_release_buffers(conn_);
    ret = amqp_consume_message(conn_, &envelope, nullptr, 0);

    if (AMQP_RESPONSE_NORMAL != ret.reply_type) {
      return;
    } else {
      std::string msg_body = std::string((char *)envelope.message.body.bytes);
      bool consume_success = this->Consume(msg_body);
      if (consume_success) {
        /* TODO : add death message queue
         * If the cosume logic cause error we can retry some times
         * then create a death message queue and push them to this queue */
        amqp_basic_ack(conn_, 1, envelope.delivery_tag, 0);
      }
      amqp_destroy_envelope(&envelope);
    }
  }
}

void RmqConsumer::Stop() {
  amqp_channel_close(conn_, 1, AMQP_REPLY_SUCCESS);
  amqp_connection_close(conn_, AMQP_REPLY_SUCCESS);
  amqp_destroy_connection(conn_);
}

/** This function is used to throw exceptions
 * when the common amqp rpc got error
 * */
void RmqConsumer::Die(const amqp_rpc_reply_t &reply,
                      const std::string exception_info) {
  switch (reply.reply_type) {
  case AMQP_RESPONSE_NORMAL:
    return;
  default:
    throw exception_info;
  }
}

RmqConsumer::~RmqConsumer() { Stop(); }

} // namespace fdqueue
