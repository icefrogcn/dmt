DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20191117185433');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20191117185433');
-- Add your query below.


ALTER TABLE `command`
	CHANGE COLUMN `flags` `flags` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0' AFTER `help`;


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
