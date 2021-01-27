//  Created by Jaromír Landa on 15/10/2020.
//

#include <iostream>
#include <thread>

#include <pcl/console/parse.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/ransac.h>
#include <pcl/sample_consensus/sac_model_plane.h>
#include <pcl/sample_consensus/sac_model_sphere.h>
#include <pcl/visualization/pcl_visualizer.h>

#include <pcl/filters/voxel_grid.h>
#include <pcl/kdtree/kdtree_flann.h>

#include "PLYLoader.hpp"
#include "PCLVisualization.hpp"
#include "GroundExtractor.hpp"
#include "Ransac.hpp"
#include "EdgeExtractor.hpp"
#include "Segmentation.hpp"
#include "RoofExtractor.hpp"


int
main(int argc, char** argv)
{
 
    PLYLoader loader;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud = loader.loadCloud("PCLApp/urban_area.ply");
    
    pcl::KdTreeFLANN<pcl::PointXYZ> kdtree;
    kdtree.setInputCloud (cloud);
    
    pcl::PointCloud<pcl::PointXYZ>::Ptr filteredCloud (new pcl::PointCloud<pcl::PointXYZ>);

    pcl::VoxelGrid<pcl::PointXYZ> voxelGrigFilter;
    voxelGrigFilter.setInputCloud(cloud);
    voxelGrigFilter.setLeafSize(1.0f, 1.0f, 1.0f);
    voxelGrigFilter.filter(*filteredCloud);
    
    std::cout << filteredCloud->points.size() << std::endl;

    GroundExtractor groundExtractor;
    groundExtractor.extractGround(filteredCloud);
    filteredCloud = groundExtractor.getEverythingElse();
    
    Segmentation segmentation;
    std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr> segmentedCloud = segmentation.euclidianClusterSegmentation(filteredCloud);
    
    RoofExtractor roofEx = RoofExtractor(segmentedCloud);
    std::vector<Roof> roofs = roofEx.getRoofs();
    
    
    //EdgeExtractor edgeExtractor;
    //filteredCloud = edgeExtractor.computeEdgeDetection(filteredCloud, 1, 100);
    
    PCVisualization pclVisualization;
    pclVisualization.initializeVisualization();
    pclVisualization.addRoofs(roofs);
    //pclVisualization.addSegmentedCloud(segmentedCloud);
    //pclVisualization.addCloud(filteredCloud, Color(0, 255, 255));
    //pclVisualization.addNormal(filteredCloud,edgeExtractor.getNormalCloud(filteredCloud));
    
    //pclVisualization.addCloud(groundExtractor.getGround(), Color(255, 0, 0));
    pclVisualization.runVisualization();
    return 0;
 }
