#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/CommandTOL.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/RCIn.h>
#include <sensor_msgs/LaserScan.h>

int count;
int flag=1;
static double distances1;
static double distances2;
static double distances3;
static double distances4;
mavros_msgs::State current_state;
void LidarCallback(const sensor_msgs::LaserScan msg)
{
    distances1 = msg.ranges[0];//
    distances2 = msg.ranges[127];
    distances3 = msg.ranges[255];
    distances4 = msg.ranges[383];
//     ROS_INFO("前方测距：%f米",distances);
}
// double get_x_distance(const sensor_msgs::LaserScan msg)
// {
//         double fMiDist = msg.ranges[180];
//         return fMiDist;
// }
void state_cb(const mavros_msgs::State::ConstPtr& msg){
    current_state = *msg;
}

mavros_msgs::RCIn rc;
int rc_value;
void rc_cb(const mavros_msgs::RCIn::ConstPtr& msg)//遥控器通道值回调函数
        {
                rc=*msg;
                rc_value=rc.channels[4]; //订阅第五通道
        }


int main(int argc, char **argv)
{
    ros::init(argc, argv, "offboard");

    ros::NodeHandle nh;
    setlocale(LC_ALL,"");//设置中文

    ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>
            ("/iris_0/mavros/state", 10, state_cb);
    ros::Publisher local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>
            ("/iris_0/mavros/setpoint_position/local", 10);
    ros::ServiceClient arming_client = nh.serviceClient<mavros_msgs::CommandBool>
            ("/iris_0/mavros/cmd/arming");
    ros::ServiceClient set_mode_client = nh.serviceClient<mavros_msgs::SetMode>
            ("/iris_0/mavros/set_mode");
    ros::ServiceClient land_client = nh.serviceClient<mavros_msgs::CommandTOL>
            ("/iris_0/mavros/cmd/land");
//     ros::ServiceClient land_client = nh.serviceClient<mavros_msgs::CommandTOL>
//             ("iris_0/mavros/cmd/land");
    ros::Subscriber rc_sub=nh.subscribe<mavros_msgs::RCIn>
            ("/iris_0/mavros/rc/in",10,rc_cb);//订阅遥控器通道pwm
    ros::Subscriber lidar_sub=nh.subscribe("/iris_0/scan",10,&LidarCallback);//订阅距离信息
    //the setpoint publishing rate MUST be faster than 2Hz
    ros::Rate rate(8.0);

    // wait for FCU connection
    while(ros::ok() && !current_state.connected){
        ros::spinOnce();
        rate.sleep();
    }
    geometry_msgs::PoseStamped pose;
    pose.pose.position.x = 0;
    pose.pose.position.y = 0;
    pose.pose.position.z = 0.8;
   
    //send a few setpoints before starting
    for(int i = 100; ros::ok() && i > 0; --i){
        local_pos_pub.publish(pose);
        ros::spinOnce();
        rate.sleep();
    }

    mavros_msgs::SetMode offb_set_mode;
    offb_set_mode.request.custom_mode = "OFFBOARD";

    mavros_msgs::CommandBool arm_cmd;
    arm_cmd.request.value = true;

    mavros_msgs::CommandTOL land_cmd;
    land_cmd.request.yaw = 0;
    land_cmd.request.latitude = 0;
    land_cmd.request.longitude = 0;
    land_cmd.request.altitude = 0;

    ros::Time last_request = ros::Time::now();
//     while(ros::ok())    
    while(ros::ok())
   {
		
	if( current_state.mode != "OFFBOARD" &&
            (ros::Time::now() - last_request > ros::Duration(5.0))){
            if( set_mode_client.call(offb_set_mode) &&
                offb_set_mode.response.mode_sent){
                ROS_INFO("Offboard enabled");
            }
            last_request = ros::Time::now();
        } else {
            if( !current_state.armed &&
                (ros::Time::now() - last_request > ros::Duration(5.0))){
                if( arming_client.call(arm_cmd) &&
                    arm_cmd.response.success){
                    ROS_INFO("Vehicle armed");
                }
                last_request = ros::Time::now();
            }
        }
		
            if((flag == 1)  && (ros::Time::now() - last_request > ros::Duration(5.0)))
		{ 
			ROS_INFO("position1(0 , 0,  0.8)");
                	pose.pose.position.x = 0;
    			pose.pose.position.y = 0;
    			pose.pose.position.z = 0.8;
			last_request = ros::Time::now();
                        ROS_INFO("distances[0]：%f米",distances1);
                        ROS_INFO("distances[90]：%f米",distances2);
                        ROS_INFO("distances[180]：%f米",distances3);
                        ROS_INFO("distances[270]：%f米",distances4);
                        flag=2;
			//local_pos_pub.publish(pose);

                }

		if((flag ==2) && (ros::Time::now() - last_request > ros::Duration(5.0)))
		{
			ROS_INFO("position2(3.3 , 0, 0.8)");
                	pose.pose.position.x = 3.3;
    			pose.pose.position.y = 0;
    			pose.pose.position.z = 0.8;
			last_request = ros::Time::now();
                        ROS_INFO("distances[0]：%f米",distances1);
                        ROS_INFO("distances[90]：%f米",distances2);
                        ROS_INFO("distances[180]：%f米",distances3);
                        ROS_INFO("distances[270]：%f米",distances4);
			flag=3;
			//local_pos_pub.publish(pose);
                }
                       
		 if((flag ==3) && (ros::Time::now() - last_request > ros::Duration(5.0)))
                {
                        ROS_INFO("position3(3.3 ,0.8,  0.8)");
                        pose.pose.position.x = 3.3;
                        pose.pose.position.y = 0.8;
                        pose.pose.position.z = 0.8;
                        last_request = ros::Time::now();
                        ROS_INFO("distances[0]：%f米",distances1);
                        ROS_INFO("distances[90]：%f米",distances2);
                        ROS_INFO("distances[180]：%f米",distances3);
                        ROS_INFO("distances[270]：%f米",distances4);
			flag=4;
                        //local_pos_pub.publish(pose);
                }

		 if((flag ==4) && (ros::Time::now() - last_request > ros::Duration(5.0)))
                {
                        ROS_INFO("position4(4.5 , 0.8,  0.8)");
                        pose.pose.position.x = 4.5;
                        pose.pose.position.y = 0.8;
                        pose.pose.position.z = 0.8;
                        last_request = ros::Time::now();
                        ROS_INFO("distances[0]：%f米",distances1);
                        ROS_INFO("distances[90]：%f米",distances2);
                        ROS_INFO("distances[180]：%f米",distances3);
                        ROS_INFO("distances[270]：%f米",distances4);
			flag=5;
                        //local_pos_pub.publish(pose);
                }
                 if((flag ==5) && (ros::Time::now() - last_request > ros::Duration(5.0)))
                {
                        ROS_INFO("position5(5.3 , 0.8,  0.8)");
                        pose.pose.position.x = 5.3;
                        pose.pose.position.y = 0.8;
                        pose.pose.position.z = 0.8;
                        last_request = ros::Time::now();
                        ROS_INFO("distances[0]：%f米",distances1);
                        ROS_INFO("distances[90]：%f米",distances2);
                        ROS_INFO("distances[180]：%f米",distances3);
                        ROS_INFO("distances[270]：%f米",distances4);
			flag=6;
                        //local_pos_pub.publish(pose);
                }
                if((flag ==6) && (ros::Time::now() - last_request > ros::Duration(5.0)))
                {
                        ROS_INFO("position6(5.3 , -0.9,  0.8)");
                        pose.pose.position.x = 5.3;
                        pose.pose.position.y = -0.9;
                        pose.pose.position.z = 0.8;
                        last_request = ros::Time::now();
                        ROS_INFO("distances[0]：%f米",distances1);
                        ROS_INFO("distances[90]：%f米",distances2);
                        ROS_INFO("distances[180]：%f米",distances3);
                        ROS_INFO("distances[270]：%f米",distances4);
			flag=7;
                        //local_pos_pub.publish(pose);
                }
                while((flag ==7) && (ros::Time::now() - last_request > ros::Duration(5.0))&& distances3 < 3.5)
                {
                        ROS_INFO("向前移动0.2，寻找窗口");
                        // ROS_INFO("distances[0]：%f米",distances1);
                        // ROS_INFO("distances[90]：%f米",distances2);
                        // ROS_INFO("distances[180]：%f米",distances3);
                        // ROS_INFO("distances[270]：%f米",distances4);
                        pose.pose.position.x = pose.pose.position.x;
                        pose.pose.position.y += 0.2;
                        pose.pose.position.z = pose.pose.position.z;
                        last_request = ros::Time::now();
			// flag=8;
                        //local_pos_pub.publish(pose);
                }
                if((flag ==7) && (ros::Time::now() - last_request > ros::Duration(5.0))&& distances3> 3.5)
                {
                        // ROS_INFO("distances[0]：%f米",distances1);
                        // ROS_INFO("distances[90]：%f米",distances2);
                        // ROS_INFO("distances[180]：%f米",distances3);
                        // ROS_INFO("distances[270]：%f米",distances4);
                        ROS_INFO("找到了，向前移动0.35");
                        pose.pose.position.x = pose.pose.position.x;
                        pose.pose.position.y += 0.35;
                        pose.pose.position.z = pose.pose.position.z;
                        last_request = ros::Time::now();
                        flag=8;
                }
                while((flag == 8)  && (ros::Time::now() - last_request > ros::Duration(5.0))&&distances2>0.5)
		{ 
			ROS_INFO("未到达窗口，向前移动：0.2");
                        pose.pose.position.x += 0.2;
                        pose.pose.position.y = pose.pose.position.y;
                        pose.pose.position.z = pose.pose.position.z;
                        last_request = ros::Time::now();
                        // ROS_INFO("distances[0]：%f米",distances1);
                        // ROS_INFO("distances[90]：%f米",distances2);
                        // ROS_INFO("distances[180]：%f米",distances3);
                        // ROS_INFO("distances[270]：%f米",distances4);
			// flag=10;
                        //local_pos_pub.publish(pose);
			//local_pos_pub.publish(pose);

                }
                if((flag == 8)  && (ros::Time::now() - last_request > ros::Duration(5.0))&& distances2<0.5)
		{ 
			ROS_INFO("现在处于窗口，向前移动0.4");
                        pose.pose.position.x += 0.4;
                        pose.pose.position.y = pose.pose.position.y;
                        pose.pose.position.z = pose.pose.position.z;
                        last_request = ros::Time::now();
                        // ROS_INFO("distances[0]：%f米",distances1);
                        // ROS_INFO("distances[90]：%f米",distances2);
                        // ROS_INFO("distances[180]：%f米",distances3);
                        // ROS_INFO("distances[270]：%f米",distances4);
                        //local_pos_pub.publish(pose);
			//local_pos_pub.publish(pose);
                        flag=9;
                }
                while((flag == 9)  && (ros::Time::now() - last_request > ros::Duration(5.0))&& distances2<1.5)
		{ 
			ROS_INFO("找第一个门，再向前移动0.2");
                        pose.pose.position.x += 0.2;
                        pose.pose.position.y = pose.pose.position.y;
                        pose.pose.position.z = pose.pose.position.z;
                        last_request = ros::Time::now();
                        // ROS_INFO("distances[0]：%f米",distances1);
                        // ROS_INFO("distances[90]：%f米",distances2);
                        // ROS_INFO("distances[180]：%f米",distances3);
                        // ROS_INFO("distances[270]：%f米",distances4);
                        //local_pos_pub.publish(pose);
			//local_pos_pub.publish(pose);
                        flag=9;
                }
                if((flag == 9)  && (ros::Time::now() - last_request > ros::Duration(5.0))&& distances2>1.5)
		{ 
			ROS_INFO("找到了第一个门，向前移动0.35");
                        pose.pose.position.x = pose.pose.position.x;
                        pose.pose.position.y += 0.35;
                        pose.pose.position.z = pose.pose.position.z;
                        last_request = ros::Time::now();
                        // ROS_INFO("distances[0]：%f米",distances1);
                        // ROS_INFO("distances[90]：%f米",distances2);
                        // ROS_INFO("distances[180]：%f米",distances3);
                        // ROS_INFO("distances[270]：%f米",distances4);
                        //local_pos_pub.publish(pose);
			//local_pos_pub.publish(pose);
                        // flag=9;
                }
                if((flag == 9)  && (ros::Time::now() - last_request > ros::Duration(5.0))&& distances1<0.35)
		{ 
			ROS_INFO("第一个门找到了，向前移动0.35");
                        pose.pose.position.x = pose.pose.position.x;
                        pose.pose.position.y += 0.35;
                        pose.pose.position.z = pose.pose.position.z;
                        last_request = ros::Time::now();
                        // ROS_INFO("distances[0]：%f米",distances1);
                        // ROS_INFO("distances[90]：%f米",distances2);
                        // ROS_INFO("distances[180]：%f米",distances3);
                        // ROS_INFO("distances[270]：%f米",distances4);
                        //local_pos_pub.publish(pose);
			//local_pos_pub.publish(pose);
                        flag=10;
                }
                 if((flag==10) && (ros::Time::now() - last_request > ros::Duration(5.0)))
                {
                        break;

                }

		// if((flag ==6) && (ros::Time::now() - last_request > ros::Duration(5.0)))
		// {
		// 	ROS_INFO("position2(2.5 , 4.33,  8)");
                // 	pose.pose.position.x = 2.5;
    		// 	pose.pose.position.y = 4.33;
    		// 	pose.pose.position.z = 8;
		// 	last_request = ros::Time::now();
		// 	flag=7;
		// 	//local_pos_pub.publish(pose);
                // }
                       
		//  if((flag ==7) && (ros::Time::now() - last_request > ros::Duration(5.0)))
                // {
                //         ROS_INFO("position3(5 , 0,  8)");
                //         pose.pose.position.x = 5.0;
                //         pose.pose.position.y = 0.0;
                //         pose.pose.position.z = 8;
                //         last_request = ros::Time::now();
		// 	flag=8;
                //         //local_pos_pub.publish(pose);
                // }

		//  if((flag ==8) && (ros::Time::now() - last_request > ros::Duration(5.0)))
                // {
                //         ROS_INFO("position4(0 , 0,  5)");
                //         pose.pose.position.x = 0.0;
                //         pose.pose.position.y = 0.0;
                //         pose.pose.position.z = 8;
                //         last_request = ros::Time::now();
		// 	flag=9;
                //         //local_pos_pub.publish(pose);
                // }

		//  if((flag ==5) && (ros::Time::now() - last_request > ros::Duration(5.0)))
                // {
                //         ROS_INFO("position5(0 ,0,  5)");
                //         pose.pose.position.x = 0;
                //         pose.pose.position.y = 0;
                //         pose.pose.position.z = 5;
                //         last_request = ros::Time::now();
		// 	flag=6;
                //         //local_pos_pub.publish(pose);
                // }
        local_pos_pub.publish(pose);
        ros::spinOnce();
        rate.sleep();
    }
        while (ros::ok())
        {
                ROS_INFO("tring to land");
                while (!(land_client.call(land_cmd) &&
                land_cmd.response.success))
                {
                        //local_pos_pub.publish(pose);
                        ROS_INFO("tring to land");
                        ros::spinOnce();
                        rate.sleep(); 
                }
        }
        
        

    return 0;
}



