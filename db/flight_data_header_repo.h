#ifndef FDPP_DB_FLIGHT_DATA_HEADER_REPO_H
#define FDPP_DB_FLIGHT_DATA_HEADER_REPO_H

#include "base_repo.h"
#include "conncpp/ResultSet.hpp"
#include "flight_data_header.h"
#include <memory>
#include <string>
#include <vector>

namespace fddb {

class FlightDataHeaderRepo : public BaseRepo {

public:
  FlightDataHeaderRepo(const std::string db_url, const std::string uname,
                       const std::string pwd);
  ~FlightDataHeaderRepo();

  /* The CURD Methods */
  bool CreateOne(fdmodels::FlightDataHeader header);
  bool UpdateById(long id, fdmodels::FlightDataHeader newHeader);
  bool RemoveById(long id);
  fdmodels::FlightDataHeader QueryById(long id);
  std::vector<fdmodels::FlightDataHeader>
  QueryAndOrder(int page_index, int page_size, std::string order);

private:
  void SqlToModel(std::shared_ptr<sql::ResultSet> res,
                  fdmodels::FlightDataHeader &header);
};
} // namespace fddb
#endif // !FDPP_DB_FLIGHT_DATA_HEADER_REPO_H
