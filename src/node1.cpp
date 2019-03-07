#include "include_files/include_files.h"
#include "source_code/point_cloud.cpp"


int main(int argc, char **argv)
{
	ros::init(argc, argv, "node1");
	ros::NodeHandle nh1;
	
	ros::Publisher pc_publisher, grid_publisher;
	
	sleep(2);

	cout<<"here"<<endl;
	
	// class for the point cloud processing
	point_cloud *p_cloud = new point_cloud(nh1, pc_publisher, grid_publisher);
	ros::Rate loop_rate(1);

	// some condition for changing the directions in the occupancy grid
	int count=0, check_count = 8;	
	

	while(ros::ok()) {
		count++;
		p_cloud->publish_data(pc_publisher, grid_publisher, count, check_count);
		ros::spinOnce();
		loop_rate.sleep();
	}


// Destructors for all the objects defined in the heap
	delete(p_cloud);
	
	return 0;
}