#include "include_files/include_files.h"

class ConfigTest : public cartographer_ros::testing::TestWithParam<const char*>{};

TEST_P(ConfigTest, ValidateNodeOptions) {
	EXPECT_NO_FATAL_FAILURE(
    {LoadOptions(cartographer_ros::ros::package::getPath("Mini_SLAM") +"/config_files",GetParam());}
    );
}

INSTANTIATE_TEST_CASE_P(ValidateAllNodeOptions, ConfigurationFilesTest,
                        ::testing::Values("2DLidar_SLAM.lua"));