#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    ROS_INFO_STREAM("Moving the rover toward the ball.");

    // Request linear and angular velocities.
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    // Call the DriveToTarget service and pass the requested velocities.
    if (!client.call(srv))
        ROS_ERROR("Failed to call service DriveToTarget");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
    int WHITE_PIXEL = 255;
    int STEP = 2;
    int LEFT_CENTER_LIMIT = (int)(img.step / 3) ;
    int RIGHT_CENTER_LIMIT = (int)(img.step / 3) * 2;
    bool isBallFound = false;

    // Identify if the ball falls in the left, mid, or right side of the image
    for(int i = 0; i < img.height; i += STEP)
    {
        for(int j = 0; j < img.step; j += STEP)
        {
            if(static_cast<int>(img.data[(i * img.step) + j]) == WHITE_PIXEL)
            {
                if(j < LEFT_CENTER_LIMIT)
                {
                    drive_robot(0.0, 0.05 );
                }
                else if(j > RIGHT_CENTER_LIMIT)
                {
                    drive_robot(0.0, -0.05);
                }
                else
                {
                    drive_robot(0.05, 0.0);
                }

                isBallFound = true;
                break;
            }
        }

        if(isBallFound)
        {
            break;
        }
    }

    // Stop the robot, the ball was not been found.
    if(!isBallFound)
    {
        drive_robot(0.0, 0.0);
    }
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
