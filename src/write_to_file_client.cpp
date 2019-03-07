#include "include_files/include_files.h"
#include "Mini_SLAM/write_to_file.h"
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "write_to_file");
  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<Mini_SLAM::write_to_file>("write_to_file");
  Mini_SLAM::write_to_file srv;
    
  if (!client.call(srv))
  {
    ROS_ERROR("Failed to call service write_to_file");
    return 1;
  }

  return 0;
}