#include <yarp/os/LogComponent.h>
#include <yarp/os/LogStream.h>
#include <yarp/os/Network.h>
#include <yarp/os/Node.h>
#include <yarp/os/Publisher.h>
#include <yarp/os/Time.h>
 
//#include <yarp/rosmsg/std_msgs/String.h>
#include <yarp/rosmsg/Yarpinfo.h>
#include <yarp/rosmsg/Vjxoutput.h>
#include <vector>
 
using yarp::os::Network;
using yarp::os::Node;
using yarp::os::Publisher;
using std::vector;
 
namespace {
YARP_LOG_COMPONENT(TALKER, "yarp.example.ros.talker")
constexpr double loop_delay = 0.1;
}
 
int main(int argc, char* argv[])
{
    double t0, tnow; // timestamp variables

    YARP_UNUSED(argc);
    YARP_UNUSED(argv);
 
    Network yarp;
 
    /* creates a node called /yarp/talker */
    Node node("/yarp/talker");
 
    /* subscribe to topic chatter */
    yarp::os::Publisher<yarp::rosmsg::Vjxoutput> publisher;
    if (!publisher.topic("output2ros")) {
        yCError(TALKER) << "Failed to create publisher to yarpinfo";
        return -1;
    }
 
    while (true) {
        /* prepare some data */
        yarp::rosmsg::Vjxoutput ros_output;
        vector<double> sklt_out, vel_out;
        for (int j = 0; j < 13; j++)
        {
            sklt_out.push_back(rand() * 150.0 / RAND_MAX);
            sklt_out.push_back(rand() * 150.0 / RAND_MAX);
            vel_out.push_back(rand() * (300.0 / RAND_MAX) - 150);
            vel_out.push_back(rand() * (300.0 / RAND_MAX) - 150);
        }
        // // print to check what data is created - used to debug
        // std::cout << tnow << std::endl;
        // for(auto t : sklt_out)
        //     std::cout << t << ", ";
        // std::cout << std::endl;
        // for(auto t : vel_out)
        //     std::cout << t << ", ";
        // std::cout << std::endl;
        // std::cout << std::endl;

        // put data in ros output structure
        ros_output.timestamp = tnow;
        ros_output.pose = sklt_out;
        ros_output.velocity = vel_out;

        
        //data.msg = "Hello from YARP PASSING THROUGH YARPSERVER <---> ROS-YARP-BRIDGE <---> ROS1-ROS2-BRIDGE <----> ROS2";
 
        /* publish it to the topic */
        publisher.write(ros_output);
 
        /* wait some time to avoid flooding with messages */
        yarp::os::Time::delay(loop_delay);
    }
 
    return 0;
}