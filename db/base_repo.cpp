#include "base_repo.h"
#include "conncpp/SQLString.hpp"

namespace fddb {

BaseRepo::BaseRepo(const std::string db_url, const std::string uname,
                   const std::string pwd) {
  db_url_ = sql::SQLString(db_url);
  db_properties_["user"] = uname;
  db_properties_["password"] = pwd;
  driver_ = sql::mariadb::get_driver_instance();
}

void BaseRepo::Connect() {
  conn_ = std::unique_ptr<sql::Connection>(
      driver_->connect(db_url_, db_properties_));
}

BaseRepo::~BaseRepo() { conn_->close(); }

} // namespace fddb
