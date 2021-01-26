//  Created by Student on 1/22/21.

#include "EdgeExtractor.hpp"
EdgeExtractor::EdgeExtractor(){
    
}

PointCloud<Normal>::Ptr EdgeExtractor::getNormalCloud(PointCloud<PointXYZ>::ConstPtr inputCloud){
    PointCloud<Normal>::Ptr normal (new PointCloud<Normal>);
    NormalEstimation<PointXYZ, Normal> ne;
     // ne.setRadiusSearch(100);//might be too low or high
      ne.setKSearch(10);
    //ne.setNormalEstimationMethod (ne.COVARIANCE_MATRIX);
    //ne.setNormalSmoothingSize (10.0f);
    //ne.setBorderPolicy (ne.BORDER_POLICY_MIRROR);
    ne.setInputCloud (inputCloud);
    ne.compute (*normal);
    return normal;
}

PointCloud<PointXYZ>::Ptr EdgeExtractor::computeEdgeDetection (PointCloud<PointXYZ>::ConstPtr cloud, float th_dd, int max_search)
{
    PointCloud<Normal>::Ptr normalCloud = getNormalCloud(cloud);

    cout << "Normals size: " << normalCloud->size() << endl;
    OrganizedEdgeFromNormals<PointXYZ, Normal, Label> oed;
  oed.setInputNormals (normalCloud);
  oed.setInputCloud (cloud);
  oed.setDepthDisconThreshold (th_dd);
  oed.setMaxSearchNeighbors (max_search);
  oed.setEdgeType (oed.EDGELABEL_NAN_BOUNDARY | oed.EDGELABEL_OCCLUDING | oed.EDGELABEL_OCCLUDED | oed.EDGELABEL_HIGH_CURVATURE | oed.EDGELABEL_RGB_CANNY);
  PointCloud<Label> labels;
  vector<PointIndices> label_indices;
  oed.compute (labels, label_indices);

    PointCloud<PointXYZ>::Ptr occluding_edges (new PointCloud<PointXYZ>),
        occluded_edges (new PointCloud<PointXYZ>),
        nan_boundary_edges (new PointCloud<PointXYZ>),
        high_curvature_edges (new PointCloud<PointXYZ>),
        rgb_edges (new PointCloud<PointXYZ>);

      copyPointCloud (*cloud, label_indices[0].indices, *nan_boundary_edges);
      copyPointCloud (*cloud, label_indices[1].indices, *occluding_edges);
      copyPointCloud (*cloud, label_indices[2].indices, *occluded_edges);
      copyPointCloud (*cloud, label_indices[3].indices, *high_curvature_edges);
      copyPointCloud (*cloud, label_indices[4].indices, *rgb_edges);
    cout << "Nan size: " << nan_boundary_edges->size() << endl;
    cout << "Nan size: " << occluding_edges->size() << endl;
    cout << "Nan size: " << occluded_edges->size() << endl;
    cout << "Nan size: " << high_curvature_edges->size() << endl;
    cout << "Nan size: " << rgb_edges->size() << endl;
    cout << "Nan size: " << rgb_edges->size() << endl;

    return occluding_edges;
}
