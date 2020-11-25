#include "PCLVisualization.hpp"


PCVisualization::PCVisualization()
{
    m_numberOfClouds = 0;
}

void PCVisualization::initializeVisualization(){
    
    // inicoalizace visuzalizeru
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
    // nasetuju ho
    m_viewer = viewer;
    // nastavim pozadi
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
    
    // potrebuju jmeno
    std::stringstream stream;
    stream << "cloud" << m_numberOfClouds;
    std::string cloudName =  stream.str();
    
    // pridam cloud
    m_viewer->addPointCloud<pcl::PointXYZ> (cloud, cloudName);
    // nasetuju vlastnosti
    m_viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, cloudName);
    // naseruju barvu
    m_viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR, (double)pointsColor.R/255, (double)pointsColor.G/255, (double)pointsColor.B/255, cloudName);
    // inkrementuju pocet mracen
    m_numberOfClouds++;
}


