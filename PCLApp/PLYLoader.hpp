//
//  PLYLoader.hpp
//  PCLApp
//
//  Created by Jaromír Landa on 04/11/2020.
//

#ifndef PLYLoader_hpp
#define PLYLoader_hpp

#include <stdio.h>
#include <pcl/point_types.h>
#include <pcl/io/ply_io.h>

class PLYLoader {
public:
    PLYLoader();
    pcl::PointCloud<pcl::PointXYZ>::Ptr loadCloud(std::string filename);
};

#endif /* PLYLoader_hpp */
