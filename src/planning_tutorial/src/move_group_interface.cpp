#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

#include <moveit_visual_tools/moveit_visual_tools.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "move_group_interface");
  ros::NodeHandle node_handle;
  ros::AsyncSpinner spinner(1);
  spinner.start();

  
  // MoveIt! operates on sets of joints called "planning groups" and stores them in an object called
  // the `JointModelGroup`. Throughout MoveIt! the terms "planning group" and "joint model group"
  // are used interchangably.
  static const std::string PLANNING_GROUP = "first_manipulator";
  static const std::string PLANNING_GROUP1 = "second_manipulator";

  // The :move_group_interface:`MoveGroup` class can be easily
  // setup using just the name of the planning group you would like to control and plan for.
  moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);
  moveit::planning_interface::MoveGroupInterface move_group1(PLANNING_GROUP1);
  // Now, we call the planner to compute the plan and visualize it. Note that we are just planning, not asking move_group to actually move the robot.
  moveit::planning_interface::MoveGroupInterface::Plan my_plan;
  moveit::planning_interface::MoveGroupInterface::Plan my_plan1;

  // Cartesian Paths
  // ^^^^^^^^^^^^^^^
  // You can plan a Cartesian path directly by specifying a list of waypoints
  // for the end-effector to go through. Note that we are starting
  // from the new start state above.  The initial pose (start state) does not
  // need to be added to the waypoint list but adding it can help with visualizations
  geometry_msgs::Pose target_pose = move_group.getCurrentPose().pose;
  geometry_msgs::Pose target_pose1 = move_group1.getCurrentPose().pose;

  std::vector<geometry_msgs::Pose> waypoints;
  std::vector<geometry_msgs::Pose> waypoints1;
  waypoints.push_back(target_pose);
  waypoints1.push_back(target_pose1);

  target_pose.position.z -= 0.2;
  waypoints.push_back(target_pose);  // down

  target_pose.position.x -= 0.2;
  waypoints.push_back(target_pose);  // right

  target_pose.position.z += 0.2;
  target_pose.position.x += 0.2;
  waypoints.push_back(target_pose);  // up and left

  target_pose1.position.z -= 0.2;
  waypoints1.push_back(target_pose1);  // down

  target_pose1.position.x -= 0.2;
  waypoints1.push_back(target_pose1);  // right

  target_pose1.position.z += 0.2;
  target_pose1.position.x += 0.2;
  waypoints1.push_back(target_pose1);  // up and left
  moveit_msgs::RobotTrajectory trajectory;
  moveit_msgs::RobotTrajectory trajectory1;
  const double jump_threshold = 0.0;
  const double eef_step = 0.01;
  double fraction = move_group.computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);
  double fraction1 = move_group1.computeCartesianPath(waypoints1, eef_step, jump_threshold, trajectory1);
  my_plan.trajectory_=trajectory;
  my_plan1.trajectory_=trajectory1;
  move_group.execute(my_plan);
  move_group1.execute(my_plan1);

    
  ros::shutdown();
  return 0;
}
