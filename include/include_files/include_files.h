#include<iostream>
#include<ros/ros.h>

#include<nav_msgs/OccupancyGrid.h>
#include<sensor_msgs/PointCloud2.h>
#include<sensor_msgs/PointField.h>
#include<pcl/point_types.h>
#include<pcl/point_cloud.h>
#include<pcl_ros/point_cloud.h>
#include<pcl_conversions/pcl_conversions.h>
#include<Eigen/Dense>
#include<string>
#include<vector>


#include "cartographer/mapping/2d/probability_grid.h"
#include "cartographer_ros/node_options.h"
#include "gtest/gtest.h"
#include "ros/package.h"

using namespace std;