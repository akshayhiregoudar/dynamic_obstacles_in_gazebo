#include <boost/bind.hpp>
#include <gazebo/gazebo.hh>
#include <ignition/math.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <stdio.h>


namespace gazebo
{
  class AnimatedBox4 : public ModelPlugin
  {
    public: void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
    {
      // Store the pointer to the model
      this->model = _parent;

        // create the animation
        gazebo::common::PoseAnimationPtr anim(
              // name the animation "test",
              // make it last 8 seconds,
              // and set it on a repeat loop
              new gazebo::common::PoseAnimation("test", 8.0, true));

        gazebo::common::PoseKeyFrame *key;

        // set starting location of the box
        key = anim->CreateKeyFrame(0);
        key->Translation(ignition::math::Vector3d(-4.5, -8, 0));
        key->Rotation(ignition::math::Quaterniond(0, 0, 0));

        // set waypoint location after 2 seconds
        key = anim->CreateKeyFrame(2.0);
        key->Translation(ignition::math::Vector3d(-3.5, -5, 0));
        key->Rotation(ignition::math::Quaterniond(0, 0, 0));


        key = anim->CreateKeyFrame(4.0);
        key->Translation(ignition::math::Vector3d(-4, -1, 0));
        key->Rotation(ignition::math::Quaterniond(0, 0, 0));


        key = anim->CreateKeyFrame(6.0);
        key->Translation(ignition::math::Vector3d(-3, -5.5, 0));
        key->Rotation(ignition::math::Quaterniond(0, 0, 0));


        key = anim->CreateKeyFrame(8.0);
        key->Translation(ignition::math::Vector3d(-4.5, -8, 0));
        key->Rotation(ignition::math::Quaterniond(0, 0, 0));

   

        // set the animation
        _parent->SetAnimation(anim);
    }

    // Pointer to the model
    private: physics::ModelPtr model;

    // Pointer to the update event connection
    private: event::ConnectionPtr updateConnection;
  };

  // Register this plugin with the simulator
  GZ_REGISTER_MODEL_PLUGIN(AnimatedBox4)
}
