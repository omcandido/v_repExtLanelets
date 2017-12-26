/* ----------------------------------------------------------
 * v_repExtLanelets plugin
 * (c) Candido Otero, 2017, Universidade de Vigo
 * ----------------------------------------------------------*/

#include "lanelet2obj.hpp"
#include <stdio.h>

using namespace LLet;

std::string lanelet2obj::generateMesh(const std::string &filePath,
                    const double oriLat,
                    const double oriLon)
{


    auto lanelets = parse_xml(filePath);

    LocalGeographicCS geo(oriLat,oriLon);

    PolygonContainer laneShapeContainer;

    //  1.
    //  For each lanelet in 'lanelets', save it as a polygon.
    //  To do so, append each node of the rigth boundary
    //  and do the same with the left boundary.
    //  All points must be transformed to Cartessian coordinates
    //  relative to the origin point

    for (auto const & lanelet : lanelets){ //for each lane
        Polygon laneShape;
        std::vector<point_with_id_t> wayR = lanelet->nodes(RIGHT);
        std::vector<point_with_id_t> wayL = lanelet->nodes(LEFT);
        for (int i = 0; i < wayR.size(); ++i){//for each right bound
            Point iterPoint;
            double lat = std::get<0>(wayR.at(i));
            double lon = std::get<1>(wayR.at(i));
            geo.ll2xy(lat,lon,iterPoint.X, iterPoint.Y);
            laneShape.push_back(iterPoint);
        }
        for (int i = wayL.size() -1; i >= 0; --i){//for each left bound, reversed
            Point iterPoint;
            double lat = std::get<0>(wayL.at(i));
            double lon = std::get<1>(wayL.at(i));
            geo.ll2xy(lat,lon,iterPoint.X, iterPoint.Y);
            laneShape.push_back(iterPoint);
        }
        laneShapeContainer.push_back(laneShape);
    }
    //  2.
    //  Now all polygons get triangulated and their vertices
    //  are saved in an OBJ file, according to this format rules

    std::ofstream outFile;

    std::stringstream ssTime;
    ssTime<<std::time(0);
    std::string OBJauxPath = "laneletsGenerated" + ssTime.str() + ".obj";
    char OBJfilePath[OBJauxPath.size() + 1];
    strcpy(OBJfilePath, OBJauxPath.c_str());

    outFile.open(OBJfilePath);

    int index=0;
    for (int p=0; p < laneShapeContainer.size(); ++p) //for each polygon
    {
        Vector2dVector pointList2D;
        for (int v = 0; v < laneShapeContainer[p].size(); ++v) //for each vertex
        {
            pointList2D.push_back(Vector2d(laneShapeContainer[p][v].X,
                                           laneShapeContainer[p][v].Y));
        }

        Vector2dVector result;
        Triangulate::Process(pointList2D,result);

        int tcount = result.size()/3;

        for (int i=0; i<tcount; i++)
        {
            const Vector2d &p1 = result[i*3 + 0];
            const Vector2d &p2 = result[i*3 + 1];
            const Vector2d &p3 = result[i*3 + 2];

            outFile<< "v "<< p1.GetX() << " " << p1.GetY() << " " << 0.1  <<"\n";
            outFile<< "v "<< p2.GetX() << " " << p2.GetY() << " " << 0.1  <<"\n";
            outFile<< "v "<< p3.GetX() << " " << p3.GetY() << " " << 0.1  <<"\n";
        }

        outFile << "g lanelet" << p + 1 <<"\n";

        for (int i=0; i<tcount; i++)
        {
            outFile<< "f "<< index+1 << " " << index+2 << " " << index+3 <<"\n";
            index += 3;
        }
    }
    outFile.close();
    return OBJauxPath;
}


int lanelet2obj::importLanelets(const std::string &filePath,
                   const double oriLat,
                   const double oriLon,
                   const bool rm)
{
    std::string path = generateMesh(filePath, oriLat, oriLon);
    int handleShape = simImportShape(0,
                                     path.c_str(),
                                     (1*0 + 2*0 + 4*0 + 8*0 + 16*0),
                                     0.00001,
                                     1);
    if (handleShape!=-1){
        int res = simSetObjectName(handleShape, "LaneletMap");
        handleShape = res == -1 ? -2 : handleShape;
    }
    if (rm) remove(path.c_str());   // remove after loading the OBJ file into the scene
    return handleShape;     // handleSpahe = -1 means error. Positive otherwise
}

