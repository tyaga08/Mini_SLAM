#include "include_files/include_files.h"
#include 

class occupancy_grid {
private:
	nav_msgs::OccupancyGrid grid;

public:
	ros::Publisher oc_grid_pub;

	occupancy_grid(ros::NodeHandle nh, ros::Publisher pc_publisher) {
		grid.info.resolution = 1;
		grid.info.width = 10;
		grid.info.height = 10;
		grid.data = {1,1,1,1,1,1,0,1,1,1,
					 1,0,0,0,0,0,0,0,0,1,
					 1,0,0,0,0,0,0,0,0,1,
					 1,0,0,1,0,0,1,0,0,1,
					 1,0,0,0,0,0,0,0,0,1,
					 1,0,0,0,0,0,0,0,0,1,
					 1,0,0,1,0,0,1,0,0,1,
					 1,0,0,0,0,0,0,0,0,1,
					 1,0,0,0,0,0,0,0,0,1,
					 1,1,1,1,1,1,1,0,0,1};

	}

	void publish_data () {
		oc_grid_pub.publish(grid);
		
	}

	~occupancy_grid() {}





};