#include "include_files/include_files.h"

class occupancy_grid {
private:
	pair<int8_t,int8_t> bot_start_point;
	pair<int8_t,int8_t> bot_curr_pos;
	int16_t bot_curr_ori;
	vector<pair<int8_t,int8_t> > lidar_point_cloud;

	vector<int8_t> lidar_sense = vector<int8_t>(14);

public:
	nav_msgs::OccupancyGrid grid;

	occupancy_grid() {
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


		bot_start_point = pair<int8_t,int8_t>(9,7);
		bot_curr_pos = bot_start_point;
		bot_curr_ori = 0;

	}

	~occupancy_grid() {}

	pair<int8_t,int8_t> navigate_robot(string signal);

	inline int8_t conv_coordinates_to_arrindex(pair<int8_t,int8_t> inp_point);

	inline pair<int8_t,int8_t> conv_arrindex_to_coordinates(int8_t inp_index);

	vector<pair<int8_t,int8_t> > lidar_scan();

};


pair<int8_t,int8_t> occupancy_grid::navigate_robot(string signal) {

	if(signal=="forward") {
		if(bot_curr_ori==0) {
			bot_curr_pos.first -= 1;
		}

		else if(bot_curr_ori==180) {
			bot_curr_pos.first += 1;
		}

		else if(bot_curr_ori==90) {
			bot_curr_pos.second -= 1;
		}

		else if(bot_curr_ori==270) {
			bot_curr_pos.second +=1;
		}
	}
	
	else if(signal=="left") {
		if(bot_curr_ori==0) {
			bot_curr_ori = 90;
		}

		else if(bot_curr_ori==90) {
			bot_curr_ori = 180;
		}

		else if(bot_curr_ori==180) {
			bot_curr_ori = 270;
		}

		else if(bot_curr_ori==270) {
			bot_curr_ori = 0;
		}	
	}

	return bot_curr_pos;
}

vector<pair<int8_t,int8_t> > occupancy_grid::lidar_scan() {

	int8_t curr_index = occupancy_grid::conv_coordinates_to_arrindex(bot_curr_pos);

	// Calculating the 1's and 0's in the occupancy grid in order nearest to farthest and left to right w.r.t the robot (BFS) and storing it in vector
	if(bot_curr_ori==0) {
		lidar_sense = {grid.data[curr_index-1], grid.data[curr_index-11], grid.data[curr_index-10], grid.data[curr_index-9], grid.data[curr_index+1], grid.data[curr_index-2], grid.data[curr_index-12], grid.data[curr_index-22], grid.data[curr_index-21], grid.data[curr_index-20], grid.data[curr_index-19], grid.data[curr_index-18], grid.data[curr_index-8], grid.data[curr_index+2]};
	}

	else if(bot_curr_ori==90) {
		lidar_sense = {grid.data[curr_index+10], grid.data[curr_index+9], grid.data[curr_index-1], grid.data[curr_index-11], grid.data[curr_index-10], grid.data[curr_index+20], grid.data[curr_index+19], grid.data[curr_index+18], grid.data[curr_index+8], grid.data[curr_index-2], grid.data[curr_index-12], grid.data[curr_index-22], grid.data[curr_index-21], grid.data[curr_index-20]};
	}

	else if(bot_curr_ori==180) {
		lidar_sense = {grid.data[curr_index+1], grid.data[curr_index+11], grid.data[curr_index+10], grid.data[curr_index+9], grid.data[curr_index-1], grid.data[curr_index+2], grid.data[curr_index+12], grid.data[curr_index+22], grid.data[curr_index+21], grid.data[curr_index+20], grid.data[curr_index+19], grid.data[curr_index+18], grid.data[curr_index+8], grid.data[curr_index-2]};
	}

	else if(bot_curr_ori==270) {
		lidar_sense = {grid.data[curr_index-10], grid.data[curr_index-9], grid.data[curr_index+1], grid.data[curr_index+11], grid.data[curr_index+10], grid.data[curr_index-20], grid.data[curr_index-19], grid.data[curr_index-18], grid.data[curr_index-8], grid.data[curr_index+2], grid.data[curr_index+12], grid.data[curr_index+22], grid.data[curr_index+21], grid.data[curr_index+20]};
	}


	// Using the above vector to generate the point cloud

	vector<pair<int8_t, int8_t> > temp_cloud;
	if(lidar_sense.at(0))
		temp_cloud.push_back(pair<int8_t,int8_t>(0,1));

	else if(lidar_sense.at(5))
		temp_cloud.push_back(pair<int8_t,int8_t>(0,2));

	if(lidar_sense.at(1))
		temp_cloud.push_back(pair<int8_t,int8_t>(1,1));
	
	else if(lidar_sense.at(7))
		temp_cloud.push_back(pair<int8_t,int8_t>(2,2));

	if(lidar_sense.at(2))
		temp_cloud.push_back(pair<int8_t,int8_t>(1,0));

	else if(lidar_sense.at(9))
		temp_cloud.push_back(pair<int8_t,int8_t>(2,0));

	if(lidar_sense.at(3))
		temp_cloud.push_back(pair<int8_t,int8_t>(1,-1));

	else if(lidar_sense.at(11))
		temp_cloud.push_back(pair<int8_t,int8_t>(2,-2));

	if(lidar_sense.at(4))
		temp_cloud.push_back(pair<int8_t,int8_t>(0,-1));

	else if(lidar_sense.at(13))
		temp_cloud.push_back(pair<int8_t,int8_t>(0,-2));

	if(lidar_sense.at(6)==1 && (lidar_sense.at(0)+lidar_sense.at(1))==0)
		temp_cloud.push_back(pair<int8_t,int8_t>(1,2));

	if(lidar_sense.at(8)==1 && (lidar_sense.at(1)+lidar_sense.at(2))==0)
		temp_cloud.push_back(pair<int8_t,int8_t>(2,1));

	if(lidar_sense.at(10)==1 && (lidar_sense.at(2)+lidar_sense.at(3))==0)
		temp_cloud.push_back(pair<int8_t,int8_t>(2,-1));

	if(lidar_sense.at(12)==1 && (lidar_sense.at(3)+lidar_sense.at(4))==0)
		temp_cloud.push_back(pair<int8_t,int8_t>(1,-2));

	lidar_point_cloud = temp_cloud;
	return lidar_point_cloud;
}

inline int8_t occupancy_grid::conv_coordinates_to_arrindex(pair<int8_t,int8_t> inp_point) {
	return (inp_point.first*10 + inp_point.second);
}

inline pair<int8_t,int8_t> occupancy_grid::conv_arrindex_to_coordinates(int8_t inp_index) {
	return pair<int8_t,int8_t> (inp_index/10, inp_index%10);
}