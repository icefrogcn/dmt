DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20210307040307');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20210307040307');
-- Add your query below.


-- Correct waypoints for Black Drake (GUID: 5505)
UPDATE `creature` SET `position_x`=-8237.179688, `position_y`=-2684.229980, `position_z`=135.231995, `orientation`=5 WHERE `guid`=5505;
DELETE FROM `creature_movement` WHERE `id`=5505;
INSERT INTO `creature_movement` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `waittime`, `wander_distance`, `script_id`) VALUES
(5505, 1, -8237.179688, -2684.229980, 135.231995, 100.000000, 0, 0.000000, 0),
(5505, 2, -8211.030273, -2709.600098, 134.895996, 100.000000, 0, 0.000000, 0),
(5505, 3, -8200.120117, -2743.290039, 135.145996, 100.000000, 0, 0.000000, 0),
(5505, 4, -8188.790039, -2777.899902, 137.026001, 100.000000, 0, 0.000000, 0),
(5505, 5, -8162.600098, -2813.899902, 135.658997, 100.000000, 0, 0.000000, 0),
(5505, 6, -8149.270020, -2840.250000, 134.134003, 100.000000, 0, 0.000000, 0),
(5505, 7, -8143.580078, -2884.080078, 135.742996, 100.000000, 0, 0.000000, 0),
(5505, 8, -8116.919922, -2898.330078, 134.740005, 100.000000, 0, 0.000000, 0),
(5505, 9, -8078.220215, -2889.320068, 136.641006, 100.000000, 0, 0.000000, 0),
(5505, 10, -8043.600098, -2900.379883, 134.007004, 100.000000, 0, 0.000000, 0),
(5505, 11, -8074.029785, -2889.459961, 136.634003, 100.000000, 0, 0.000000, 0),
(5505, 12, -8108.919922, -2898.379883, 134.373001, 100.000000, 0, 0.000000, 0),
(5505, 13, -8139.350098, -2889.800049, 135.617996, 100.000000, 0, 0.000000, 0),
(5505, 14, -8146.839844, -2848.120117, 134.369003, 100.000000, 0, 0.000000, 0),
(5505, 15, -8157.810059, -2822.159912, 134.792999, 100.000000, 0, 0.000000, 0),
(5505, 16, -8186.029785, -2782.639893, 136.996002, 100.000000, 0, 0.000000, 0),
(5505, 17, -8197.419922, -2752.379883, 135.966995, 100.000000, 0, 0.000000, 0),
(5505, 18, -8206.530273, -2717.100098, 134.783997, 100.000000, 0, 0.000000, 0);

