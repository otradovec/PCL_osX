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
    pcl::PointXYZ min,max;
    pcl::getMinMax3D(*cloud, min, max);
    std::cout << "min x " << min.x << "y "  << min.y << "z " << min.z << "\n";
    std::cout << "max x " << max.x << "y "  << max.y << "z " << max.z << "\n";

    m_viewer->addPointCloud<pcl::PointXYZ> (cloud, cloudName);
    m_viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, cloudName);
    m_viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR, (double)pointsColor.R/255, (double)pointsColor.G/255, (double)pointsColor.B/255, cloudName);
    m_numberOfClouds++;
}

void PCVisualization::addNormal(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, pcl::PointCloud<pcl::Normal>::Ptr normalCloud){
    cout << "Normal size " << normalCloud->size() << "\n";
    for (int i=0; i<10; i++) {
        cout << "Normal x " << normalCloud->at(i).normal_x
        << "Normal y " << normalCloud->at(i).normal_y
        << "Normal z " << normalCloud->at(i).normal_z
        << "Normal z " << normalCloud->at(i).curvature << "\n";
    }
    m_viewer->addPointCloudNormals<pcl::PointXYZ, pcl::Normal>(cloud, normalCloud, 50,0.1, "normals");
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

Color PCVisualization::rundomColorGenerator() {
    
    int r = rand() % (255 - 0) + 0;
    int g = rand() % (255 - 0) + 0;
    int b = rand() % (255 - 0) + 0;
    return Color(r, g, b);
}

void PCVisualization::addSegmentedCloud(std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr> segmentedClouds) {
    
    for (int i = 0; i < segmentedClouds.size(); i++) {
        addCloud(segmentedClouds.at(i), rundomColorGenerator());
    }
}

void PCVisualization::addRoofs(std::vector<Roof> roofs){
    Color color = rundomColorGenerator();
    for(Roof roof: roofs){
        color = rundomColorGenerator();
        this->addLine(roof.gethx(), roof.gethy(), color);
        this->addLine(roof.gethx(), roof.getly(), color);
        this->addLine(roof.getlx(), roof.gethy(), color);
        this->addLine(roof.getlx(), roof.getly(), color);
        this->addLine(roof.getTophx(),roof.getToplx(),color);
        
        if (roof.goesFromTopleftTobottomright()) {
            this->addLine(roof.getTophx(),roof.gethx(),color);
            this->addLine(roof.getTophx(), roof.getly(), color);
            this->addLine(roof.getToplx(), roof.getlx(), color);
            this->addLine(roof.getToplx(),roof.gethy(),color);
        }else{
            this->addLine(roof.getTophx(),roof.gethx(),color);
            this->addLine(roof.getTophx(), roof.gethy(), color);
            this->addLine(roof.getToplx(), roof.getlx(), color);
            this->addLine(roof.getToplx(),roof.getly(),color);
        }
    }
}


void PCVisualization::addLine(pcl::PointXYZ point1, pcl::PointXYZ point2, Color color){
    m_viewer->addLine(point1, point2, (double)color.R/255, (double)color.G/255, (double)color.B/255, "line" + std::to_string(m_numberOfClouds));
    m_numberOfClouds += 1;
}
