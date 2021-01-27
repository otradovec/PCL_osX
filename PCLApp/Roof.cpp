//  Created by Student on 1/26/21.

#include "Roof.hpp"

Roof::Roof(pcl::PointCloud<pcl::PointXYZ>::Ptr roofCloud){
    hx = hy = lx = ly = roofCloud->points.at(1);
    for(PointXYZ point:roofCloud->points){
        if (point.x>hx.x)
            hx=point;
        else if (point.x<lx.x)
            lx=point;
        
        if (point.y>hy.y)
            hy = point;
        else if (point.y<ly.y)
            ly=point;
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
