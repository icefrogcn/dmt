DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200528153754');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200528153754');
-- Add your query below.


-- Remove spawn spell from creatures.
DELETE FROM `creature_ai_scripts` WHERE `id` IN (21001, 51101, 57001, 60401, 94801, 127001, 165401, 179101, 179301, 179401, 179501, 179601, 184701, 191801, 197101, 197401, 447401, 447501, 1040501, 1040601, 1040701, 1058001, 1080101, 1083601, 1094301, 1107501);
DELETE FROM `creature_ai_events` WHERE `id` IN (21001, 51101, 57001, 60401, 94801, 127001, 165401, 179101, 179301, 179401, 179501, 179601, 184701, 191801, 197101, 197401, 447401, 447501, 1040501, 1040601, 1040701, 1058001, 1080101, 1083601, 1094301, 1107501);
UPDATE `creature_template` SET `ai_name`='' WHERE `entry` IN (210, 511, 570, 604, 1270, 1654, 1795, 1918, 1974, 4475, 10580);


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
