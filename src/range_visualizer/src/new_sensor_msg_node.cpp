#include "ros/ros.h"
/*#include "std_msgs/String.h"*/
#include "sensor_msgs/Range.h"


int main(int argc, char **argv)
{
	ros::init(argc, argv,"new_sensor_msg_node");
	ros::NodeHandle n;
	ros::Publisher chatter_pub = n.advertise<sensor_msgs::Range>("sensor",1000);
	ros::Rate loop_rate(10);

	sensor_msgs::Range msg;		
	std_msgs::Header header;

	msg.header.frame_id= "sensor_range";
	msg.field_of_view = 0.785;
	msg.min_range = 0.02;
	msg.max_range = 4;
	
	int count = 0;
	while (ros::ok())
	{
				
		msg.range = 4*((float)(rand())/(RAND_MAX));			
		
		ROS_INFO("%f", msg.range);

		chatter_pub.publish(msg);
		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
}
