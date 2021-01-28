//  Created by Student on 1/26/21.

#ifndef Roof_hpp
#define Roof_hpp

#include <stdio.h>

#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/common/common.h>

using namespace pcl;
using namespace std;

class Roof{
    PointXYZ hx,ly,lx,hy,tophx,toplx;
    
public:
    Roof(pcl::PointCloud<pcl::PointXYZ>::Ptr roofCloud);
    PointXYZ gethx();
    PointXYZ getlx();
    PointXYZ gethy();
    PointXYZ getly();
    PointXYZ getTophx();
    PointXYZ getToplx();
    bool goesFromTopleftTobottomright();
};

#endif /* Roof_hpp */
