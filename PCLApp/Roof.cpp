//  Created by Student on 1/26/21.

#include "Roof.hpp"

Roof::Roof(pcl::PointCloud<pcl::PointXYZ>::Ptr roofCloud){
    hx = hy = lx = ly = tophx = toplx = roofCloud->points.at(1);
    pcl::PointXYZ min,max;
    pcl::getMinMax3D(*roofCloud, min, max);
    float threshold = ((max.z-min.z) * 0.7) + min.z;
    for(PointXYZ point:roofCloud->points){
        if (point.x>hx.x)
            hx=point;
        else if (point.x<lx.x)
            lx=point;
        
        if (point.y>hy.y)
            hy = point;
        else if (point.y<ly.y)
            ly=point;
        float zImportance = (0.02*500000)/600;
 
        if (point.z >threshold) {
            if(this->goesFromTopleftTobottomright()){
                if(point.x+(point.z*zImportance)-point.y > tophx.x+(tophx.z*zImportance)-tophx.y)
                    tophx = point;
                else if(point.x-(point.z*zImportance)-point.y < toplx.x-(toplx.z*zImportance)-toplx.y)
                    toplx = point;
            }else{
                if(point.x+(point.z*zImportance)+point.y > tophx.x+(tophx.z*zImportance)+tophx.y)
                    tophx = point;
                else if(point.x-(point.z*zImportance)+point.y < toplx.x-(toplx.z*zImportance)+toplx.y)
                    toplx = point;
            }
            
        }
    }
}

PointXYZ Roof::gethx(){
    return hx;
}
PointXYZ Roof::getlx(){
    return lx;
}
PointXYZ Roof::gethy(){
    return hy;
}
PointXYZ Roof::getly(){
    return ly;
}
PointXYZ Roof::getTophx(){
    return tophx;
}
PointXYZ Roof::getToplx(){
    return toplx;
}

bool Roof::goesFromTopleftTobottomright(){
    float xdiff = hy.x-ly.x;
    float ydiff = hx.y-lx.y;
    return (xdiff+ydiff) < 0;
}
