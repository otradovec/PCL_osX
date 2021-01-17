//  Created by Jaromír Landa on 04/11/2020.

#include "PLYLoader.hpp"

PLYLoader::PLYLoader(){
    
}


pcl::PointCloud<pcl::PointXYZ>::Ptr PLYLoader::loadCloud(std::string filename){

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PLYReader reader;
    reader.read(filename, *cloud);
    return cloud;
}
