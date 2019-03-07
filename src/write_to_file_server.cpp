#include "include_files/include_files.h"
#include "Mini_SLAM/write_to_file.h"
#include <fstream>

nav_msgs::OccupancyGrid occ_grid;

bool write(Mini_SLAM::write_to_file::Request &req,
            Mini_SLAM::write_to_file::Response &res)
{
  ofstream myfile;
  myfile.open("src/Mini_SLAM/map.txt", fstream::out);
  for(uint i=0; i<occ_grid.info.height; i++) {
    for(uint j=0; j<occ_grid.info.width; j++) {
      myfile<<(int)occ_grid.data[i*10+j]<<"  ";
    }
    myfile<<"\n";
  }
  bool check_flag = myfile.good();
  myfile.close();

  if(check_flag)
    res.result = "map saved to map.txt\n";
  else
    res.result = "Failed. Try again\n";
  
  cout<<res.result;
  return true;
}

void callback(const nav_msgs::OccupancyGrid::ConstPtr &msg) {
  occ_grid = *msg;
}

int main(int argc, char **argv)
{ 
  int count=0;
  ros::init(argc, argv, "add_two_ints_server");
  ros::NodeHandle n;
  ros::Subscriber occ_map = n.subscribe("/map", 1, &callback);
  ros::ServiceServer service = n.advertiseService("write_to_file", write);
  ros::spin();
  
  return 0;
}