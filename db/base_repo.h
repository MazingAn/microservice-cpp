#ifndef FDPP_DB_BASE_REPO_H
#define FDPP_DB_BASE_REPO_H

#include "conncpp/Connection.hpp"
#include "conncpp/Driver.hpp"
#include "conncpp/SQLString.hpp"
#include <memory>

namespace fddb {

class BaseRepo {

protected:
  sql::Driver *driver_;
  sql::SQLString db_url_;
  sql::Properties db_properties_;
  std::unique_ptr<sql::Connection> conn_;

public:
  BaseRepo(const std::string db_url, const std::string uname,
           const std::string pwd);
  virtual ~BaseRepo();
  void Connect();
};

} // namespace fddb

#endif // !FDPP_DB_BASE_REPO_H
