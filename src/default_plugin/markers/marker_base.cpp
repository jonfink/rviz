/*
 * Copyright (c) 2009, Willow Garage, Inc.
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

#include "marker_base.h"
#include "default_plugin/marker_display.h"
#include "rviz/common.h"
#include "rviz/visualization_manager.h"
#include "rviz/selection/selection_manager.h"
#include "rviz/frame_manager.h"

#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreSceneManager.h>

#include <tf/tf.h>
#include <tf/transform_listener.h>

namespace rviz
{

MarkerBase::MarkerBase(MarkerDisplay* owner, VisualizationManager* manager, Ogre::SceneNode* parent_node)
: owner_(owner)
, vis_manager_(manager)
, parent_node_(parent_node->createChildSceneNode())
, coll_(0)
{}

MarkerBase::~MarkerBase()
{
  vis_manager_->getSelectionManager()->removeObject(coll_);
  vis_manager_->getSceneManager()->destroySceneNode(parent_node_);
}

void MarkerBase::setMessage(const MarkerConstPtr& message)
{
  MarkerConstPtr old = message_;
  message_ = message;

  expiration_ = ros::Time::now() + message->lifetime;

  onNewMessage(old, message);
}

bool MarkerBase::expired()
{
  return ros::Time::now() >= expiration_;
}

bool MarkerBase::transform(const MarkerConstPtr& message, Ogre::Vector3& pos, Ogre::Quaternion& orient, Ogre::Vector3& scale)
{
  if (!FrameManager::instance()->transform(message->header.frame_id, message->header.stamp, message->pose, pos, orient, true))
  {
    std::string error;
    FrameManager::instance()->transformHasProblems(message->header.frame_id, message->header.stamp, error);
    owner_->setMarkerStatus(getID(), status_levels::Error, error);
    return false;
  }

  scale = Ogre::Vector3(message->scale.x, message->scale.y, message->scale.z);
  scaleRobotToOgre( scale );

  return true;
}

} // namespace rviz
