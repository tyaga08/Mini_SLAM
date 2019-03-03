#include "include_files/include_files.h"
#include "source_code/point_cloud.cpp"


using namespace std;

int main(int argc, char **argv)
{
	ros::init(argc, argv, "node_1");
	ros::NodeHandle nh1;
	
	ros::Publisher pc_publisher;
	
	sleep(5);

	cout<<"here"<<endl;
	point_cloud *p_cloud = new point_cloud(nh1, pc_publisher);
	ros::Rate loop_rate(1);

	int count=0, check_count = 8;	

	while(ros::ok()) {
		count++;
		p_cloud->publish_data(pc_publisher,count, check_count);

		cout<<"here finally"<<endl;
		ros::spinOnce();
		loop_rate.sleep();
	}




// Destructors for all the objects defined in the heap
	delete(p_cloud);
	
	return 0;
}