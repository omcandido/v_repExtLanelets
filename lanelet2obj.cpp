#include <ros/package.h>
#include <geodesy/utm.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

#include <triangulate.h>
#include <liblanelet/libLanelet/llet_xml.hpp>
#include <MRT/libLanelet/llet_xml.hpp>
#include <MRT/libLanelet/Lanelet.hpp>
#include <MRT/libLanelet/LaneletMap.hpp>

using namespace LLet;

typedef std::vector<geometry_msgs::Point> Polygon;
typedef std::vector<Polygon> PolygonContainer;



int main(int argc, char** argv)
{
    std::string map_filepath = ros::package::getPath("sec_map_manager") + "/maps/uah_lanelets_v33.osm";
    static LaneletMap loaded_map(map_filepath);

    geographic_msgs::GeoPoint geo_pt_origen;
    geo_pt_origen.latitude = 49.01554822307355;
    geo_pt_origen.longitude = 8.493907824596581;
    geodesy::UTMPoint utm_pt_origen(geo_pt_origen);

    std::vector< lanelet_ptr_t > lanelets = loaded_map.lanelets();


    PolygonContainer laneShapeContainer;
    // laneShapeContainer contains all lanelets in polygon-shape
    // in Cartesian coordinates relative to origin

    for (auto const & lanelet : lanelets)
    {
        Polygon laneShape;

        std::vector< point_with_id_t > wayR =lanelet->nodes(RIGHT);
        std::vector< point_with_id_t > wayL =lanelet->nodes(LEFT);

        for (int i =0;i<wayR.size();i++)
        {
            geographic_msgs::GeoPoint geo_pt;
            geo_pt.latitude = std::get<0>(wayR[i]);
            geo_pt.longitude = std::get<1>(wayR[i]);
            geodesy::UTMPoint utm_pt(geo_pt);

            geometry_msgs::Point iterPoint;
            iterPoint.x= utm_pt.easting - utm_pt_origen.easting;
            iterPoint.y= utm_pt.northing- utm_pt_origen.northing;

            laneShape.push_back(iterPoint);
        }

        for (int i = wayL.size()-1;i>=0;i--)
        {
            geographic_msgs::GeoPoint geo_pt;
            geo_pt.latitude = std::get<0>(wayL[i]);
            geo_pt.longitude = std::get<1>(wayL[i]);
            geodesy::UTMPoint utm_pt(geo_pt);

            geometry_msgs::Point iterPoint;
            iterPoint.x= utm_pt.easting - utm_pt_origen.easting;
            iterPoint.y= utm_pt.northing- utm_pt_origen.northing;

            laneShape.push_back(iterPoint);
        }

        laneShapeContainer.push_back(laneShape);
    }


    // Now all polygons get triangulated and their vertices
    // are saved in an OBJ file, according to this format rules

    std::ofstream outFile;

    std::stringstream ssTime;
    ssTime<<std::time(0);
    std::string auxPath = "laneletsGenerated"+ssTime.str()+".obj";
    char filePath[auxPath.size()+1];
    strcpy(filePath,auxPath.c_str());

    outFile.open(filePath);

    int index=0;
    for (int p=0; p<laneShapeContainer.size();p++) //for each polygon
    {
        Vector2dVector pointList2D;
        for (int v=0;v<laneShapeContainer[p].size();v++) //for each vertex
        {
            pointList2D.push_back(Vector2d(laneShapeContainer[p][v].x,laneShapeContainer[p][v].y));
        }

        Vector2dVector result;
        Triangulate::Process(pointList2D,result);

        int tcount = result.size()/3;

        for (int i=0; i<tcount; i++)
        {
            const Vector2d &p1 = result[i*3+0];
            const Vector2d &p2 = result[i*3+1];
            const Vector2d &p3 = result[i*3+2];

            outFile<< "v "<< p1.GetX() << " " << p1.GetY() << " " << 0.1  <<"\n";
            outFile<< "v "<< p2.GetX() << " " << p2.GetY() << " " << 0.1  <<"\n";
            outFile<< "v "<< p3.GetX() << " " << p3.GetY() << " " << 0.1  <<"\n";
        }

        outFile << "g lanelet" << p+1 <<"\n";

        for (int i=0; i<tcount; i++)
        {
            outFile<< "f "<< index+1 << " " << index+2 << " " << index+3 <<"\n";
            index+=3;
        }

    }
    outFile.close();



    return 0;
}

