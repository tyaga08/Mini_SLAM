#include "include_files/include_files.h"
#include "source_code/occupancy_grid.cpp"

using namespace std;

int main(int argc, char **argv)
{
	ros::init(argc, argv, "node_1");
	ros::NodeHandle nh1;
	
	occupancy_grid *oc_grid = new occupancy_grid();
	

	return 0;
}