include "map_builder.lua"
include "trajectory_builder.lua"

options = {
	map_builder = MAP_BUILDER,
	trajectory_builder = TRAJECTORY_BUILDER,
	map_frame = "map",
	tracking_frame = "2D_Lidar_link",
	published_frame = "2D_Lidar_link",
	odom_frame = "odom",
	provide_odom_frame = false,
	publish_frame_projected_to_2d = true,
	use_odometry = false,
	use_nav_sat = false,
	use_landmarks = false,
	num_laser_scans = 0,
	num_multi_echo_laser_scans = 0,
	num_subdivisions_per_laser_scan = 1,
	num_point_clouds = 1,
	lookup_transform_timeout_sec = 1,
	submap_publish_period_sec = 1,
	pose_publish_period_sec = 0.5,
	trajectory_publish_period_sec = 0.5,
	rangefinder_sampling_ratio = 1.,
	odometry_sampling_ratio = 1.,
	fixed_frame_pose_sampling_ratio = 1.,
	imu_sampling_ratio = 1.,
	landmarks_sampling_ratio = 1.,
}

MAP_BUILDER.use_trajectory_builder_2d = true


TRAJECTORY_BUILDER_2D.use_imu_data = false
TRAJECTORY_BUILDER_2D.min_range = 0
TRAJECTORY_BUILDER_2D.max_range = 5
TRAJECTORY_BUILDER_2D.missing_data_ray_length = 0
TRAJECTORY_BUILDER_3D.num_accumulated_range_data = 10

TRAJECTORY_BUILDER_2D.use_online_correlative_scan_matching = true
TRAJECTORY_BUILDER_2D.real_time_correlative_scan_matcher.linear_search_window = 0
-- TRAJECTORY_BUILDER_2D.real_time_correlative_scan_matcher.angular_search_window = math.rad(90.)
-- TRAJECTORY_BUILDER_2D.submaps.resolution = 0.1

-- cartographer.mapping.pose_graph.proto.max_constraint.distance = 4

TRAJECTORY_BUILDER_2D.motion_filter.max_time_seconds = 0.5
TRAJECTORY_BUILDER_2D.motion_filter.max_distance_meters = 1
TRAJECTORY_BUILDER_2D.motion_filter.max_angle_radians = math.rad(0.01)

TRAJECTORY_BUILDER_2D.submaps.grid_options_2d.grid_type = "PROBABILITY_GRID"
TRAJECTORY_BUILDER_2D.submaps.grid_options_2d.resolution = 1
TRAJECTORY_BUILDER_2D.submaps.range_data_inserter.range_data_inserter_type = "PROBABILITY_GRID_INSERTER_2D"
TRAJECTORY_BUILDER_2D.submaps.range_data_inserter.probability_grid_range_data_inserter.insert_free_space = true
TRAJECTORY_BUILDER_2D.submaps.range_data_inserter.probability_grid_range_data_inserter.hit_probability = 1
TRAJECTORY_BUILDER_2D.submaps.range_data_inserter.probability_grid_range_data_inserter.miss_probability = 0

-- POSE_GRAPH.optimize_every_n_scans = 10
-- POSE_GRAPH.constraint_builder.min_score = 0.8

-- POSE_GRAPH.constraint_builder.min_score = 0.65
-- POSE_GRAPH.constraint_builder.global_localization_min_score = 0.7

return options