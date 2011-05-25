/*
 * Copyright (c) 2011, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "interactive_marker.h"

#include "interactive_marker_tools.h"

#include <visualization_msgs/InteractiveMarkerFeedback.h>

#include "rviz/frame_manager.h"
#include "rviz/visualization_manager.h"
#include "rviz/selection/selection_manager.h"
#include "rviz/frame_manager.h"
#include "rviz/default_plugin/interactive_marker_display.h"
#include "rviz/render_panel.h"

#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreMaterialManager.h>
#include <OGRE/OgreResourceGroupManager.h>
#include <OGRE/OgreSubEntity.h>
#include <OGRE/OgreMath.h>

#include <boost/make_shared.hpp>
#include <wx/menu.h>

#include <ros/ros.h>

namespace rviz
{

InteractiveMarker::InteractiveMarker( InteractiveMarkerDisplay *owner, VisualizationManager *vis_manager, std::string topic_ns ) :
  owner_(owner)
, vis_manager_(vis_manager)
, dragging_(false)
, pose_update_requested_(false)
, menu_(0)
, heart_beat_t_(0)
, topic_ns_(topic_ns)
{
  ros::NodeHandle nh;
  std::string feedback_topic = topic_ns+"/feedback";
  feedback_pub_ = nh.advertise<visualization_msgs::InteractiveMarkerFeedback>( feedback_topic, 100, false );

  reference_node_ = vis_manager->getSceneManager()->getRootSceneNode()->createChildSceneNode();

  axes_node_ = reference_node_->createChildSceneNode();
  axes_ = new ogre_tools::Axes( vis_manager->getSceneManager(), axes_node_, 1, 0.05 );
}

InteractiveMarker::~InteractiveMarker()
{
  delete axes_;
  vis_manager_->getSceneManager()->destroySceneNode( axes_node_ );
  vis_manager_->getSceneManager()->destroySceneNode( reference_node_ );
  delete menu_;
}

void InteractiveMarker::reset()
{
  controls_.clear();
}

void InteractiveMarker::processMessage( visualization_msgs::InteractiveMarkerPoseConstPtr message )
{
  Ogre::Vector3 position( message->pose.position.x, message->pose.position.y, message->pose.position.z );
  Ogre::Quaternion orientation( message->pose.orientation.w, message->pose.orientation.x, message->pose.orientation.y, message->pose.orientation.z );

  if ( orientation.w == 0 && orientation.x == 0 && orientation.y == 0 && orientation.z == 0 )
  {
    orientation.w = 1;
  }

  requestPoseUpdate( position, orientation );
}

bool InteractiveMarker::processMessage( visualization_msgs::InteractiveMarkerConstPtr message )
{
  reset();

  visualization_msgs::InteractiveMarker auto_message = *message;
  autoComplete( auto_message );

  // copy values

  name_ = auto_message.name;

  if ( auto_message.controls.size() == 0 )
  {
    owner_->setStatus( status_levels::Ok, name_, "Marker empty.");
    return false;
  }

  frame_locked_ = auto_message.frame_locked;

  scale_ = auto_message.scale;

  reference_frame_ = auto_message.header.frame_id;

  position_ = Ogre::Vector3(
      auto_message.pose.position.x,
      auto_message.pose.position.y,
      auto_message.pose.position.z );

  orientation_ = Ogre::Quaternion(
      auto_message.pose.orientation.w,
      auto_message.pose.orientation.x,
      auto_message.pose.orientation.y,
      auto_message.pose.orientation.z );

  // setup axes
  axes_->setPosition(position_);
  axes_->setOrientation(orientation_);
  axes_->set( scale_, scale_*0.05 );

  updateReferencePose();

  for ( unsigned i=0; i<auto_message.controls.size(); i++ )
  {
    controls_.push_back( boost::make_shared<InteractiveMarkerControl>( vis_manager_, auto_message.controls[i], reference_node_, this ) );
  }

  name_control_ = boost::make_shared<InteractiveMarkerControl>( vis_manager_, makeTitle( auto_message ), reference_node_, this );
  controls_.push_back( name_control_ );

  //create menu
  if ( message->menu.size() > 0 )
  {
    menu_ = new wxMenu();

    for ( unsigned i=0; i<message->menu.size(); i++ )
    {
      wxString title = wxString::FromAscii(message->menu[i].title.c_str());
      if ( message->menu[i].entries.empty() )
      {
        menu_->Append( i, title );
      }
      else
      {
        wxMenu* sub_menu = new wxMenu;
        for ( unsigned j=0; j<message->menu[i].entries.size(); j++ )
        {
          wxString entry = wxString::FromAscii( message->menu[i].entries[j].c_str());
          sub_menu->Append( j, entry );
        }
        menu_->AppendSubMenu( sub_menu, title );
      }
    }
  }

  owner_->setStatus( status_levels::Ok, name_, "OK");
  return true;
}

void InteractiveMarker::updateReferencePose()
{
  if (!FrameManager::instance()->getTransform( reference_frame_, ros::Time(0), reference_position_, reference_orientation_ ))
  {
    std::string error;
    FrameManager::instance()->transformHasProblems(reference_frame_, ros::Time(0), error);
    owner_->setStatus( status_levels::Error, name_, error);
    return;
  }

  reference_node_->setPosition( reference_position_ );
  reference_node_->setOrientation( reference_orientation_ );
}

void InteractiveMarker::update(float wall_dt)
{
  if ( frame_locked_ )
  {
    updateReferencePose();
  }
  if ( dragging_ )
  {
    publishPose();
  }
}

void InteractiveMarker::publishPose()
{
  visualization_msgs::InteractiveMarkerFeedback feedback;

  feedback.marker_name = name_;

  feedback.event_type = visualization_msgs::InteractiveMarkerFeedback::POSE_UPDATE;
  feedback.pose.position.x = position_.x;
  feedback.pose.position.y = position_.y;
  feedback.pose.position.z = position_.z;
  feedback.pose.orientation.x = orientation_.x;
  feedback.pose.orientation.y = orientation_.y;
  feedback.pose.orientation.z = orientation_.z;
  feedback.pose.orientation.w = orientation_.w;
  feedback.dragging = dragging_;

  feedback_pub_.publish( feedback );
}

void InteractiveMarker::requestPoseUpdate( Ogre::Vector3 position, Ogre::Quaternion orientation )
{
  if ( dragging_ )
  {
    pose_update_requested_ = true;
    requested_position_ = position;
    requested_orientation_ = orientation;
  }
  else
  {
    setPose( position, orientation );
  }
}

void InteractiveMarker::setPose( Ogre::Vector3 position, Ogre::Quaternion orientation )
{
  position_ = position;
  orientation_ = orientation;

  axes_->setPosition(position_);
  axes_->setOrientation(orientation_);

  std::list<InteractiveMarkerControlPtr>::iterator it;
  for ( it = controls_.begin(); it != controls_.end(); it++ )
  {
    (*it)->interactiveMarkerPoseChanged( position_, orientation_ );
  }
}

void InteractiveMarker::setShowName( bool show )
{
  if ( name_control_.get() )
  {
    name_control_->setVisible( show );
  }
}

void InteractiveMarker::setShowAxes( bool show )
{
  axes_node_->setVisible( show );
}

void InteractiveMarker::translate( Ogre::Vector3 delta_position )
{
  setPose( position_+reference_orientation_.Inverse()*delta_position, orientation_ );
}

void InteractiveMarker::rotate( Ogre::Quaternion delta_orientation )
{
  setPose( position_, delta_orientation * orientation_ );
}

void InteractiveMarker::startDragging()
{
  dragging_ = true;
}

void InteractiveMarker::stopDragging()
{
  pose_update_requested_ = false;
  dragging_ = false;
  if ( pose_update_requested_ )
  {
    setPose( requested_position_, requested_orientation_ );
  }
  // make sure pose and dragging state are being published
  publishPose();
}

bool InteractiveMarker::handleMouseEvent(ViewportMouseEvent& event)
{
  if (event.event.LeftDown())
  {
    old_target_frame_ = vis_manager_->getTargetFrame();
    //ROS_INFO_STREAM( "Saving old target frame: " << old_target_frame_ );
    vis_manager_->setTargetFrame(reference_frame_);
    startDragging();
  }
  if (event.event.LeftUp())
  {
    //ROS_INFO_STREAM( "Setting old target frame: " << old_target_frame_ );
    vis_manager_->setTargetFrame(old_target_frame_);
    stopDragging();
  }

  if ( !menu_ )
  {
    return false;
  }

  if ( event.event.RightDown() || event.event.RightIsDown() )
  {
    return true;
  }

  if ( event.event.RightUp() )
  {
    event.panel->PopupMenu( menu_, event.event.GetX(), event.event.GetY() );
    return true;
  }

  return false;
}

}
