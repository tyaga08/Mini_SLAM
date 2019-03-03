#include "include_files/include_files.h"
#include "source_code/occupancy_grid.cpp"

class point_cloud {
private:
		sensor_msgs::PointCloud2 pcloud;
		shared_ptr<occupancy_grid> oc_grid;
		pcl::PointCloud<pcl::PointXY> cloud;
	

public:

	point_cloud(ros::NodeHandle &nh, ros::Publisher &pc_publisher) {
		oc_grid = shared_ptr<occupancy_grid>(new occupancy_grid());

		cloud.height = 3;
		cloud.width = 5;
		cloud.is_dense = true;
		cloud.points.resize(cloud.height*cloud.width);

		pcloud.height = 1;
		pcloud.width = 1;

		pcloud.point_step = 2; // considering uint8 for datatype
		pcloud.row_step = pcloud.point_step* pcloud.width;
		cout<<"here in constructor"<<endl;
		// 
		sensor_msgs::PointField field1, field2;
		field1.name = "x";
		field1.offset = 0;
		field1.datatype = sensor_msgs::PointField::INT8;
		field1.count = 1;

		field2.name = "y";
		field2.offset = 0;
		field2.datatype = sensor_msgs::PointField::INT8;
		field2.count = 1;

		pcloud.fields = {field1,field2};

		cout<<"here"<<endl;

		pcloud.is_dense = true;
		pc_publisher = nh.advertise<sensor_msgs::PointCloud2>("/cloud", 1);
	}

	~point_cloud() {}

	void publish_data(ros::Publisher &pc_publisher, int &count, int &check_count);
	
	void synthesize_point_cloud(vector<pair<int8_t,int8_t> > &occupied_points);

};


void point_cloud::publish_data(ros::Publisher &pc_publisher, int &count, int &check_count) {
		if(count!=check_count)
			oc_grid->navigate_robot("forward");

		else {
			check_count = 6;
			count = 0;
			oc_grid->navigate_robot("left");
		}

		vector<pair<int8_t,int8_t> > occupied_points = oc_grid->lidar_scan();

		synthesize_point_cloud(occupied_points);

		pc_publisher.publish(pcloud);
	}

void point_cloud::synthesize_point_cloud(vector<pair<int8_t,int8_t> > &occupied_points) {
	for(uint i=0; i<occupied_points.size(); i++) {
		cloud.points[i].x = occupied_points.at(i).first;
		cloud.points[i].y = occupied_points.at(i).second;
	}
}