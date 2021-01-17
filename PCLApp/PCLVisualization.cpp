#include "PCLVisualization.hpp"


PCVisualization::PCVisualization()
{
    m_numberOfClouds = 0;
}

void PCVisualization::initializeVisualization(){
        boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
    m_viewer = viewer;
    m_viewer->setBackgroundColor (0, 0, 0);
}


void PCVisualization::runVisualization(){
    
    m_viewer->initCameraParameters();
    m_viewer->resetCameraViewpoint("cloud0");
    
    while (!m_viewer->wasStopped ())
    {
        m_viewer->spinOnce (100);
        boost::this_thread::sleep (boost::posix_time::microseconds (100000));
    }
    m_viewer->close();
}


void PCVisualization::addCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, Color pointsColor){
        std::stringstream stream;
    stream << "cloud" << m_numberOfClouds;
    std::string cloudName =  stream.str();
    
    m_viewer->addPointCloud<pcl::PointXYZ> (cloud, cloudName);
    m_viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, cloudName);
    // setting color
    m_viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR, (double)pointsColor.R/255, (double)pointsColor.G/255, (double)pointsColor.B/255, cloudName);
    m_numberOfClouds++;
}

pcl::visualization::PCLVisualizer::Ptr
PCVisualization::simpleVis (pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud)
{
  // -----Open 3D viewer and add point cloud-----
  pcl::visualization::PCLVisualizer::Ptr viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
  viewer->setBackgroundColor (0, 0, 0);
  viewer->addPointCloud<pcl::PointXYZ> (cloud, "sample cloud");
  viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud");
  //viewer->addCoordinateSystem (1.0, "global");
  viewer->initCameraParameters ();
  return (viewer);
}

