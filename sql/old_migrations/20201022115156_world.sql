DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20201022115156');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20201022115156');
-- Add your query below.


-- Waypoints for Soaring Razorbeak.
UPDATE `creature_template` SET `inhabit_type`=5 WHERE `entry`=8276;
UPDATE `creature` SET `movement_type`=2, `position_x`=1.323350, `position_y`=-2004.439941, `position_z`=255.783997 WHERE `guid`=92881;
INSERT INTO `creature_movement` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `waittime`, `wander_distance`, `script_id`) VALUES
(92881, 1, 1.323350, -2004.439941, 255.783997, 100.000000, 0, 0.000000, 0), -- spline 0/76
(92881, 2, 1.146700, -1992.199951, 256.144989, 100.000000, 0, 0.000000, 0), -- spline 1/76
(92881, 3, 5.552030, -1982.819946, 254.923004, 100.000000, 0, 0.000000, 0), -- spline 2/76
(92881, 4, 15.985100, -1973.699951, 241.533997, 100.000000, 0, 0.000000, 0), -- spline 3/76
(92881, 5, 34.329201, -1949.410034, 222.783997, 100.000000, 0, 0.000000, 0), -- spline 4/76
(92881, 6, 42.905998, -1945.030029, 210.089996, 100.000000, 0, 0.000000, 0), -- spline 5/76
(92881, 7, 55.245201, -1954.349976, 201.645004, 100.000000, 0, 0.000000, 0), -- spline 6/76
(92881, 8, 74.639503, -1952.479980, 186.173004, 100.000000, 0, 0.000000, 0), -- spline 7/76
(92881, 9, 96.289299, -1945.880005, 178.589996, 100.000000, 0, 0.000000, 0), -- spline 8/76
(92881, 10, 119.483002, -1949.760010, 175.673004, 100.000000, 0, 0.000000, 0), -- spline 9/76
(92881, 11, 140.910004, -1954.459961, 178.589996, 100.000000, 0, 0.000000, 0), -- spline 10/76
(92881, 12, 165.733002, -1953.979980, 181.145004, 100.000000, 0, 0.000000, 0), -- spline 11/76
(92881, 13, 176.141006, -1958.829956, 176.589996, 100.000000, 0, 0.000000, 0), -- spline 12/76
(92881, 14, 185.098999, -1969.939941, 178.589996, 100.000000, 0, 0.000000, 0), -- spline 13/76
(92881, 15, 193.347000, -1987.300049, 176.423004, 100.000000, 0, 0.000000, 0), -- spline 14/76
(92881, 16, 215.253006, -2009.619995, 180.423004, 100.000000, 0, 0.000000, 0), -- spline 15/76
(92881, 17, 232.587006, -2022.880005, 176.589996, 100.000000, 0, 0.000000, 0), -- spline 16/76
(92881, 18, 244.951996, -2033.459961, 176.311996, 100.000000, 0, 0.000000, 0), -- spline 17/76
(92881, 19, 256.037994, -2047.859985, 179.367004, 100.000000, 0, 0.000000, 0), -- spline 18/76
(92881, 20, 261.692993, -2065.340088, 178.589996, 100.000000, 0, 0.000000, 0), -- spline 19/76
(92881, 21, 272.279999, -2094.270020, 162.311996, 100.000000, 0, 0.000000, 0), -- spline 20/76
(92881, 22, 273.145996, -2106.719971, 146.423004, 100.000000, 0, 0.000000, 0), -- spline 21/76
(92881, 23, 264.774994, -2126.120117, 141.145004, 100.000000, 0, 0.000000, 0), -- spline 22/76
(92881, 24, 237.975006, -2146.010010, 140.617996, 100.000000, 0, 0.000000, 0), -- spline 23/76
(92881, 25, 224.380005, -2159.139893, 146.757004, 100.000000, 0, 0.000000, 0), -- spline 24/76
(92881, 26, 215.854004, -2187.320068, 142.283997, 100.000000, 0, 0.000000, 0), -- spline 25/76
(92881, 27, 211.498993, -2223.979980, 137.145996, 100.000000, 0, 0.000000, 0), -- spline 26/76
(92881, 28, 206.070999, -2247.770020, 131.395996, 100.000000, 0, 0.000000, 0), -- spline 27/76
(92881, 29, 193.518005, -2268.610107, 122.478996, 100.000000, 0, 0.000000, 0), -- spline 28/76
(92881, 30, 178.744995, -2285.540039, 128.257004, 100.000000, 0, 0.000000, 0), -- spline 29/76
(92881, 31, 191.548004, -2312.959961, 138.729004, 100.000000, 0, 0.000000, 0), -- spline 30/76
(92881, 32, 184.449005, -2339.290039, 152.895004, 100.000000, 0, 0.000000, 0), -- spline 31/76
(92881, 33, 157.412994, -2363.810059, 153.423004, 100.000000, 0, 0.000000, 0), -- spline 32/76
(92881, 34, 137.035995, -2370.969971, 154.839996, 100.000000, 0, 0.000000, 0), -- spline 33/76
(92881, 35, 111.068001, -2354.020020, 159.923004, 100.000000, 0, 0.000000, 0), -- spline 34/76
(92881, 36, 91.163498, -2316.629883, 167.007004, 100.000000, 0, 0.000000, 0), -- spline 35/76
(92881, 37, 66.269600, -2319.840088, 161.757004, 100.000000, 0, 0.000000, 0), -- spline 36/76
(92881, 38, 51.683201, -2351.020020, 155.339996, 100.000000, 0, 0.000000, 0), -- spline 37/76
(92881, 39, 46.885601, -2391.449951, 155.395004, 100.000000, 0, 0.000000, 0), -- spline 38/76
(92881, 40, 48.952000, -2429.260010, 167.007004, 100.000000, 0, 0.000000, 0), -- spline 39/76
(92881, 41, 60.984299, -2457.340088, 160.561996, 100.000000, 0, 0.000000, 0), -- spline 40/76
(92881, 42, 72.597298, -2484.929932, 167.007004, 100.000000, 0, 0.000000, 0), -- spline 41/76
(92881, 43, 67.518402, -2521.899902, 160.645004, 100.000000, 0, 0.000000, 0), -- spline 42/76
(92881, 44, 47.992401, -2556.679932, 154.673004, 100.000000, 0, 0.000000, 0), -- spline 43/76
(92881, 45, 27.443800, -2588.139893, 146.979004, 100.000000, 0, 0.000000, 0), -- spline 44/76
(92881, 46, 17.396900, -2612.679932, 148.645004, 100.000000, 0, 0.000000, 0), -- spline 45/76
(92881, 47, 21.831200, -2637.949951, 152.451004, 100.000000, 0, 0.000000, 0), -- spline 46/76
(92881, 48, 55.236801, -2648.290039, 155.867996, 100.000000, 0, 0.000000, 0), -- spline 47/76
(92881, 49, 79.086197, -2628.209961, 160.895004, 100.000000, 0, 0.000000, 0), -- spline 48/76
(92881, 50, 67.079903, -2605.689941, 163.145004, 100.000000, 0, 0.000000, 0), -- spline 49/76
(92881, 51, 58.428799, -2578.679932, 158.257004, 100.000000, 0, 0.000000, 0), -- spline 50/76
(92881, 52, 72.624199, -2532.919922, 160.979004, 100.000000, 0, 0.000000, 0), -- spline 51/76
(92881, 53, 81.372803, -2498.169922, 155.089996, 100.000000, 0, 0.000000, 0), -- spline 52/76
(92881, 54, 94.505203, -2469.600098, 159.007004, 100.000000, 0, 0.000000, 0), -- spline 53/76
(92881, 55, 100.960999, -2456.429932, 157.479004, 100.000000, 0, 0.000000, 0), -- spline 54/76
(92881, 56, 111.130997, -2428.989990, 160.673004, 100.000000, 0, 0.000000, 0), -- spline 55/76
(92881, 57, 115.309998, -2404.860107, 160.979004, 100.000000, 0, 0.000000, 0), -- spline 56/76
(92881, 58, 114.119003, -2371.610107, 157.783997, 100.000000, 0, 0.000000, 0), -- spline 57/76
(92881, 59, 109.720001, -2344.959961, 153.367996, 100.000000, 0, 0.000000, 0), -- spline 58/76
(92881, 60, 97.577103, -2320.800049, 153.701004, 100.000000, 0, 0.000000, 0), -- spline 59/76
(92881, 61, 80.574402, -2283.500000, 143.811996, 100.000000, 0, 0.000000, 0), -- spline 60/76
(92881, 62, 78.348396, -2265.120117, 144.007004, 100.000000, 0, 0.000000, 0), -- spline 61/76
(92881, 63, 84.780701, -2245.209961, 144.783997, 100.000000, 0, 0.000000, 0), -- spline 62/76
(92881, 64, 92.436798, -2223.620117, 147.283997, 100.000000, 0, 0.000000, 0), -- spline 63/76
(92881, 65, 98.482002, -2205.760010, 138.533997, 100.000000, 0, 0.000000, 0), -- spline 64/76
(92881, 66, 103.757004, -2172.600098, 140.007004, 100.000000, 0, 0.000000, 0), -- spline 65/76
(92881, 67, 100.174004, -2147.179932, 136.757004, 100.000000, 0, 0.000000, 0), -- spline 66/76
(92881, 68, 90.358101, -2125.510010, 145.561996, 100.000000, 0, 0.000000, 0), -- spline 67/76
(92881, 69, 69.620399, -2110.209961, 155.811996, 100.000000, 0, 0.000000, 0), -- spline 68/76
(92881, 70, 49.897900, -2097.540039, 174.367996, 100.000000, 0, 0.000000, 0), -- spline 69/76
(92881, 71, 40.182400, -2089.699951, 184.535995, 100.000000, 0, 0.000000, 0), -- spline 70/76
(92881, 72, 33.397400, -2076.469971, 198.817993, 100.000000, 0, 0.000000, 0), -- spline 71/76
(92881, 73, 17.798401, -2058.320068, 206.410995, 100.000000, 0, 0.000000, 0), -- spline 72/76
(92881, 74, 16.156099, -2046.180054, 219.289001, 100.000000, 0, 0.000000, 0), -- spline 73/76
(92881, 75, 5.402780, -2029.050049, 238.910995, 100.000000, 0, 0.000000, 0), -- spline 74/76
(92881, 76, 5.464740, -2020.020020, 258.058014, 100.000000, 0, 0.000000, 0), -- spline 75/76
(92881, 77, 2.117350, -2010.589966, 256.860992, 100.000000, 0, 0.000000, 0); -- spline 76/76


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
