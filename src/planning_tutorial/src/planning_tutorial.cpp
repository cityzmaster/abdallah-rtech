#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_visual_tools/moveit_visual_tools.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "planning_tutorial");
  ros::NodeHandle node_handle;
  ros::AsyncSpinner spinner(1);
  spinner.start();
  static const std::string PLANNING_GROUP = "first_manipulator";
  static const std::string PLANNING_GROUP1 = "second_manipulator";
  moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);
  moveit::planning_interface::MoveGroupInterface move_group1(PLANNING_GROUP1);

  geometry_msgs::Pose target_pose = move_group.getCurrentPose().pose;  
  geometry_msgs::Pose target_pose1 = move_group1.getCurrentPose().pose; 

  target_pose.position.z -= 0.2;
  move_group.setPoseTarget(target_pose);
  move_group.move();
  target_pose.position.x -= 0.2;
  move_group.setPoseTarget(target_pose);
  move_group.move();
  target_pose.position.z += 0.2;
  target_pose.position.x += 0.2;
  move_group.setPoseTarget(target_pose);
  move_group.move();
  
  target_pose1.position.z -= 0.2;
  move_group1.setPoseTarget(target_pose1);
  move_group1.move();
  target_pose1.position.x += 0.2;
  move_group1.setPoseTarget(target_pose1);
  move_group1.move();
  target_pose1.position.z += 0.2;
  target_pose1.position.x -= 0.2;
  move_group1.setPoseTarget(target_pose1);
  move_group1.move();
  

  ros::shutdown();
  return 0;
}
