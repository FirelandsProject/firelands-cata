CREATE USER 'firelands'@'localhost' IDENTIFIED BY 'firelands' WITH MAX_QUERIES_PER_HOUR 0 MAX_CONNECTIONS_PER_HOUR 0 MAX_UPDATES_PER_HOUR 0;

CREATE DATABASE `firelands_world` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

CREATE DATABASE `firelands_characters` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

CREATE DATABASE `firelands_auth` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

CREATE DATABASE `firelands_hotfixes` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

GRANT ALL PRIVILEGES ON `firelands_world` . * TO 'firelands'@'localhost' WITH GRANT OPTION;

GRANT ALL PRIVILEGES ON `firelands_characters` . * TO 'firelands'@'localhost' WITH GRANT OPTION;

GRANT ALL PRIVILEGES ON `firelands_auth` . * TO 'firelands'@'localhost' WITH GRANT OPTION;

GRANT ALL PRIVILEGES ON `firelands_hotfixes` . * TO 'firelands'@'localhost' WITH GRANT OPTION;
