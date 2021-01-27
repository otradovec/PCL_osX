//  Created by Student on 1/27/21.

#ifndef RoofExtractor_hpp
#define RoofExtractor_hpp

#include <stdio.h>
#include <vector>
#include "Roof.hpp"

class RoofExtractor{
    std::vector<Roof> roofs;
public:
    RoofExtractor(std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr> segmentedClouds);
    std::vector<Roof> getRoofs();
};

#endif /* RoofExtractor_hpp */
