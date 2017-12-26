/* ----------------------------------------------------------
 * v_repExtLanelets plugin
 * (c) Candido Otero, 2017, Universidade de Vigo
 * ----------------------------------------------------------*/

#pragma once

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <tuple>
#include <numeric>

#include "triangulate.h"
#include "v_repLib.h"
#include "MRT/libLanelet/llet_xml.hpp"
#include "MRT/libLanelet/Lanelet.hpp"
#include "MRT/libLanelet/LaneletMap.hpp"
#include "MRT/Commons/LocalGeographicCS.hpp"

namespace lanelet2obj {

using namespace LLet;

typedef struct {
    double X;
    double Y;
}Point;

typedef std::vector<Point> Polygon;
typedef std::vector<Polygon> PolygonContainer;

std::string generateMesh(const std::string &filePath,
                      const double oriLat,
                      const double oriLon);

int importLanelets(const std::string &filePath,
                   const double oriLat,
                   const double oriLon,
                   const bool rm);


}//end namespace
