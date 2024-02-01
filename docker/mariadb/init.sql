CREATE DATABASE IF NOT EXISTS fdpp; 
CREATE TABLE IF NOT EXISTS `fdpp.flightdataheader` (
  `id` int(11) NOT NULL,
  `aircraft_number` varchar(32) DEFAULT NULL,
  `aircraft_type` varchar(32) DEFAULT NULL,
  `fcd_type` varchar(32) DEFAULT NULL,
  `fly_start_time` mediumtext DEFAULT NULL,
  `fly_end_time` mediumtext DEFAULT NULL,
  `engine_start_time` mediumtext DEFAULT NULL,
  `engine_end_time` mediumtext DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;
