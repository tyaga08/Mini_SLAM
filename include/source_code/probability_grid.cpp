#include "include_files/include_files.h"

class probability_grid {
private:
	pcl::PointCloud<pcl::PointXY> lidar_pc;
	shared_ptr<cartographer::mapping::ProbabilityGrid> bin_prob_grid;
	Eigen::Array2i cell_idx;


public:

	probability_grid() {
		bin_prob_grid = shared_ptr<cartographer::mapping::ProbabilityGrid> (new cartographer::mapping::ProbabilityGrid(cartographer::mapping::MapLimits(1., {10,10}, cartographer::mapping::CellLimits(10,10))));
	}

	~probability_grid() {}

	void cloud_callback(const sensor_msgs::PointCloud2::ConstPtr& msg);

	void assign_grid_probability();
	
};

void probability_grid::cloud_callback(const sensor_msgs::PointCloud2::ConstPtr& msg) {
	sensor_msgs::PointCloud2 lidar_pc2 = *msg;
	
	pcl::fromROSMsg(lidar_pc2, lidar_pc);

	cout<<"points received"<<endl;
	for(uint i=0; i<lidar_pc.size(); i++) {
		cout<<lidar_pc[i].x<<","<<lidar_pc[i].y<<endl;
	}

	probability_grid::assign_grid_probability();
}

void probability_grid::assign_grid_probability() {
	// get the current pose before filling the probability grid
	for(uint i=0; i<lidar_pc.size(); i++) {
		cell_idx = Eigen::Array2i(i/10,i%10);
		// cell_idx = Eigen::Array2i(lidar_pc[i].x, lidar_pc[i].y);
		cout<<bin_prob_grid->GetProbability(cell_idx)<<endl;
		bin_prob_grid->SetProbability(cell_idx,1.);
		cout<<"here"<<endl;
	}



}