-- Correct waypoints for Black Drake (GUID: 3298)
UPDATE `creature` SET `position_x`=-8123.180176, `position_y`=-3010.610107, `position_z`=134.710999, `orientation`=0.5 WHERE `guid`=3298;
DELETE FROM `creature_movement` WHERE `id`=3298;
INSERT INTO `creature_movement` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `waittime`, `wander_distance`, `script_id`) VALUES
(3298, 1, -8123.180176, -3010.610107, 134.710999, 100.000000, 0, 0.000000, 0),
(3298, 2, -8099.200195, -2983.000000, 134.651001, 100.000000, 0, 0.000000, 0),
(3298, 3, -8074.770020, -2949.510010, 134.852005, 100.000000, 0, 0.000000, 0),
(3298, 4, -8034.419922, -2949.979980, 133.115005, 100.000000, 0, 0.000000, 0),
(3298, 5, -8006.509766, -2929.399902, 134.520996, 100.000000, 0, 0.000000, 0),
(3298, 6, -7981.220215, -2909.330078, 135.266998, 100.000000, 0, 0.000000, 0),
(3298, 7, -7945.669922, -2910.080078, 132.231995, 100.000000, 0, 0.000000, 0),
(3298, 8, -7913.439941, -2907.810059, 133.048996, 100.000000, 0, 0.000000, 0),
(3298, 9, -7874.390137, -2897.290039, 133.229996, 100.000000, 0, 0.000000, 0),
(3298, 10, -7857.990234, -2913.199951, 131.306000, 100.000000, 0, 0.000000, 0),
(3298, 11, -7836.500000, -2931.500000, 130.692001, 100.000000, 0, 0.000000, 0),
(3298, 12, -7813.069824, -2939.729980, 131.337997, 100.000000, 0, 0.000000, 0),
(3298, 13, -7785.689941, -2955.949951, 132.113007, 100.000000, 0, 0.000000, 0),
(3298, 14, -7758.580078, -2958.689941, 133.225998, 100.000000, 0, 0.000000, 0),
(3298, 15, -7778.689941, -2957.899902, 131.582001, 100.000000, 0, 0.000000, 0),
(3298, 16, -7807.979980, -2944.699951, 131.574997, 100.000000, 0, 0.000000, 0),
(3298, 17, -7833.520020, -2939.629883, 131.785995, 100.000000, 0, 0.000000, 0),
(3298, 18, -7854.379883, -2916.870117, 131.091995, 100.000000, 0, 0.000000, 0),
(3298, 19, -7870.330078, -2898.610107, 132.957001, 100.000000, 0, 0.000000, 0),
(3298, 20, -7904.399902, -2906.159912, 133.347000, 100.000000, 0, 0.000000, 0),
(3298, 21, -7936.560059, -2909.790039, 131.987000, 100.000000, 0, 0.000000, 0),
(3298, 22, -7976.850098, -2907.620117, 134.996002, 100.000000, 0, 0.000000, 0),
(3298, 23, -7999.609863, -2923.659912, 135.638000, 100.000000, 0, 0.000000, 0),
(3298, 24, -8027.490234, -2948.290039, 131.955994, 100.000000, 0, 0.000000, 0),
(3298, 25, -8066.810059, -2949.350098, 135.227005, 100.000000, 0, 0.000000, 0),
(3298, 26, -8093.509766, -2976.840088, 134.876007, 100.000000, 0, 0.000000, 0);

-- Correct waypoints for Black Drake (GUID: 3299)
UPDATE `creature` SET `position_x`=-7561.109863, `position_y`=-2696.100098, `position_z`=135.421997, `orientation`=4 WHERE `guid`=3299;
DELETE FROM `creature_movement` WHERE `id`=3299;
INSERT INTO `creature_movement` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `waittime`, `wander_distance`, `script_id`) VALUES
(3299, 1, -7561.109863, -2696.100098, 135.421997, 100.000000, 0, 0.000000, 0),
(3299, 2, -7580.839844, -2716.489990, 134.274002, 100.000000, 0, 0.000000, 0),
(3299, 3, -7586.839844, -2751.270020, 133.199005, 100.000000, 0, 0.000000, 0),
(3299, 4, -7594.109863, -2774.199951, 133.438004, 100.000000, 0, 0.000000, 0),
(3299, 5, -7620.370117, -2804.790039, 134.020004, 100.000000, 0, 0.000000, 0),
(3299, 6, -7633.339844, -2843.179932, 133.923004, 100.000000, 0, 0.000000, 0),
(3299, 7, -7636.810059, -2871.290039, 134.742004, 100.000000, 0, 0.000000, 0),
(3299, 8, -7651.270020, -2904.689941, 133.983994, 100.000000, 0, 0.000000, 0),
(3299, 9, -7674.500000, -2937.639893, 131.742004, 100.000000, 0, 0.000000, 0),
(3299, 10, -7713.589844, -2940.070068, 133.417007, 100.000000, 0, 0.000000, 0),
(3299, 11, -7725.209961, -2920.709961, 133.434006, 100.000000, 0, 0.000000, 0),
(3299, 12, -7750.109863, -2910.959961, 132.880005, 100.000000, 0, 0.000000, 0),
(3299, 13, -7765.939941, -2875.719971, 133.384003, 100.000000, 0, 0.000000, 0),
(3299, 14, -7809.930176, -2863.889893, 133.563995, 100.000000, 0, 0.000000, 0),
(3299, 15, -7774.640137, -2873.459961, 133.509995, 100.000000, 0, 0.000000, 0),
(3299, 16, -7753.089844, -2908.590088, 132.345001, 100.000000, 0, 0.000000, 0),
(3299, 17, -7730.700195, -2915.679932, 133.535004, 100.000000, 0, 0.000000, 0),
(3299, 18, -7718.839844, -2935.330078, 133.363007, 100.000000, 0, 0.000000, 0),
(3299, 19, -7681.540039, -2940.379883, 131.828003, 100.000000, 0, 0.000000, 0),
(3299, 20, -7655.330078, -2911.959961, 133.927994, 100.000000, 0, 0.000000, 0),
(3299, 21, -7639.520020, -2879.159912, 134.682007, 100.000000, 0, 0.000000, 0),
(3299, 22, -7634.959961, -2850.909912, 134.179993, 100.000000, 0, 0.000000, 0),
(3299, 23, -7624.169922, -2812.000000, 133.891006, 100.000000, 0, 0.000000, 0),
(3299, 24, -7598.720215, -2781.080078, 133.457993, 100.000000, 0, 0.000000, 0),
(3299, 25, -7588.189941, -2759.419922, 133.348007, 100.000000, 0, 0.000000, 0),
(3299, 26, -7584.979980, -2723.189941, 134.063004, 100.000000, 0, 0.000000, 0);

