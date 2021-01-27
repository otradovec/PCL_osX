//  Created by Student on 1/27/21.

#include "RoofExtractor.hpp"

RoofExtractor::RoofExtractor(std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr> segmentedClouds){
    for (pcl::PointCloud<pcl::PointXYZ>::Ptr cloud: segmentedClouds) {
        roofs.push_back(Roof(cloud));
    }
}
std::vector<Roof> RoofExtractor::getRoofs(){
    return roofs;
}
