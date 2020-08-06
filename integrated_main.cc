#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>
#include <gazebo/gazebo.hh>
#include <gazebo/common/common.hh>
#include <gazebo/physics/physics.hh>

#include <iostream>


// Function is called every time a message is received.
void posesStampedCallback(ConstPosesStampedPtr &posesStamped)
{
  std::cout << posesStamped->DebugString();

  ::google::protobuf::int32 sec = posesStamped->time().sec();
  ::google::protobuf::int32 nsec = posesStamped->time().nsec();
  std::cout << "Read time: sec: " << sec << " nsec: " << nsec << std::endl;

  for (int i =0; i < posesStamped->pose_size(); ++i)
  {
    const ::gazebo::msgs::Pose &pose = posesStamped->pose(i);
    std::string name = pose.name();
    if (name == std::string("box"))
    {
      const ::gazebo::msgs::Vector3d &position = pose.position();

      double x = position.x();
      double y = position.y();
      double z = position.z();

      std::cout << "Read position: x: " << x
          << " y: " << y << " z: " << z << std::endl;
    }
  }
}


int main(int _argc, char **_argv)
{
  std::string str = "animated_box.world";
  if (_argc > 1)
  {
    str = _argv[1];
  }

  try
  {
    // load gazebo server
    gazebo::setupServer(_argc, _argv);

    // Load a world
    gazebo::physics::WorldPtr world = gazebo::loadWorld(str);

    // Create our node for communication
    gazebo::transport::NodePtr node(new gazebo::transport::Node());
    node->Init();

    // Listen to Gazebo pose information topic
    gazebo::transport::SubscriberPtr sub =
    node->Subscribe("~/pose/info", posesStampedCallback);

    // Busy wait loop...replace with your own code as needed.
    while (true)
    {
      // Run simulation for 100 steps.
      gazebo::runWorld(world, 100);
    }

    // Make sure to shut everything down.
    gazebo::shutdown();
  }
  catch(gazebo::common::Exception &e)
  {
    std::cerr << "ERROR: " << e << std::endl;
    return 1;
  }

  return 0;
}
