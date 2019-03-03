#include "include_files/include_files.h"
#include "source_code/point_cloud.cpp"

using namespace std;

int main(int argc, char **argv)
{
	ros::init(argc, argv, "node_1");
	ros::NodeHandle nh1;
	int count=0;
	ros::Publisher pc_publisher;
	
	sleep(5);

	cout<<"here"<<endl;
	point_cloud *p_cloud = new point_cloud(nh1, pc_publisher);

	while(ros::ok()) {
		p_cloud->publish_data(pc_publisher);
		cout<<"here finally"<<endl;
		ros::spinOnce();
	}	
	delete(p_cloud);
	
	return 0;
}