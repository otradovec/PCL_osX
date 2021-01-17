//  Created by Student on 1/17/21.
//

#ifndef KeypointExtractor_hpp
#define KeypointExtractor_hpp

#include <stdio.h>
#include <iostream>

#include <pcl/range_image/range_image.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/range_image_visualizer.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/features/range_image_border_extractor.h>
#include <pcl/keypoints/narf_keypoint.h>
#include <pcl/console/parse.h>
#include <pcl/common/file_io.h> // for getFilenameWithoutExtension



class KeypointExtractor{
public:
    KeypointExtractor();
    pcl::PointCloud<pcl::PointXYZ>::Ptr extract(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
};

#endif /* KeypointExtractor_hpp */
