#ifndef FDPP_DB_FLIGHT_DATA_HEADER_REPO_H
#define FDPP_DB_FLIGHT_DATA_HEADER_REPO_H

#include "base_repo.h"
#include "flight_data_header.h"
#include <string>

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
};
} // namespace fddb
#endif // !FDPP_DB_FLIGHT_DATA_HEADER_REPO_H
