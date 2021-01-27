#pragma warning(disable:4996)
#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define BOOST_ALL_NO_LIB
#define BOOST_USE_WINDOWS_H
#define NOMINMAX

#include <iostream>
#include <pcl/segmentation/region_growing.h>
#include <pcl/search/search.h>
#include <pcl/search/kdtree.h>
#include <pcl/features/normal_3d.h>
#include <pcl/segmentation/extract_clusters.h>

#include <vector>

class Segmentation{
private:
    
    
public:
    Segmentation();
    std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr> euclidianClusterSegmentation(pcl::PointCloud<pcl::PointXYZ>::Ptr cloudToSegment);
    
};