-- Correct spawn position height for Black Dragonspawn (GUID: 5334)
UPDATE `creature` SET `position_z`=135.333 WHERE `guid`=5334;

-- Correct spawn position height for Black Dragonspawn (GUID: 5336)
UPDATE `creature` SET `position_z`=142.414 WHERE `guid`=5336;

-- Correct waypoints for Scalding Drake (GUID: 3302)
UPDATE `creature` SET `position_x`=-8304.780273, `position_y`=-1953.719971, `position_z`=144.904999, `orientation`=5 WHERE `guid`=3302;
DELETE FROM `creature_movement` WHERE `id`=3302;
INSERT INTO `creature_movement` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `waittime`, `wander_distance`, `script_id`) VALUES
(3302, 1, -8304.780273, -1953.719971, 144.904999, 100.000000, 0, 0.000000, 0),
(3302, 2, -8283.099609, -1992.349976, 147.235992, 100.000000, 0, 0.000000, 0),
(3302, 3, -8249.459961, -1987.719971, 147.843002, 100.000000, 0, 0.000000, 0),
(3302, 4, -8230.400391, -1999.250000, 143.108994, 100.000000, 0, 0.000000, 0),
(3302, 5, -8189.729980, -2025.579956, 145.520004, 100.000000, 0, 0.000000, 0),
(3302, 6, -8166.750000, -2040.760010, 141.024002, 100.000000, 0, 0.000000, 0),
(3302, 7, -8142.370117, -2071.070068, 132.522003, 100.000000, 0, 0.000000, 0),
(3302, 8, -8147.959961, -2101.080078, 133.621994, 100.000000, 0, 0.000000, 0),
(3302, 9, -8174.189941, -2136.659912, 135.776993, 100.000000, 0, 0.000000, 0),
(3302, 10, -8191.919922, -2158.639893, 134.141998, 100.000000, 0, 0.000000, 0),
(3302, 11, -8199.820313, -2189.120117, 133.255997, 100.000000, 0, 0.000000, 0),
(3302, 12, -8201.469727, -2221.419922, 133.013000, 100.000000, 0, 0.000000, 0),
(3302, 13, -8196.969727, -2260.520020, 132.608002, 100.000000, 0, 0.000000, 0),
(3302, 14, -8200.959961, -2228.399902, 132.675003, 100.000000, 0, 0.000000, 0),
(3302, 15, -8200.799805, -2199.939941, 132.533997, 100.000000, 0, 0.000000, 0),
(3302, 16, -8196.410156, -2167.870117, 133.727997, 100.000000, 0, 0.000000, 0),
(3302, 17, -8178.500000, -2142.050049, 135.813004, 100.000000, 0, 0.000000, 0),
(3302, 18, -8150.810059, -2107.159912, 133.664001, 100.000000, 0, 0.000000, 0),
(3302, 19, -8141.240234, -2080.679932, 132.386993, 100.000000, 0, 0.000000, 0),
(3302, 20, -8162.129883, -2045.250000, 139.184006, 100.000000, 0, 0.000000, 0),
(3302, 21, -8183.870117, -2029.449951, 145.190994, 100.000000, 0, 0.000000, 0),
(3302, 22, -8224.589844, -2003.380005, 143.169998, 100.000000, 0, 0.000000, 0),
(3302, 23, -8243.299805, -1988.530029, 146.145004, 100.000000, 0, 0.000000, 0),
(3302, 24, -8277.799805, -1994.469971, 147.082993, 100.000000, 0, 0.000000, 0);

