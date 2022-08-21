/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `vehicle_seat_addon` (
  `SeatEntry` int unsigned NOT NULL COMMENT 'VehicleSeatEntry.dbc identifier',
  `SeatOffsetX` float DEFAULT '0',
  `SeatOffsetY` float DEFAULT '0',
  `SeatOffsetZ` float DEFAULT '0',
  `SeatOffsetO` float DEFAULT '0' COMMENT 'Seat Orientation override value',
  `ExitParamX` float DEFAULT '0',
  `ExitParamY` float DEFAULT '0',
  `ExitParamZ` float DEFAULT '0',
  `ExitParamO` float DEFAULT '0',
  `ExitParamValue` tinyint(1) DEFAULT '0',
  PRIMARY KEY (`SeatEntry`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DELETE FROM `vehicle_seat_addon`;
/*!40000 ALTER TABLE `vehicle_seat_addon` DISABLE KEYS */;
INSERT INTO `vehicle_seat_addon` (`SeatEntry`, `SeatOffsetX`, `SeatOffsetY`, `SeatOffsetZ`, `SeatOffsetO`, `ExitParamX`, `ExitParamY`, `ExitParamZ`, `ExitParamO`, `ExitParamValue`) VALUES
	(2764, 0, 0, 0, 0, -2, 2, 0, 0, 1),
	(2765, 0, 0, 0, 0, -2, -2, 0, 0, 1),
	(2767, 0, 0, 0, 0, -2, 2, 0, 0, 1),
	(2768, 0, 0, 0, 0, -2, -2, 0, 0, 1),
	(7909, 0, 0, 0, 0, -311.465, -48.5972, 212.807, 1.06465, 2),
	(7936, 0, 0, 0, 0, -311.465, -48.5972, 212.807, 1.06465, 2),
	(8030, 0, 0, 0, 0, -9618.69, -1030.11, 41.6842, 4.84749, 2),
	(8104, 0, 0, 0, 0, -311.465, -48.5972, 212.807, 1.06465, 2),
	(8372, 0, 0, 0, 3.14159, 0, 0, 0, 0, 0),
	(8426, 0, 0, 0, 3.14159, 0, 0, 0, 0, 0),
	(8450, 0, 0, 0, 3.14159, 0, 0, 0, 0, 0),
	(8451, 0, 0, 0, 3.14159, 0, 0, 0, 0, 0),
	(8453, 0, 0, 0, 3.14159, 0, 0, 0, 0, 0),
	(10472, 0, 0, 0, 0, -11929.8, 12035.6, 35.458, 2.16421, 2),
	(10699, 263.089, 15.0095, 100.149, 0, 0, 0, 0, 0, 0);
/*!40000 ALTER TABLE `vehicle_seat_addon` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
