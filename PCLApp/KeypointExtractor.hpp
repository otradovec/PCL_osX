//  Created by Student on 1/17/21.
//

#ifndef KeypointExtractor_hpp
#define KeypointExtractor_hpp

#include <stdio.h>
#include <iostream>

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
