#include "include_files/include_files.h"
#include "source_code/probability_grid.cpp"

int main(int argc, char **argv)
{
	ros::init(argc, argv, "node2");
	ros::NodeHandle nh2;

	ros::Subscriber pc_subscriber;

	probability_grid *pr_grid = new probability_grid();

	pc_subscriber = nh2.subscribe("/cloud",1, &probability_grid::cloud_callback, pr_grid);

	ros::spin();

	return 0;
}