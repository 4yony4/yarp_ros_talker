#include <yarp/os/LogComponent.h>
#include <yarp/os/LogStream.h>
#include <yarp/os/Network.h>
#include <yarp/os/Node.h>
#include <yarp/os/Publisher.h>
#include <yarp/os/Time.h>
 
//#include <yarp/rosmsg/std_msgs/String.h>
#include <yarp/rosmsg/Yarpinfo.h>
 
using yarp::os::Network;
using yarp::os::Node;
using yarp::os::Publisher;
 
namespace {
YARP_LOG_COMPONENT(TALKER, "yarp.example.ros.talker")
constexpr double loop_delay = 0.1;
}
 
int main(int argc, char* argv[])
{
    YARP_UNUSED(argc);
    YARP_UNUSED(argv);
 
    Network yarp;
 
    /* creates a node called /yarp/talker */
    Node node("/yarp/talker");
 
    /* subscribe to topic chatter */
    yarp::os::Publisher<yarp::rosmsg::Yarpinfo> publisher;
    if (!publisher.topic("yarpinfo")) {
        yCError(TALKER) << "Failed to create publisher to yarpinfo";
        return -1;
    }
 
    while (true) {
        /* prepare some data */
        yarp::rosmsg::Yarpinfo data;
        data.msg = "Hello from YARP PASSING THROUGH YARPSERVER <---> ROS-YARP-BRIDGE <---> ROS1-ROS2-BRIDGE <----> ROS2";
 
        /* publish it to the topic */
        publisher.write(data);
 
        /* wait some time to avoid flooding with messages */
        yarp::os::Time::delay(loop_delay);
    }
 
    return 0;
}