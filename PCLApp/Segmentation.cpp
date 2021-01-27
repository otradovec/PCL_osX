#include "Segmentation.hpp"

Segmentation::Segmentation(){
    
}

std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr> Segmentation::euclidianClusterSegmentation(pcl::PointCloud<pcl::PointXYZ>::Ptr cloudToSegment){
    
    std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr> segmentedClouds;
    
    pcl::search::KdTree<pcl::PointXYZ>::Ptr kdTree (new pcl::search::KdTree<pcl::PointXYZ>);
    kdTree->setInputCloud (cloudToSegment);
    
    std::vector<pcl::PointIndices> clusterIndices;
    pcl::EuclideanClusterExtraction<pcl::PointXYZ> euclideanClusterExtraction;
    euclideanClusterExtraction.setClusterTolerance (1.15); // 2cm
    euclideanClusterExtraction.setMinClusterSize (100);
    euclideanClusterExtraction.setMaxClusterSize (1000);
    euclideanClusterExtraction.setSearchMethod (kdTree);
    euclideanClusterExtraction.setInputCloud (cloudToSegment);
    euclideanClusterExtraction.extract (clusterIndices);
    
    
    for (std::vector<pcl::PointIndices>::const_iterator it = clusterIndices.begin (); it != clusterIndices.end (); ++it)
    {
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloudCluster (new pcl::PointCloud<pcl::PointXYZ>);
        for (std::vector<int>::const_iterator pit = it->indices.begin (); pit != it->indices.end (); ++pit)
            cloudCluster->points.push_back (cloudToSegment->points[*pit]); //*
        cloudCluster->width = cloudCluster->points.size ();
        cloudCluster->height = 1;
        cloudCluster->is_dense = true;
        
        segmentedClouds.push_back(cloudCluster);
    }
    
    return segmentedClouds;
}
