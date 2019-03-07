###Mini_SLAM  
  
  
This package is a small project on SLAM  
  
  
  
To run this project, source your catkin_ws first.  
  
#To clone the package  
git clone https://github.com/tyaga08/Mini_SLAM.git  

#To build  
cd catkin_ws  
catkin_make  
  
#To run open 3 terminals  
roslaunch Mini_SLAM cartographer.launch  
roslaunch Mini_SLAM node1.launch  
rosrun Mini_SLAM write_to_file_server  
  
#To write the map to file  
rosservice call /write_to_file