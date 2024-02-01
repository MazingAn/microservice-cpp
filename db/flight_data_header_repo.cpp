#include "flight_data_header_repo.h"
#include "base_repo.h"
#include "conncpp/Exception.hpp"
#include "conncpp/PreparedStatement.hpp"
#include "conncpp/ResultSet.hpp"
#include "conncpp/Statement.hpp"
#include "flight_data_header.h"
#include <iostream>
#include <memory>
#include <sstream>

namespace fddb {

FlightDataHeaderRepo::FlightDataHeaderRepo(const std::string db_url,
                                           const std::string uname,
                                           const std::string pwd)
    : BaseRepo(db_url, uname, pwd) {}

FlightDataHeaderRepo::~FlightDataHeaderRepo() {
  std::cout << "DeConstructure FlightDataHeaderRepo" << std::endl;
}

bool FlightDataHeaderRepo::CreateOne(fdmodels::FlightDataHeader header) {
  std::shared_ptr<sql::PreparedStatement> pstmnt(conn_->prepareStatement(
      "INSERT INTO FlightDataHeader(id, aircraft_number, fcd_type, "
      "aircraft_type, fly_start_time, fly_end_time, engine_start_time, "
      "engine_end_time) VALUES(?,?,?,?,?,?,?,?);"));
  try {
    pstmnt->setLong(1, header.id_);
    pstmnt->setString(2, header.aircraft_number_);
    pstmnt->setString(3, header.fcd_type_);
    pstmnt->setString(4, header.aircraft_type_);
    pstmnt->setLong(5, header.fly_start_time_);
    pstmnt->setLong(6, header.fly_end_time_);
    pstmnt->setLong(7, header.engine_start_time_);
    pstmnt->setLong(8, header.engine_end_time_);
    pstmnt->executeUpdate();
    return true;
  } catch (sql::SQLException &e) {
    std::cerr << "Create FlightDataHeader Error." << std::endl;
    std::cerr << e.getMessage() << std::endl;
    return false;
  }
}

bool FlightDataHeaderRepo::UpdateById(long id,
                                      fdmodels::FlightDataHeader newHeader) {
  std::shared_ptr<sql::PreparedStatement> pstmnt(conn_->prepareStatement(
      "UPDATE FlightDataHeader set aircraft_number=?, fcd_type=?, "
      "aircraft_type=?, fly_start_time=?, fly_end_time=?, engine_start_time=?, "
      "engine_end_time=? WHERE id=?"));
  try {
    pstmnt->setString(1, newHeader.aircraft_number_);
    pstmnt->setString(2, newHeader.fcd_type_);
    pstmnt->setString(3, newHeader.aircraft_type_);
    pstmnt->setLong(4, newHeader.fly_start_time_);
    pstmnt->setLong(5, newHeader.fly_end_time_);
    pstmnt->setLong(6, newHeader.engine_start_time_);
    pstmnt->setLong(7, newHeader.engine_end_time_);
    pstmnt->setLong(8, newHeader.id_);
    pstmnt->executeUpdate();
    return true;
  } catch (sql::SQLException &e) {
    std::cerr << "Update FlightDataHeader Error." << std::endl;
    std::cerr << e.getMessage() << std::endl;
    return false;
  }
}

bool FlightDataHeaderRepo::RemoveById(long id) {
  std::shared_ptr<sql::PreparedStatement> pstmnt(
      conn_->prepareStatement("DELETE FlightDataHeader WHERE id=?"));
  try {
    pstmnt->setLong(1, id);
    pstmnt->executeUpdate();
    return true;
  } catch (sql::SQLException &e) {
    std::cerr << "Delete FlightDataHeader By Id : " << id << " Error."
              << std::endl;
    std::cerr << e.getMessage() << std::endl;
    return false;
  }
}

fdmodels::FlightDataHeader FlightDataHeaderRepo::QueryById(long id) {
  std::shared_ptr<sql::Statement> stmnt(conn_->createStatement());
  try {
    std::stringstream ss;
    ss << "SELECT * FROM FlightDataHeader WHERE id=" << id;
    std::shared_ptr<sql::ResultSet> res(stmnt->executeQuery(ss.str()));
    fdmodels::FlightDataHeader header{};
    header.id_ = res->getLong("id");
    header.aircraft_number_ = res->getString("aircraft_number");
    header.aircraft_type_ = res->getString("aircraft_type");
    header.fcd_type_ = res->getString("fcd_type");
    header.fly_start_time_ = res->getLong("fly_start_time");
    header.fly_end_time_ = res->getLong("fly_end_time");
    header.engine_start_time_ = res->getLong("engine_start_time");
    header.engine_end_time_ = res->getLong("engine_end_time");
    return header;
  } catch (sql::SQLException &e) {
    std::cerr << "Query FlightDataHeader By Id : " << id << " Error."
              << std::endl;
    std::cerr << e.getMessage() << std::endl;
    return fdmodels::FlightDataHeader{};
  }
}

} // namespace fddb
