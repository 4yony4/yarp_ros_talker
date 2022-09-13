#include <yarp/rosmsg/Debug.h>
#include <iostream>
#include <yarp/os/Network.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/Time.h>
 
int main()
{
    yarp::os::Network network;
 
    yarp::os::Port port;
 
    if (!port.open("/chatter"))
    {
        std::cerr<<"Error opening port, check your yarp network\n";
        return -1;
    }
 
    std::cout<<"Starting chatter\n";
    double count=0.0;
    while(true)
    {
        yarp::rosmsg::Debug d;
 
        // d.text is a string
        d.msg="Hello from chatter";
 
        //d.content is a vector, let's push some data
        //d.content.push_back(count++);
        //d.content.push_back(count++);
 
        port.write(d);
 
        yarp::os::Time::delay(0.1);
    }
 
    return 0;
}