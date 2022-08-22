/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `creature_trainer` (
  `CreatureId` int unsigned NOT NULL,
  `TrainerId` int unsigned NOT NULL DEFAULT '0',
  `MenuId` int unsigned NOT NULL DEFAULT '0',
  `OptionIndex` int unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`CreatureId`,`MenuId`,`OptionIndex`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DELETE FROM `creature_trainer`;
/*!40000 ALTER TABLE `creature_trainer` DISABLE KEYS */;
INSERT INTO `creature_trainer` (`CreatureId`, `TrainerId`, `MenuId`, `OptionIndex`) VALUES
	(198, 44, 4660, 0),
	(328, 135, 4661, 0),
	(331, 135, 4486, 0),
	(375, 127, 13921, 0),
	(376, 3, 4466, 0),
	(377, 3, 4666, 0),
	(459, 32, 1503, 0),
	(460, 32, 4681, 0),
	(461, 154, 4503, 0),
	(514, 58, 2744, 0),
	(812, 101, 7691, 0),
	(837, 127, 4679, 0),
	(895, 15, 4675, 0),
	(906, 154, 4667, 0),
	(908, 101, 0, 3),
	(911, 145, 4650, 0),
	(912, 145, 4684, 0),
	(913, 16, 4649, 0),
	(914, 16, 4475, 0),
	(915, 17, 4659, 0),
	(916, 17, 4676, 0),
	(917, 33, 381, 0),
	(918, 33, 4502, 0),
	(925, 168, 4663, 0),
	(926, 168, 4678, 0),
	(927, 164, 4664, 0),
	(928, 164, 4470, 0),
	(985, 16, 523, 0),
	(986, 124, 4104, 0),
	(987, 40, 4101, 0),
	(988, 154, 4642, 0),
	(1103, 163, 4261, 0),
	(1218, 101, 7691, 0),
	(1226, 3, 4680, 0),
	(1228, 135, 4463, 0),
	(1229, 16, 4683, 0),
	(1231, 40, 4007, 0),
	(1232, 164, 4677, 0),
	(1234, 33, 410, 0),
	(1241, 58, 2741, 0),
	(1292, 155, 648, 0),
	(1317, 131, 4161, 0),
	(1346, 163, 4353, 0),
	(1355, 136, 5853, 0),
	(1382, 136, 5854, 0),
	(1385, 56, 0, 3),
	(1386, 122, 4134, 0),
	(1404, 40, 4657, 0),
	(1411, 33, 4658, 0),
	(1430, 136, 5853, 0),
	(1458, 101, 7691, 0),
	(1470, 122, 4115, 0),
	(1473, 101, 0, 3),
	(1632, 56, 4172, 0),
	(1651, 10, 5665, 0),
	(1676, 407, 4145, 0),
	(1680, 10, 5665, 0),
	(1681, 49, 4361, 0),
	(1683, 10, 5665, 0),
	(1699, 136, 5853, 0),
	(1700, 10, 5665, 0),
	(1701, 49, 7690, 0),
	(1702, 407, 4135, 0),
	(1901, 16, 4569, 0),
	(2114, 133, 0, 3),
	(2119, 145, 4653, 0),
	(2122, 17, 85, 0),
	(2123, 127, 3645, 0),
	(2124, 44, 4654, 0),
	(2126, 32, 4655, 0),
	(2127, 154, 4656, 0),
	(2128, 135, 63, 0),
	(2129, 3, 3645, 0),
	(2130, 33, 0, 3),
	(2131, 16, 656, 0),
	(2132, 122, 0, 0),
	(2326, 107, 5855, 0),
	(2329, 107, 5855, 0),
	(2390, 101, 0, 3),
	(2391, 122, 4129, 0),
	(2399, 163, 4356, 0),
	(2485, 130, 4822, 0),
	(2489, 129, 4823, 0),
	(2492, 149, 4827, 0),
	(2627, 163, 4348, 0),
	(2798, 107, 5856, 0),
	(2834, 10, 5665, 0),
	(2836, 58, 2784, 0),
	(2837, 122, 4127, 0),
	(2856, 101, 0, 3),
	(2998, 58, 1017, 0),
	(3001, 49, 7690, 0),
	(3004, 163, 4351, 0),
	(3007, 56, 4242, 0),
	(3009, 122, 4128, 0),
	(3011, 62, 4165, 0),
	(3013, 101, 7691, 0),
	(3014, 101, 0, 0),
	(3026, 136, 5854, 0),
	(3028, 10, 5665, 0),
	(3033, 39, 3921, 0),
	(3034, 39, 4606, 0),
	(3036, 39, 4607, 0),
	(3038, 40, 4011, 0),
	(3039, 40, 4023, 0),
	(3040, 40, 4524, 0),
	(3041, 16, 4526, 0),
	(3042, 16, 4525, 0),
	(3043, 16, 4527, 0),
	(3044, 3, 4533, 0),
	(3045, 3, 4531, 0),
	(3046, 3, 4532, 0),
	(3047, 135, 4534, 0),
	(3048, 135, 4536, 0),
	(3049, 135, 4535, 0),
	(3059, 145, 4645, 0),
	(3060, 50, 4644, 0),
	(3061, 15, 4647, 0),
	(3062, 134, 4103, 0),
	(3063, 16, 655, 0),
	(3064, 39, 3926, 0),
	(3065, 40, 4012, 0),
	(3067, 136, 5854, 0),
	(3069, 56, 4185, 0),
	(3087, 136, 5853, 0),
	(3136, 58, 2781, 0),
	(3137, 49, 7690, 0),
	(3153, 145, 523, 0),
	(3155, 17, 141, 0),
	(3156, 32, 4643, 0),
	(3157, 134, 4652, 0),
	(3169, 16, 523, 0),
	(3170, 33, 141, 0),
	(3171, 40, 4017, 0),
	(3172, 154, 4641, 0),
	(3173, 124, 4104, 0),
	(3174, 58, 2746, 0),
	(3175, 49, 0, 3),
	(3179, 10, 5665, 0),
	(3181, 107, 5855, 0),
	(3184, 122, 0, 0),
	(3185, 133, 0, 0),
	(3290, 407, 0, 3),
	(3324, 154, 4603, 0),
	(3325, 154, 4604, 0),
	(3326, 154, 2384, 0),
	(3327, 33, 4513, 0),
	(3328, 33, 4512, 0),
	(3332, 10, 4741, 0),
	(3344, 124, 4516, 0),
	(3345, 131, 4168, 0),
	(3347, 122, 4126, 0),
	(3352, 40, 4010, 0),
	(3353, 16, 4509, 0),
	(3354, 16, 4511, 0),
	(3355, 58, 1012, 0),
	(3357, 49, 7690, 0),
	(3363, 163, 4347, 0),
	(3365, 56, 4209, 0),
	(3399, 136, 4747, 0),
	(3403, 124, 4515, 0),
	(3404, 101, 7691, 0),
	(3478, 58, 2783, 0),
	(3484, 163, 4270, 0),
	(3494, 407, 4140, 0),
	(3523, 163, 0, 3),
	(3549, 56, 4184, 0),
	(3555, 49, 0, 3),
	(3557, 58, 0, 3),
	(3593, 145, 4696, 0),
	(3594, 17, 4690, 0),
	(3595, 127, 4692, 0),
	(3596, 15, 4695, 0),
	(3597, 50, 4688, 0),
	(3598, 16, 4697, 0),
	(3599, 33, 436, 0),
	(3600, 3, 4691, 0),
	(3601, 40, 4009, 0),
	(3602, 39, 3923, 0),
	(3603, 122, 0, 0),
	(3604, 101, 0, 0),
	(3605, 56, 4174, 0),
	(3606, 62, 4156, 0),
	(3607, 10, 5665, 0),
	(3690, 46, 0, 0),
	(3703, 56, 4206, 0),
	(3704, 163, 4350, 0),
	(3706, 3, 3644, 0),
	(3963, 40, 4092, 0),
	(3964, 122, 0, 3),
	(3965, 101, 0, 3),
	(3967, 56, 4211, 0),
	(4087, 16, 4581, 0),
	(4089, 16, 4578, 0),
	(4090, 3, 4574, 0),
	(4091, 3, 4573, 0),
	(4092, 3, 4572, 0),
	(4138, 40, 4621, 0),
	(4146, 40, 4008, 0),
	(4156, 10, 5665, 0),
	(4159, 163, 4349, 0),
	(4160, 122, 4131, 0),
	(4163, 33, 4576, 0),
	(4165, 130, 4821, 0),
	(4187, 37, 0, 0),
	(4204, 101, 7691, 0),
	(4205, 40, 4693, 0),
	(4210, 136, 5853, 0),
	(4211, 107, 5855, 0),
	(4212, 56, 4241, 0),
	(4213, 62, 4163, 0),
	(4214, 33, 4577, 0),
	(4215, 33, 4575, 0),
	(4217, 39, 1403, 0),
	(4218, 39, 3924, 0),
	(4219, 39, 4571, 0),
	(4254, 49, 7690, 0),
	(4258, 58, 0, 0),
	(4552, 136, 5854, 0),
	(4563, 154, 0, 3),
	(4564, 154, 0, 3),
	(4565, 154, 4610, 0),
	(4566, 135, 4539, 0),
	(4567, 135, 0, 3),
	(4568, 135, 0, 3),
	(4573, 10, 12887, 0),
	(4576, 163, 0, 3),
	(4578, 163, 0, 3),
	(4582, 33, 0, 3),
	(4583, 33, 0, 3),
	(4584, 33, 0, 3),
	(4588, 56, 0, 3),
	(4591, 107, 0, 3),
	(4593, 16, 0, 3),
	(4594, 16, 0, 3),
	(4595, 16, 0, 3),
	(4596, 58, 0, 3),
	(4598, 49, 0, 3),
	(4606, 3, 0, 3),
	(4607, 3, 0, 3),
	(4608, 3, 0, 3),
	(4611, 122, 4132, 0),
	(4614, 101, 7691, 0),
	(4616, 62, 4166, 0),
	(4732, 46, 0, 0),
	(4752, 46, 0, 0),
	(4753, 46, 0, 3),
	(4772, 46, 0, 0),
	(4773, 46, 0, 0),
	(4888, 58, 0, 3),
	(4892, 40, 0, 3),
	(4894, 136, 12847, 0),
	(4898, 101, 0, 0),
	(4900, 122, 4122, 0),
	(4941, 407, 12846, 0),
	(5113, 16, 4570, 0),
	(5114, 16, 4568, 0),
	(5115, 40, 4549, 0),
	(5116, 40, 4550, 0),
	(5117, 40, 4551, 0),
	(5127, 56, 4205, 0),
	(5137, 101, 7691, 0),
	(5141, 3, 4559, 0),
	(5142, 3, 4558, 0),
	(5143, 3, 0, 3),
	(5144, 135, 4463, 0),
	(5145, 135, 4463, 0),
	(5146, 135, 4555, 0),
	(5147, 164, 4557, 0),
	(5148, 164, 4556, 0),
	(5149, 164, 2304, 0),
	(5150, 107, 4762, 0),
	(5153, 163, 4345, 0),
	(5157, 62, 4160, 0),
	(5159, 136, 4748, 0),
	(5161, 10, 4742, 0),
	(5164, 27, 0, 0),
	(5165, 33, 411, 0),
	(5166, 33, 0, 3),
	(5167, 33, 4561, 0),
	(5171, 154, 4567, 0),
	(5172, 154, 2381, 0),
	(5173, 154, 4566, 0),
	(5174, 407, 4150, 0),
	(5177, 122, 4123, 0),
	(5388, 29, 12848, 0),
	(5392, 49, 7690, 0),
	(5479, 16, 4482, 0),
	(5480, 16, 4481, 0),
	(5482, 136, 646, 0),
	(5484, 3, 4468, 0),
	(5489, 3, 4467, 0),
	(5491, 164, 4470, 0),
	(5492, 164, 4470, 0),
	(5493, 10, 645, 0),
	(5495, 154, 4505, 0),
	(5496, 154, 4504, 0),
	(5497, 135, 4463, 0),
	(5498, 135, 4484, 0),
	(5499, 122, 4201, 0),
	(5501, 40, 4694, 0),
	(5504, 39, 4508, 0),
	(5511, 58, 581, 0),
	(5513, 49, 660, 0),
	(5515, 40, 4474, 0),
	(5516, 40, 4473, 0),
	(5517, 40, 4472, 0),
	(5518, 407, 4146, 0),
	(5564, 143, 4203, 0),
	(5566, 101, 643, 0),
	(5612, 154, 4682, 0),
	(5690, 10, 5665, 0),
	(5695, 62, 4202, 0),
	(5759, 107, 5856, 0),
	(5880, 135, 64, 0),
	(5938, 10, 5665, 0),
	(5939, 107, 5856, 0),
	(5941, 10, 5665, 0),
	(5943, 107, 5856, 0),
	(5957, 149, 4825, 0),
	(6094, 107, 5855, 0),
	(6286, 136, 2021, 0),
	(6287, 155, 0, 0),
	(6288, 83, 0, 3),
	(6289, 155, 0, 0),
	(6290, 155, 0, 0),
	(6291, 155, 0, 0),
	(6292, 155, 0, 0),
	(6295, 83, 0, 3),
	(6306, 83, 0, 3),
	(6387, 83, 0, 3),
	(7087, 83, 0, 3),
	(7088, 155, 0, 0),
	(7089, 155, 0, 0),
	(7230, 27, 0, 3),
	(7231, 27, 0, 3),
	(7232, 58, 0, 3),
	(7311, 135, 11933, 0),
	(7312, 135, 4553, 0),
	(7315, 16, 4579, 0),
	(7406, 407, 0, 3),
	(7869, 56, 0, 3),
	(7871, 56, 0, 0),
	(7944, 407, 1468, 0),
	(7946, 10, 0, 3),
	(7948, 122, 4133, 0),
	(7949, 62, 4164, 0),
	(7953, 46, 0, 0),
	(7954, 46, 0, 0),
	(8126, 407, 0, 3),
	(8128, 49, 0, 0),
	(8140, 164, 4662, 0),
	(8141, 16, 4091, 0),
	(8142, 39, 4646, 0),
	(8144, 83, 0, 3),
	(8146, 101, 7691, 0),
	(8153, 56, 0, 3),
	(8306, 136, 5854, 0),
	(8308, 40, 4092, 0),
	(8664, 164, 11767, 0),
	(8736, 407, 4152, 0),
	(8738, 407, 0, 3),
	(9584, 67, 0, 0),
	(10578, 133, 0, 0),
	(10930, 40, 4674, 0),
	(11017, 407, 4151, 0),
	(11025, 407, 4142, 0),
	(11031, 407, 0, 3),
	(11037, 407, 4138, 0),
	(11052, 163, 4355, 0),
	(11072, 62, 0, 3),
	(11073, 62, 0, 3),
	(11074, 62, 0, 3),
	(11097, 56, 4243, 0),
	(11098, 56, 0, 3),
	(11146, 27, 0, 0),
	(11177, 27, 0, 0),
	(11178, 27, 0, 3),
	(11397, 3, 3643, 0),
	(11401, 3, 4801, 0),
	(11406, 3, 3642, 0),
	(12025, 101, 0, 3),
	(12030, 83, 0, 3),
	(12032, 10, 5665, 0),
	(12042, 39, 4687, 0),
	(12939, 107, 5382, 0),
	(12961, 10, 5665, 0),
	(13283, 33, 5061, 0),
	(13417, 124, 5123, 0),
	(13476, 39, 0, 3),
	(14740, 10, 6087, 1),
	(15279, 44, 0, 3),
	(15280, 168, 0, 3),
	(15283, 32, 0, 3),
	(15284, 127, 0, 3),
	(15285, 17, 6650, 0),
	(15400, 58, 7256, 0),
	(15501, 29, 8376, 0),
	(15513, 15, 6652, 0),
	(16160, 62, 7524, 1),
	(16161, 122, 7524, 1),
	(16253, 136, 7171, 0),
	(16266, 154, 7566, 0),
	(16269, 135, 6648, 0),
	(16270, 40, 0, 3),
	(16272, 107, 5856, 0),
	(16273, 155, 0, 0),
	(16275, 164, 6647, 0),
	(16276, 3, 7438, 0),
	(16277, 136, 5854, 0),
	(16278, 143, 0, 3),
	(16279, 33, 6650, 0),
	(16280, 46, 8275, 0),
	(16366, 163, 7524, 1),
	(16367, 101, 7524, 1),
	(16499, 15, 7262, 0),
	(16500, 44, 7264, 0),
	(16501, 168, 7260, 0),
	(16502, 127, 7349, 0),
	(16503, 145, 7263, 0),
	(16583, 58, 0, 3),
	(16588, 122, 7810, 0),
	(16633, 62, 8731, 0),
	(16640, 163, 8658, 0),
	(16642, 122, 8733, 0),
	(16644, 101, 7691, 0),
	(16646, 154, 7566, 0),
	(16647, 154, 7437, 0),
	(16648, 154, 7566, 0),
	(16651, 135, 6648, 0),
	(16652, 135, 6648, 0),
	(16653, 135, 6648, 0),
	(16654, 149, 4824, 0),
	(16655, 39, 4605, 0),
	(16658, 3, 6649, 0),
	(16659, 3, 6649, 0),
	(16660, 3, 6649, 0),
	(16661, 124, 4105, 0),
	(16662, 107, 5855, 0),
	(16663, 49, 7690, 0),
	(16667, 407, 8656, 0),
	(16669, 58, 7494, 0),
	(16672, 40, 6652, 0),
	(16673, 40, 6652, 0),
	(16674, 40, 6652, 0),
	(16676, 136, 5854, 0),
	(16679, 164, 6647, 0),
	(16680, 164, 6647, 0),
	(16681, 164, 6647, 0),
	(16684, 33, 6650, 0),
	(16685, 33, 6650, 0),
	(16686, 33, 6650, 0),
	(16688, 56, 8732, 0),
	(16692, 83, 7842, 0),
	(16719, 136, 5853, 0),
	(16721, 39, 7567, 0),
	(16723, 122, 0, 3),
	(16724, 58, 0, 3),
	(16725, 62, 8866, 0),
	(16726, 407, 8867, 0),
	(16728, 56, 0, 3),
	(16729, 163, 8868, 0),
	(16731, 107, 5855, 0),
	(16736, 101, 7691, 0),
	(16738, 40, 7262, 0),
	(16749, 135, 7264, 0),
	(16752, 49, 7690, 0),
	(16755, 130, 4824, 0),
	(16756, 3, 7265, 0),
	(16761, 164, 7260, 0),
	(16763, 83, 7842, 0),
	(16771, 16, 7263, 0),
	(16774, 10, 5665, 0),
	(16780, 10, 5665, 0),
	(16823, 58, 7826, 0),
	(17089, 134, 7522, 0),
	(17101, 10, 7361, 0),
	(17110, 40, 7368, 0),
	(17120, 16, 7263, 0),
	(17121, 164, 7260, 0),
	(17122, 40, 7262, 0),
	(17204, 124, 7377, 0),
	(17212, 124, 7467, 0),
	(17214, 107, 7380, 0),
	(17215, 122, 7384, 0),
	(17219, 124, 7357, 0),
	(17222, 407, 7383, 0),
	(17245, 58, 7389, 0),
	(17246, 136, 7388, 0),
	(17424, 107, 7455, 0),
	(17434, 101, 7459, 0),
	(17441, 83, 7429, 0),
	(17442, 56, 7430, 0),
	(17480, 16, 7263, 0),
	(17481, 135, 7264, 0),
	(17482, 3, 7265, 0),
	(17483, 164, 7260, 0),
	(17487, 163, 8519, 0),
	(17488, 49, 7690, 0),
	(17504, 16, 7263, 0),
	(17505, 40, 7262, 0),
	(17509, 164, 7260, 0),
	(17510, 3, 7265, 0),
	(17511, 3, 7265, 0),
	(17513, 135, 7264, 0),
	(17514, 135, 7264, 0),
	(17519, 124, 7357, 0),
	(17520, 124, 7357, 0),
	(17634, 407, 0, 3),
	(17637, 407, 0, 3),
	(17983, 133, 0, 0),
	(18018, 10, 7609, 1),
	(18747, 49, 7690, 0),
	(18748, 101, 7691, 0),
	(18749, 163, 7817, 0),
	(18751, 29, 8646, 0),
	(18752, 407, 0, 3),
	(18753, 62, 7818, 0),
	(18754, 56, 7816, 0),
	(18755, 83, 7842, 0),
	(18771, 56, 7816, 0),
	(18772, 163, 7818, 0),
	(18773, 62, 7818, 0),
	(18774, 29, 7818, 0),
	(18775, 407, 0, 3),
	(18776, 101, 7691, 0),
	(18777, 83, 7842, 0),
	(18779, 49, 7690, 0),
	(18802, 122, 7818, 0),
	(18911, 10, 10437, 0),
	(18987, 136, 7818, 0),
	(18988, 136, 7818, 0),
	(18990, 159, 0, 3),
	(18991, 159, 0, 3),
	(18993, 136, 7879, 0),
	(19052, 122, 8540, 0),
	(19063, 29, 7815, 0),
	(19180, 83, 7818, 0),
	(19184, 107, 0, 3),
	(19185, 136, 8460, 0),
	(19187, 56, 7816, 0),
	(19251, 62, 0, 3),
	(19252, 62, 7818, 0),
	(19340, 148, 8433, 0),
	(19341, 58, 0, 3),
	(19369, 136, 0, 3),
	(19478, 107, 5856, 0),
	(19539, 29, 8646, 0),
	(19540, 62, 7818, 0),
	(19576, 407, 7818, 0),
	(19775, 29, 8380, 0),
	(19778, 29, 8382, 0),
	(20124, 58, 0, 3),
	(20125, 58, 0, 3),
	(20406, 164, 8111, 0),
	(20407, 124, 8110, 0),
	(20791, 148, 8268, 0),
	(20914, 46, 0, 3),
	(21087, 143, 0, 0),
	(21209, 58, 0, 3),
	(22477, 107, 0, 3),
	(23103, 135, 0, 3),
	(23127, 124, 7357, 0),
	(23128, 164, 6647, 0),
	(23534, 154, 1522, 0),
	(23566, 33, 0, 3),
	(23734, 107, 8802, 0),
	(23896, 10, 8826, 0),
	(24868, 407, 0, 3),
	(25099, 407, 9084, 0),
	(25277, 407, 0, 3),
	(26564, 58, 9459, 0),
	(26903, 122, 0, 3),
	(26904, 58, 0, 3),
	(26905, 136, 9985, 0),
	(26906, 62, 0, 3),
	(26907, 407, 0, 3),
	(26909, 10, 0, 3),
	(26910, 101, 0, 3),
	(26911, 56, 0, 3),
	(26912, 49, 0, 3),
	(26913, 83, 0, 3),
	(26914, 163, 10116, 0),
	(26915, 29, 9894, 0),
	(26916, 63, 9879, 0),
	(26951, 122, 0, 3),
	(26952, 58, 0, 3),
	(26953, 136, 9987, 0),
	(26954, 62, 0, 3),
	(26955, 407, 0, 0),
	(26956, 107, 0, 3),
	(26957, 10, 0, 3),
	(26958, 101, 0, 3),
	(26959, 63, 9879, 0),
	(26960, 29, 9895, 0),
	(26961, 56, 0, 0),
	(26962, 49, 0, 3),
	(26963, 90, 0, 0),
	(26964, 163, 10117, 0),
	(26969, 163, 10115, 0),
	(26972, 136, 9988, 0),
	(26974, 101, 0, 3),
	(26975, 122, 0, 3),
	(26976, 49, 0, 3),
	(26977, 63, 9879, 0),
	(26980, 62, 0, 3),
	(26981, 27, 0, 0),
	(26982, 29, 9893, 0),
	(26986, 83, 0, 3),
	(26987, 122, 0, 3),
	(26988, 58, 0, 3),
	(26989, 136, 9986, 0),
	(26990, 62, 0, 3),
	(26991, 407, 0, 3),
	(26992, 160, 0, 0),
	(26993, 10, 0, 3),
	(26994, 101, 0, 3),
	(26995, 63, 9879, 0),
	(26996, 56, 0, 3),
	(26997, 29, 9892, 0),
	(26998, 56, 0, 3),
	(26999, 91, 0, 0),
	(27000, 83, 0, 3),
	(27001, 163, 10114, 0),
	(27023, 122, 0, 3),
	(27029, 122, 0, 3),
	(27034, 58, 0, 3),
	(27703, 144, 9581, 0),
	(27704, 135, 9580, 0),
	(27705, 149, 9578, 0),
	(28471, 55, 9691, 0),
	(28472, 55, 9692, 0),
	(28474, 55, 9693, 0),
	(28693, 62, 0, 0),
	(28694, 27, 0, 0),
	(28696, 90, 0, 0),
	(28697, 407, 0, 0),
	(28698, 91, 0, 0),
	(28699, 77, 10118, 0),
	(28700, 56, 0, 0),
	(28701, 29, 9873, 0),
	(28702, 63, 0, 0),
	(28703, 122, 10627, 0),
	(28704, 89, 0, 0),
	(28705, 136, 9772, 0),
	(28706, 160, 0, 0),
	(28742, 10, 9833, 0),
	(28956, 135, 9990, 0),
	(28958, 135, 9990, 0),
	(29156, 148, 9777, 0),
	(29194, 55, 9792, 0),
	(29195, 55, 9793, 0),
	(29196, 55, 9794, 0),
	(29233, 107, 0, 3),
	(29505, 27, 0, 0),
	(29506, 27, 0, 0),
	(29507, 56, 0, 0),
	(29508, 56, 0, 3),
	(29509, 56, 0, 3),
	(29513, 405, 0, 0),
	(29514, 406, 0, 0),
	(29631, 136, 9831, 0),
	(29924, 27, 0, 0),
	(30706, 6, 0, 0),
	(30709, 6, 0, 0),
	(30710, 63, 0, 3),
	(30711, 63, 0, 3),
	(30713, 6, 0, 0),
	(30715, 6, 0, 3),
	(30716, 63, 0, 3),
	(30717, 6, 0, 0),
	(30721, 63, 0, 3),
	(30722, 123, 0, 0),
	(31084, 55, 10027, 0),
	(31238, 137, 10723, 0),
	(32474, 31, 0, 0),
	(33580, 163, 0, 3),
	(33581, 56, 0, 3),
	(33583, 62, 0, 3),
	(33586, 407, 0, 3),
	(33587, 136, 0, 3),
	(33588, 122, 0, 3),
	(33589, 160, 0, 0),
	(33590, 29, 0, 3),
	(33591, 58, 0, 3),
	(33608, 122, 0, 0),
	(33609, 34, 0, 0),
	(33610, 62, 0, 0),
	(33611, 407, 0, 0),
	(33612, 143, 0, 0),
	(33613, 42, 0, 0),
	(33614, 150, 0, 0),
	(33615, 123, 0, 0),
	(33616, 374, 0, 0),
	(33617, 82, 0, 0),
	(33618, 83, 0, 0),
	(33619, 136, 0, 0),
	(33621, 160, 0, 0),
	(33623, 31, 0, 0),
	(33630, 122, 10359, 0),
	(33631, 58, 10362, 0),
	(33633, 62, 10365, 0),
	(33634, 407, 0, 3),
	(33635, 56, 10361, 0),
	(33636, 163, 10364, 0),
	(33637, 29, 8646, 0),
	(33638, 63, 9879, 0),
	(33639, 101, 10350, 0),
	(33640, 49, 10351, 0),
	(33641, 83, 10360, 0),
	(33674, 122, 10359, 0),
	(33675, 58, 10362, 0),
	(33676, 62, 10365, 0),
	(33677, 407, 0, 3),
	(33678, 101, 10350, 0),
	(33679, 63, 9879, 0),
	(33680, 29, 8646, 0),
	(33681, 56, 10361, 0),
	(33682, 49, 10351, 0),
	(33683, 83, 10360, 0),
	(33684, 163, 10364, 0),
	(33996, 101, 10408, 1),
	(34673, 15, 0, 3),
	(34689, 44, 10683, 0),
	(34692, 127, 10685, 0),
	(34693, 17, 0, 3),
	(34695, 134, 10684, 0),
	(34696, 32, 10681, 0),
	(34697, 145, 10821, 0),
	(34708, 136, 10569, 0),
	(34713, 136, 10569, 0),
	(34785, 136, 0, 3),
	(34786, 136, 10569, 0),
	(35100, 386, 0, 0),
	(35133, 386, 0, 0),
	(35135, 386, 0, 0),
	(35281, 164, 7260, 0),
	(35758, 40, 0, 3),
	(35778, 154, 10550, 0),
	(35780, 135, 0, 3),
	(35786, 124, 10552, 0),
	(35805, 3, 0, 3),
	(35806, 33, 0, 3),
	(35807, 16, 10555, 0),
	(35839, 145, 10694, 0),
	(35869, 32, 0, 3),
	(35870, 127, 10700, 0),
	(35871, 17, 0, 3),
	(35872, 44, 10698, 0),
	(35873, 50, 10696, 0),
	(35874, 15, 0, 3),
	(36518, 40, 0, 3),
	(36519, 154, 10815, 0),
	(36520, 135, 0, 3),
	(36521, 124, 10817, 0),
	(36523, 3, 0, 3),
	(36524, 33, 0, 3),
	(36525, 16, 10555, 0),
	(36615, 107, 10826, 0),
	(36628, 39, 10834, 0),
	(36629, 40, 10835, 0),
	(36630, 33, 0, 3),
	(36631, 135, 10837, 0),
	(36632, 3, 10838, 0),
	(36651, 16, 10836, 0),
	(36652, 154, 0, 3),
	(37072, 58, 0, 0),
	(37115, 134, 0, 3),
	(37121, 44, 0, 3),
	(37724, 127, 11766, 0),
	(37737, 168, 11767, 0),
	(38037, 145, 10977, 0),
	(38122, 40, 0, 3),
	(38242, 134, 0, 3),
	(38243, 50, 10984, 0),
	(38244, 17, 0, 3),
	(38245, 127, 10986, 0),
	(38246, 44, 10987, 0),
	(38247, 15, 10988, 0),
	(38465, 135, 10837, 0),
	(38466, 3, 0, 3),
	(38467, 40, 0, 3),
	(38513, 154, 12576, 0),
	(38514, 135, 0, 3),
	(38515, 124, 0, 3),
	(38516, 3, 0, 3),
	(38517, 33, 0, 3),
	(38518, 16, 0, 3),
	(38793, 16, 10836, 0),
	(38794, 135, 10837, 0),
	(38795, 3, 10838, 0),
	(38796, 33, 0, 3),
	(38797, 154, 0, 3),
	(38798, 40, 10835, 0),
	(38799, 39, 10834, 0),
	(38911, 15, 11109, 0),
	(39100, 40, 11154, 0),
	(39116, 40, 0, 3),
	(39206, 44, 4651, 0),
	(39214, 15, 0, 3),
	(39718, 373, 11821, 0),
	(42323, 127, 0, 3),
	(42324, 145, 0, 3),
	(42331, 44, 0, 3),
	(42366, 17, 0, 3),
	(42618, 32, 0, 3),
	(43001, 164, 11767, 0),
	(43004, 3, 11766, 0),
	(43005, 135, 12606, 0),
	(43006, 44, 0, 3),
	(43009, 16, 14199, 0),
	(43010, 145, 11793, 0),
	(43011, 40, 11817, 0),
	(43012, 16, 11793, 0),
	(43013, 164, 11767, 0),
	(43015, 3, 11766, 0),
	(43277, 40, 11817, 0),
	(43278, 15, 14200, 0),
	(43428, 157, 8519, 0),
	(43429, 58, 8521, 0),
	(43431, 49, 7690, 0),
	(43455, 32, 0, 3),
	(43464, 124, 12529, 0),
	(43693, 386, 0, 0),
	(43769, 386, 0, 0),
	(43795, 164, 11767, 0),
	(43796, 3, 11766, 0),
	(43870, 3, 11766, 0),
	(43881, 154, 12821, 0),
	(43883, 154, 12821, 0),
	(43892, 154, 12821, 0),
	(44128, 16, 14199, 0),
	(44129, 16, 14199, 0),
	(44238, 373, 11821, 0),
	(44247, 40, 11817, 0),
	(44249, 40, 11817, 0),
	(44380, 39, 11824, 0),
	(44393, 124, 12529, 0),
	(44394, 124, 12529, 0),
	(44395, 39, 11829, 0),
	(44396, 39, 11829, 0),
	(44455, 16, 10694, 0),
	(44459, 39, 10696, 0),
	(44461, 40, 0, 3),
	(44464, 33, 0, 3),
	(44465, 135, 10698, 0),
	(44468, 3, 10700, 0),
	(44469, 154, 0, 3),
	(44582, 2, 11861, 0),
	(44723, 16, 11875, 0),
	(44725, 164, 11767, 0),
	(44726, 39, 0, 3),
	(44735, 3, 11766, 0),
	(44740, 124, 11878, 0),
	(44743, 40, 11879, 0),
	(44781, 58, 8521, 0),
	(44782, 155, 0, 0),
	(44783, 163, 4351, 0),
	(44919, 386, 0, 0),
	(44975, 10, 12443, 0),
	(44978, 39, 11906, 0),
	(45019, 16, 11912, 0),
	(45023, 40, 11913, 0),
	(45029, 124, 4105, 0),
	(45095, 33, 12050, 0),
	(45137, 3, 4521, 0),
	(45138, 154, 11932, 0),
	(45139, 149, 0, 3),
	(45286, 388, 12188, 11),
	(45286, 389, 12189, 11),
	(45286, 390, 12190, 11),
	(45286, 122, 12191, 11),
	(45286, 80, 12192, 11),
	(45286, 51, 12193, 11),
	(45286, 102, 12195, 11),
	(45286, 63, 12196, 11),
	(45286, 48, 12197, 11),
	(45286, 103, 12198, 11),
	(45286, 117, 12199, 11),
	(45306, 3, 0, 3),
	(45337, 3, 6649, 0),
	(45339, 3, 4544, 0),
	(45347, 3, 12010, 0),
	(45540, 107, 0, 3),
	(45545, 407, 0, 0),
	(45548, 58, 0, 0),
	(45550, 75, 0, 0),
	(45559, 163, 4351, 0),
	(45709, 16, 12344, 0),
	(45713, 40, 12048, 0),
	(45714, 135, 0, 3),
	(45717, 33, 0, 3),
	(45718, 124, 12052, 0),
	(45720, 154, 0, 3),
	(46357, 49, 7690, 0),
	(46667, 16, 12151, 0),
	(46675, 29, 7815, 0),
	(46709, 75, 0, 0),
	(46716, 6, 0, 0),
	(46741, 101, 7691, 0),
	(46983, 40, 11817, 0),
	(47233, 33, 141, 0),
	(47246, 135, 12233, 0),
	(47247, 135, 12233, 0),
	(47248, 135, 12233, 0),
	(47253, 149, 12235, 0),
	(47346, 373, 11821, 0),
	(47382, 373, 11821, 0),
	(47384, 388, 12188, 11),
	(47384, 389, 12189, 11),
	(47384, 390, 12190, 11),
	(47384, 122, 12191, 11),
	(47384, 80, 12192, 11),
	(47384, 51, 12193, 11),
	(47384, 102, 12195, 11),
	(47384, 63, 12196, 11),
	(47384, 48, 12197, 11),
	(47384, 103, 12198, 11),
	(47384, 117, 12199, 11),
	(47396, 388, 12188, 11),
	(47396, 389, 12189, 11),
	(47396, 390, 12190, 11),
	(47396, 122, 12191, 11),
	(47396, 80, 12192, 11),
	(47396, 51, 12193, 11),
	(47396, 102, 12195, 11),
	(47396, 63, 12196, 11),
	(47396, 48, 12197, 11),
	(47396, 103, 12198, 11),
	(47396, 117, 12199, 11),
	(47400, 388, 12188, 11),
	(47400, 389, 12189, 11),
	(47400, 390, 12190, 11),
	(47400, 122, 12191, 11),
	(47400, 80, 12192, 11),
	(47400, 51, 12193, 11),
	(47400, 102, 12195, 11),
	(47400, 63, 12196, 11),
	(47400, 48, 12197, 11),
	(47400, 103, 12198, 11),
	(47400, 117, 12199, 11),
	(47405, 75, 0, 0),
	(47418, 388, 12188, 11),
	(47418, 389, 12189, 11),
	(47418, 390, 12190, 11),
	(47418, 122, 12191, 11),
	(47418, 80, 12192, 11),
	(47418, 51, 12193, 11),
	(47418, 102, 12195, 11),
	(47418, 63, 12196, 11),
	(47418, 48, 12197, 11),
	(47418, 103, 12198, 11),
	(47418, 117, 12199, 11),
	(47419, 388, 12188, 11),
	(47419, 389, 12189, 11),
	(47419, 390, 12190, 11),
	(47419, 122, 12191, 11),
	(47419, 80, 12192, 11),
	(47419, 51, 12193, 11),
	(47419, 102, 12195, 11),
	(47419, 63, 12196, 11),
	(47419, 48, 12197, 11),
	(47419, 103, 12198, 11),
	(47419, 117, 12199, 11),
	(47420, 388, 12188, 11),
	(47420, 389, 12189, 11),
	(47420, 390, 12190, 11),
	(47420, 122, 12191, 11),
	(47420, 80, 12192, 11),
	(47420, 51, 12193, 11),
	(47420, 102, 12195, 11),
	(47420, 63, 12196, 11),
	(47420, 48, 12197, 11),
	(47420, 103, 12198, 11),
	(47420, 117, 12199, 11),
	(47421, 388, 12188, 11),
	(47421, 389, 12189, 11),
	(47421, 390, 12190, 11),
	(47421, 122, 12191, 11),
	(47421, 80, 12192, 11),
	(47421, 51, 12193, 11),
	(47421, 102, 12195, 11),
	(47421, 63, 12196, 11),
	(47421, 48, 12197, 11),
	(47421, 103, 12198, 11),
	(47421, 117, 12199, 11),
	(47431, 388, 12188, 11),
	(47431, 389, 12189, 11),
	(47431, 390, 12190, 11),
	(47431, 122, 12191, 11),
	(47431, 80, 12192, 11),
	(47431, 51, 12193, 11),
	(47431, 102, 12195, 11),
	(47431, 63, 12196, 11),
	(47431, 48, 12197, 11),
	(47431, 103, 12198, 11),
	(47431, 117, 12199, 11),
	(47569, 373, 11821, 0),
	(47571, 373, 12410, 0),
	(47572, 373, 11821, 0),
	(47575, 373, 11821, 0),
	(47579, 373, 11821, 0),
	(47767, 40, 12341, 0),
	(47788, 40, 12341, 0),
	(48513, 46, 0, 0),
	(48612, 154, 0, 3),
	(48613, 135, 63, 0),
	(48614, 3, 0, 3),
	(48615, 33, 0, 3),
	(48616, 16, 656, 0),
	(48618, 40, 11154, 0),
	(48619, 388, 12188, 11),
	(48619, 389, 12189, 11),
	(48619, 390, 12190, 11),
	(48619, 122, 12191, 11),
	(48619, 80, 12192, 11),
	(48619, 51, 12193, 11),
	(48619, 102, 12195, 11),
	(48619, 63, 12196, 11),
	(48619, 48, 12197, 11),
	(48619, 103, 12198, 11),
	(48619, 117, 12199, 11),
	(49715, 3, 3645, 0),
	(49716, 135, 63, 0),
	(49718, 154, 0, 3),
	(49720, 16, 656, 0),
	(49736, 16, 0, 3),
	(49741, 164, 12516, 0),
	(49745, 33, 0, 3),
	(49749, 3, 4666, 0),
	(49760, 135, 12521, 0),
	(49769, 154, 12522, 0),
	(49781, 16, 12523, 0),
	(49782, 33, 0, 3),
	(49784, 3, 3642, 0),
	(49786, 135, 0, 3),
	(49791, 154, 0, 3),
	(49793, 164, 12527, 0),
	(49806, 40, 0, 3),
	(49808, 124, 12529, 0),
	(49870, 33, 0, 3),
	(49879, 107, 10826, 0),
	(49894, 40, 12048, 0),
	(49895, 154, 0, 3),
	(49896, 135, 0, 3),
	(49900, 124, 12052, 0),
	(49901, 3, 0, 3),
	(49902, 16, 0, 3),
	(49909, 33, 0, 3),
	(49923, 16, 0, 3),
	(49927, 40, 0, 3),
	(49939, 33, 0, 3),
	(49940, 3, 12537, 0),
	(49942, 39, 12539, 0),
	(49945, 154, 0, 3),
	(49946, 40, 0, 3),
	(49949, 33, 0, 3),
	(49950, 3, 0, 3),
	(49952, 135, 0, 3),
	(49954, 164, 0, 3),
	(49955, 16, 0, 3),
	(49957, 164, 7260, 0),
	(49958, 40, 12540, 0),
	(49959, 135, 7264, 0),
	(49961, 16, 7263, 0),
	(49962, 3, 7265, 0),
	(49963, 154, 12522, 0),
	(49964, 124, 7357, 0),
	(49966, 40, 7262, 0),
	(49968, 135, 4463, 0),
	(49997, 39, 11906, 0),
	(49998, 154, 11932, 0),
	(50001, 3, 3644, 0),
	(50002, 135, 11933, 0),
	(50004, 40, 11913, 0),
	(50006, 16, 11912, 0),
	(50007, 40, 0, 3),
	(50010, 135, 12918, 0),
	(50011, 124, 4105, 0),
	(50012, 164, 0, 3),
	(50013, 3, 12920, 0),
	(50015, 33, 12050, 0),
	(50016, 33, 0, 3),
	(50017, 154, 0, 3),
	(50018, 16, 0, 3),
	(50019, 124, 7357, 0),
	(50020, 40, 7262, 0),
	(50021, 135, 7264, 0),
	(50022, 124, 4104, 0),
	(50023, 164, 7260, 0),
	(50024, 3, 7265, 0),
	(50025, 16, 7263, 0),
	(50027, 33, 0, 3),
	(50028, 154, 0, 3),
	(50029, 135, 12233, 0),
	(50031, 3, 3644, 0),
	(50032, 40, 12341, 0),
	(50033, 16, 523, 0),
	(50034, 39, 11877, 0),
	(50035, 164, 11767, 0),
	(50127, 33, 0, 3),
	(50128, 154, 12746, 0),
	(50130, 124, 7357, 0),
	(50136, 39, 12539, 0),
	(50137, 39, 12927, 0),
	(50142, 154, 7566, 0),
	(50144, 40, 6652, 0),
	(50147, 33, 6650, 0),
	(50148, 3, 6649, 0),
	(50149, 16, 11793, 0),
	(50150, 164, 6647, 0),
	(50152, 39, 11877, 0),
	(50153, 124, 4104, 0),
	(50155, 16, 0, 3),
	(50156, 154, 12522, 0),
	(50157, 40, 0, 3),
	(50158, 33, 0, 3),
	(50160, 164, 12516, 0),
	(50163, 3, 12714, 0),
	(50171, 39, 12539, 0),
	(50174, 124, 7357, 0),
	(50247, 388, 12188, 11),
	(50247, 389, 12189, 11),
	(50247, 390, 12190, 11),
	(50247, 122, 12191, 11),
	(50247, 80, 12192, 11),
	(50247, 51, 12193, 11),
	(50247, 102, 12195, 11),
	(50247, 63, 12196, 11),
	(50247, 48, 12197, 11),
	(50247, 103, 12198, 11),
	(50247, 117, 12199, 11),
	(50497, 40, 11817, 0),
	(50498, 33, 0, 3),
	(50499, 135, 12716, 0),
	(50500, 16, 0, 3),
	(50501, 3, 12714, 0),
	(50502, 154, 0, 3),
	(50505, 39, 12539, 0),
	(50506, 39, 12539, 0),
	(50507, 39, 12539, 0),
	(50567, 136, 5853, 0),
	(50570, 10, 5665, 0),
	(50574, 107, 5855, 0),
	(50609, 40, 0, 3),
	(50690, 135, 12606, 0),
	(50714, 135, 0, 3),
	(50715, 135, 0, 3),
	(50716, 135, 12521, 0),
	(50717, 135, 0, 3),
	(50720, 135, 0, 3),
	(50723, 154, 0, 3),
	(50729, 154, 0, 3),
	(50732, 154, 0, 3),
	(51637, 124, 4103, 0),
	(51638, 124, 4530, 0),
	(51639, 124, 4529, 0),
	(51640, 124, 4528, 0),
	(51997, 373, 12725, 0),
	(51998, 33, 5061, 0),
	(52170, 91, 0, 0),
	(52292, 124, 7357, 0),
	(52317, 124, 4103, 0),
	(52319, 39, 11877, 0),
	(52335, 39, 12755, 0),
	(52586, 29, 0, 3),
	(52587, 29, 0, 3),
	(52636, 407, 8517, 0),
	(52640, 27, 8521, 0),
	(52642, 49, 7690, 0),
	(52645, 2, 7815, 0),
	(52651, 407, 13014, 0),
	(52657, 29, 7815, 0),
	(53403, 3, 0, 3),
	(53404, 154, 0, 3),
	(53405, 124, 12529, 0),
	(53407, 46, 0, 0),
	(53409, 49, 0, 3),
	(53410, 62, 12843, 0),
	(53415, 63, 12844, 0),
	(53421, 373, 12850, 0),
	(53436, 56, 12852, 0),
	(53437, 83, 0, 3),
	(54232, 136, 12838, 0),
	(55684, 58, 0, 3),
	(56068, 10, 5665, 0),
	(56796, 107, 657, 0);
/*!40000 ALTER TABLE `creature_trainer` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;