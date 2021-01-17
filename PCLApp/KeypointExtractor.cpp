//  Created by Student on 1/17/21.
//

#include "KeypointExtractor.hpp"

KeypointExtractor::KeypointExtractor(){}

pcl::PointCloud<pcl::PointXYZ>::Ptr KeypointExtractor::extract(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud){
    // angular resolution in degrees (default "<<angular_resolution<<")\n"
    float angular_resolution = 0.5f;
    //  support size for the interest points (diameter of the used sphere - "
    float support_size = 0.8f;
    //    coordinate frame (default "<< (int)coordinate_frame<<")\n"
    //coordinate_frame = pcl::RangeImage::CoordinateFrame (argv);
    pcl::RangeImage::CoordinateFrame coordinate_frame = pcl::RangeImage::CAMERA_FRAME;
    //  Treat all unseen points as maximum range readings\n"
    bool setUnseenToMaxRange = false;
    
    angular_resolution = pcl::deg2rad (angular_resolution);
    
    pcl::PointCloud<pcl::PointXYZ>& point_cloud = *cloud;
    pcl::PointCloud<pcl::PointWithViewpoint> far_ranges;
    Eigen::Affine3f scene_sensor_pose (Eigen::Affine3f::Identity ());
    scene_sensor_pose = Eigen::Affine3f (Eigen::Translation3f (point_cloud.sensor_origin_[0],point_cloud.sensor_origin_[1], point_cloud.sensor_origin_[2])) *
        Eigen::Affine3f (point_cloud.sensor_orientation_);
    
     // -----------------------------------------------
    // -----Create RangeImage from the PointCloud-----
    // -----------------------------------------------
    float noise_level = 0.0;
    float min_range = 0.0f;
    int border_size = 1;
    pcl::RangeImage::Ptr range_image_ptr (new pcl::RangeImage);
    pcl::RangeImage& range_image = *range_image_ptr;
    range_image.createFromPointCloud (cloud, angular_resolution, pcl::deg2rad (360.0f), pcl::deg2rad (180.0f), scene_sensor_pose, coordinate_frame, noise_level, min_range, border_size);
    if (setUnseenToMaxRange)
        range_image.setUnseenToMaxRange ();
    
    // --------------------------------------------
    // -----Open 3D viewer and add point cloud-----
    // --------------------------------------------
    pcl::visualization::PCLVisualizer viewer ("3D Viewer");
    viewer.setBackgroundColor (1, 1, 1);
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointWithRange> range_image_color_handler (range_image_ptr, 0, 0, 0);
    viewer.addPointCloud (range_image_ptr, range_image_color_handler, "range image");
    viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "range image");
    //viewer.addCoordinateSystem (1.0f, "global");
    //PointCloudColorHandlerCustom<pcl::PointXYZ> point_cloud_color_handler (point_cloud_ptr, 150, 150, 150);
    //viewer.addPointCloud (point_cloud_ptr, point_cloud_color_handler, "original point cloud");
    viewer.initCameraParameters ();
    //setViewerPose (viewer, range_image.getTransformationToWorldSystem ());
    
    // --------------------------
    // -----Show range image-----
    // --------------------------
    pcl::visualization::RangeImageVisualizer range_image_widget ("Range image");
    range_image_widget.showRangeImage (range_image);
    
    // --------------------------------
    // -----Extract NARF keypoints-----
    // --------------------------------
    pcl::RangeImageBorderExtractor range_image_border_extractor;
    pcl::NarfKeypoint narf_keypoint_detector (&range_image_border_extractor);
    narf_keypoint_detector.setRangeImage (&range_image);
    narf_keypoint_detector.getParameters ().support_size = support_size;
    //narf_keypoint_detector.getParameters ().add_points_on_straight_edges = true;
    //narf_keypoint_detector.getParameters ().distance_for_additional_points = 0.5;
    
    pcl::PointCloud<int> keypoint_indices;
    narf_keypoint_detector.compute (keypoint_indices);
    std::cout << "Found "<<keypoint_indices.size ()<<" key points.\n";
    
    pcl::PointCloud<pcl::PointXYZ>::Ptr keypoints_ptr (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>& keypoints = *keypoints_ptr;
    keypoints.resize (keypoint_indices.size ());
    for (std::size_t i=0; i<keypoint_indices.size (); ++i)
    keypoints[i].getVector3fMap () = range_image[keypoint_indices[i]].getVector3fMap ();
    return keypoints_ptr;
    
    
}
