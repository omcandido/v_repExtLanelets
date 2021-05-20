# v_repExtLanelets

## Citation

J. López, C. Otero, R. Sanz, E. Paz, E. Molinos and R. Barea, "A new approach to local navigation for autonomous driving vehicles based on the curvature velocity method," 2019 International Conference on Robotics and Automation (ICRA), 2019, pp. 1751-1757, doi: 10.1109/ICRA.2019.8794380.

___

A V-REP plugin to import lanelets as meshes

The liblanelet library is used from source instead of binaries,
so there is no need to run 'scons install' if you are going to compile the plugin.

No dependencies should be necesary to compile the plugin, other than V-REP's libraries.
To solve these dependencies, clone the plugin in the V-REP/programming folder, along with the other plugins
(this is because it needs the "common", "include", etc V-REP folders).

If you find any problems, please let me know.

## INSTRUCTIONS
- Compile the plugin (there is a compiled plugin for Linux x64 under the "compiled_plugin" folder)
- Run V-REP
- Plugins >> Lanelets import...
- Choose the OSM file with the mapped lanelets
- Set the origin in lat/lon format (THIS IS MANDATORY)
  The origin point must be a local reference point and it should 
  be 'near' the mapped area to avoid problems with large distances.
  This is the point of the Earth that will match the origin of the scene in V-REP.
  
  If you want to add buildings and other elements automatically,
  you can go to https://www.openstreetmap.org and export the same area you have mapped from 
  JOSM (roughly the same area). You will get an OSM file.
  Then, use http://osm2world.org/ to convert that file into an OBJ file.
  The first lines of this file contain the origin in lat/lon format that 
  you must enter so that both meshes match.
  (NOTE: the exported file by osm2world will most likely have elements that are not 
  of your interest. I recommend you to remove them manually using some program like Blender, 
  V-REP itself or simply editing the text file and keeping only what you want, e.g: buildings).

  If you do not have any local reference point of your interest, you can simply enter
  the coordinates of one arbitrary Node of the map you want or even better, some random point
  approximately in the middle of the map. 

- Click Import and a shape should appear in your scene. If you don't see anything,
  you probably need to zoom out. To do so, you can select the shape in the tree window
  and click 'Fit to view' (5th button starting from the left on the V-REP top toolbar).

## MORE INFO
The creation of this plugin has been motivated by the "Smart Elderly Car Project" (collaboration 
between the Uvigo and UAH), in which an autonomous urban car is simulated in V-REP.

J. López, C. Otero, R. Sanz, E. Paz, E. Molinos and R. Barea, "A new approach to local navigation for autonomous driving vehicles based on the curvature velocity method," 2019 International Conference on Robotics and Automation (ICRA), 2019, pp. 1751-1757, doi: 10.1109/ICRA.2019.8794380.

C. Otero, E. Paz, R. Sanz y J. López , R. Barea, E. Romera, E. Molinos, R. Arroyo, L.M. Bergasa, E. López , “ SIMULACIÓN DE VEHÍCULOS AUTÓNOMOS USANDO V - REP BAJO ROS ”,  Accepted for publication in the conference JA2017 (XXXVIII  Jornadas  de Automática), Gijón , Spain, September, 6th - 8th 2017.

- Project's website: https://www.robesafe.uah.es/index.php/en/smartelderlycar

- Youtube demos:
	* https://www.youtube.com/user/RobeSafe
	* https://www.youtube.com/channel/UC7jt8T4QEy3RLMCZEwME8SA/videos

### TODO:
- [ ] Add regulatory elements.
- [ ] Add textures
- [ ] Possibility of directly adding buildings using an exported map from Open Street Map
- [ ] Smooth lanelets
- [ ] Improve triangulation
- [ ] Fix assert exception (llet_xml.cpp, line 203)
- ...

NOTE: this project was meant to be taken on by students as a Bs. Project, but there has been a lack of volunteers. Feel free to improve this code.
