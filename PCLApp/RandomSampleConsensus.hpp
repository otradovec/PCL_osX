//  Created by Student on 1/17/21.
//

#ifndef RandomSampleConsensus_hpp
#define RandomSampleConsensus_hpp

#include <iostream>
#include <thread>

#include <pcl/console/parse.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/ransac.h>
#include <pcl/sample_consensus/sac_model_plane.h>


#include "PCLVisualization.hpp"

using namespace std::chrono_literals;

class RandomSampleConsensus{
public:
    RandomSampleConsensus();
    pcl::PointCloud<pcl::PointXYZ>::Ptr getPlanes(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
};

#include <stdio.h>

#endif /* RandomSampleConsensus_hpp */
