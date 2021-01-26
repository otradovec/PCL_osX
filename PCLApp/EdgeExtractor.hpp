//
//  EdgeExtractor.hpp
//  PCLApp
//
//  Created by Student on 1/22/21.
//

#ifndef EdgeExtractor_hpp
#define EdgeExtractor_hpp

#include <stdio.h>
#include <iostream>

#include <boost/thread/thread.hpp>
#include <pcl/common/common_headers.h>
#include <pcl/features/normal_3d.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/features/organized_edge_detection.h>
#include <pcl/features/integral_image_normal.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/impl/point_types.hpp>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/PCLPointCloud2.h>

using namespace std;
using namespace pcl;
using namespace pcl::io;
using namespace pcl::console;
using namespace cv;

class EdgeExtractor{
public:
    EdgeExtractor();
    PointCloud<PointXYZ>::Ptr computeEdgeDetection (PointCloud<PointXYZ>::ConstPtr cloud, float th_dd, int max_search);
    PointCloud<Normal>::Ptr getNormalCloud(PointCloud<PointXYZ>::ConstPtr inputCloud);
};

#endif /* EdgeExtractor_hpp */
