#include "include_files/include_files.h"

class occupancy_grid {
private:
	nav_msgs::OccupancyGrid grid;

public:
	occupancy_grid() {
		grid.info.resolution = 1;
		grid.info.width = 10;
		grid.info.height = 10;
	}

	~occupancy_grid() {}



};