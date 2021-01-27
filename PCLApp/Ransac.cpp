//  Created by Student on 1/17/21.
//

#include "Ransac.hpp"

Ransac::Ransac(){
    
}

pcl::PointCloud<pcl::PointXYZ>::Ptr Ransac::getPlanes(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud){

    //cloud->points.resize (cloud->width * cloud->height);
    pcl::SampleConsensusModelPlane<pcl::PointXYZ>::Ptr
    model_p (new pcl::SampleConsensusModelPlane<pcl::PointXYZ> (cloud));
    pcl::RandomSampleConsensus<pcl::PointXYZ> ransac (model_p);
    ransac.setDistanceThreshold (0.9);
    ransac.computeModel();
    std::vector<int> inliers;
    ransac.getInliers(inliers);
    pcl::PointCloud<pcl::PointXYZ>::Ptr finalCloud (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::copyPointCloud (*cloud, inliers, *finalCloud);
    return finalCloud;
}

