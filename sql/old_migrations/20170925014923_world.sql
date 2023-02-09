INSERT INTO migrations VALUES ('20170925014923');

REPLACE INTO gameobject (guid, id, map, position_x, position_y, position_z, orientation, rotation0, rotation1, rotation2, rotation3, spawntimesecs, animprogress, state, spawnFlags) VALUES
(429001,176584,429,102.525,-245.12,-56.3859,4.41487,0,0,0,0,604800,100,1,0),
(429002,176584,429,27.7274,-233.591,-53.0545,5.26702,0,0,0,0,604800,100,1,0),
(429003,176584,429,-92.3299,-259.519,-57.4316,4.85861,0,0,0,0,604800,100,1,0),
(429004,176584,429,-93.1671,-351.001,-56.9023,0.978747,0,0,0,0,604800,100,1,0),
(429005,176584,429,8.88853,-323.391,-51.6519,2.61238,0,0,0,0,604800,100,1,0),
(429006,176584,429,81.3605,-315.488,-55.0872,4.51697,0,0,0,0,604800,100,1,0),
(429007,176584,429,74.4623,-227.844,-56.924,2.34926,0,0,0,0,604800,100,1,0),
(429008,176584,429,-19.7489,-228.08,-56.1614,3.64125,0,0,0,0,604800,100,1,0),
(429009,176584,429,-35.1216,-327.748,-50.5495,3.24855,0,0,0,0,604800,100,1,0),
(429010,176584,429,-125.315,-313.137,-57.1105,3.80628,0,0,0,0,604800,100,1,0),
(429011,176584,429,114.686,-329.191,-55.0092,3.08371,0,0,0,0,604800,100,1,0),
(429012,142145,429,-43.4409,-438.748,16.4105,0.970886,0,0,0,0,604800,100,1,0),
(429013,142145,429,-54.5013,-437.795,-58.6145,2.35711,0,0,0,0,604800,100,1,0),
(429014,142145,429,-57.4221,-391.066,-58.6134,1.11618,0,0,0,0,604800,100,1,0),
(429015,142145,429,-92.8304,-223.093,-56.2404,2.98153,0,0,0,0,604800,100,1,0),
(429016,142145,429,24.5955,-395.136,-58.6137,0.0127397,0,0,0,0,604800,100,1,0),
(429017,142145,429,23.8166,-443.174,-58.622,3.05616,0,0,0,0,604800,100,1,0),
(429018,142145,429,22.3715,-422.871,-4.22198,5.47518,0,0,0,0,604800,100,1,0),
(429019,142145,429,-80.0236,-431.638,-4.21906,1.32828,0,0,0,0,604800,100,1,0),
(429020,142145,429,-7.73704,-432.26,-4.22207,5.85615,0,0,0,0,604800,100,1,0),
(429021,142145,429,-1.1858,-463.63,-58.6357,2.94234,0,0,0,0,604800,100,1,0),
(429022,142144,429,59.622,-382.857,-58.6199,6.21345,0,0,0,0,604800,100,1,0),
(429023,142144,429,32.9827,-635.064,-25.1502,3.64128,0,0,0,0,604800,100,1,0),
(429024,142144,429,70.1228,-784.91,-25.1672,2.41607,0,0,0,0,604800,100,1,0),
(429025,142144,429,17.6999,-715.219,-25.162,5.71083,0,0,0,0,604800,100,1,0),
(429026,142144,429,67.9744,-669.121,-25.1647,4.949,0,0,0,0,604800,100,1,0),
(429027,142144,429,80.1087,-420.509,-4.21348,0.570417,0,0,0,0,604800,100,1,0),
(429028,142144,429,-111.823,-433.323,-58.6057,1.3951,0,0,0,0,604800,100,1,0),
(429029,142144,429,-35.9896,-427.127,-37.9605,3.18974,0,0,0,0,604800,100,1,0);

REPLACE INTO pool_template (entry, max_limit, description, flags, instance) VALUES 
(4291, 2, 'Dire Maul East - Dreamfoil', 0, 0),
(4292, 2, 'Dire Maul East - Gromsblood', 0, 0),
(4293, 3, 'Dire Maul East - Ghost Mushroom', 0, 0);

REPLACE INTO pool_gameobject (guid, pool_entry, chance, description, flags) VALUES 
(429001,4291,0,'Dreamfoil',0),
(429002,4291,0,'Dreamfoil',0),
(429003,4291,0,'Dreamfoil',0),
(429004,4291,0,'Dreamfoil',0),
(429005,4291,0,'Dreamfoil',0),
(429006,4291,0,'Dreamfoil',0),
(429007,4291,0,'Dreamfoil',0),
(429008,4291,0,'Dreamfoil',0),
(429009,4291,0,'Dreamfoil',0),
(429010,4291,0,'Dreamfoil',0),
(429011,4291,0,'Dreamfoil',0),
(429012,4292,0,'Gromsblood',0),
(429013,4292,0,'Gromsblood',0),
(429014,4292,0,'Gromsblood',0),
(429015,4292,0,'Gromsblood',0),
(429016,4292,0,'Gromsblood',0),
(429017,4292,0,'Gromsblood',0),
(429018,4292,0,'Gromsblood',0),
(429019,4292,0,'Gromsblood',0),
(429020,4292,0,'Gromsblood',0),
(429021,4292,0,'Gromsblood',0),
(429022,4293,0,'Ghost Mushroom',0),
(429023,4293,0,'Ghost Mushroom',0),
(429024,4293,0,'Ghost Mushroom',0),
(429025,4293,0,'Ghost Mushroom',0),
(429026,4293,0,'Ghost Mushroom',0),
(429027,4293,0,'Ghost Mushroom',0),
(429028,4293,0,'Ghost Mushroom',0),
(429029,4293,0,'Ghost Mushroom',0);