-- Correct waypoints for Scalding Drake (GUID: 3300)
UPDATE `creature` SET `position_x`=-8340.839844, `position_y`=-1849.910034, `position_z`=168.494003, `orientation`=5 WHERE `guid`=3300;
DELETE FROM `creature_movement` WHERE `id`=3300;
INSERT INTO `creature_movement` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `waittime`, `wander_distance`, `script_id`) VALUES
(3300, 1, -8340.839844, -1849.910034, 168.494003, 100.000000, 0, 0.000000, 0),
(3300, 2, -8339.019531, -1877.290039, 167.972000, 100.000000, 0, 0.000000, 0),
(3300, 3, -8327.870117, -1901.030029, 161.602997, 100.000000, 0, 0.000000, 0),
(3300, 4, -8305.009766, -1929.750000, 146.292999, 100.000000, 0, 0.000000, 0),
(3300, 5, -8272.440430, -1942.390015, 145.490005, 100.000000, 0, 0.000000, 0),
(3300, 6, -8231.320313, -1957.199951, 143.257004, 100.000000, 0, 0.000000, 0),
(3300, 7, -8210.839844, -1995.829956, 144.529007, 100.000000, 0, 0.000000, 0),
(3300, 8, -8184.229980, -2031.250000, 146.044998, 100.000000, 0, 0.000000, 0),
(3300, 9, -8163.870117, -2036.400024, 137.957001, 100.000000, 0, 0.000000, 0),
(3300, 10, -8136.359863, -2068.830078, 131.479004, 100.000000, 0, 0.000000, 0),
(3300, 11, -8125.399902, -2094.750000, 132.350006, 100.000000, 0, 0.000000, 0),
(3300, 12, -8095.040039, -2124.879883, 133.492996, 100.000000, 0, 0.000000, 0),
(3300, 13, -8121.899902, -2100.169922, 132.656006, 100.000000, 0, 0.000000, 0),
(3300, 14, -8133.419922, -2074.659912, 131.248993, 100.000000, 0, 0.000000, 0),
(3300, 15, -8158.660156, -2038.750000, 136.848999, 100.000000, 0, 0.000000, 0),
(3300, 16, -8179.680176, -2033.829956, 144.878006, 100.000000, 0, 0.000000, 0),
(3300, 17, -8207.440430, -2001.560059, 144.970993, 100.000000, 0, 0.000000, 0),
(3300, 18, -8227.400391, -1961.810059, 143.026993, 100.000000, 0, 0.000000, 0),
(3300, 19, -8266.459961, -1944.420044, 146.990997, 100.000000, 0, 0.000000, 0),
(3300, 20, -8300.330078, -1933.329956, 143.979996, 100.000000, 0, 0.000000, 0),
(3300, 21, -8324.349609, -1906.479980, 160.774002, 100.000000, 0, 0.000000, 0),
(3300, 22, -8336.230469, -1886.270020, 166.169998, 100.000000, 0, 0.000000, 0);


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
