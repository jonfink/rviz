#include "ros/ros.h"

#include <visualization_msgs/InteractiveMarkerArray.h>

#include <tf/transform_broadcaster.h>
#include <tf/tf.h>

#include <math.h>

using namespace visualization_msgs;

InteractiveMarkerArray int_marker_array;
float marker_pos = 0;

////////////////////////////////////////////////////////////////////////////////////

void frameCallback(const ros::TimerEvent&)
{
  static uint32_t counter = 0;

  static tf::TransformBroadcaster br;

  tf::Transform t;

  t.setOrigin(tf::Vector3(0.0, 0.0, sin(float(counter)/70.0) * 1));
  t.setRotation(tf::Quaternion(0.0, 0.0, 0.0, 1.0));
  br.sendTransform(tf::StampedTransform(t, ros::Time::now(), "base_link", "moving_frame"));

  t.setOrigin(tf::Vector3(0.0, 0.0, 10.0));
  t.setRotation(tf::createQuaternionFromRPY(0.0, 0.0, M_PI*0.2));
  br.sendTransform(tf::StampedTransform(t, ros::Time::now(), "moving_frame", "move_rotate_frame"));

  ++counter;
}

double rand( double min, double max )
{
  double t = (double)rand() / (double)RAND_MAX;
  return min + t*(max-min);
}


Marker makeBox( InteractiveMarker &msg )
{
  Marker marker;

  marker.type = Marker::CUBE;
  marker.scale.x = msg.scale * 0.45;
  marker.scale.y = msg.scale * 0.45;
  marker.scale.z = msg.scale * 0.45;
  marker.color.r = 1.0;
  marker.color.g = 1.0;
  marker.color.b = 1.0;
  marker.color.a = 1.0;

  return marker;
}

InteractiveMarkerControl& makeBoxControl( InteractiveMarker &msg )
{
  InteractiveMarkerControl control;
  control.always_visible = true;
  control.markers.push_back( makeBox(msg) );
  msg.controls.push_back( control );

  return msg.controls.back();
}

InteractiveMarker makeEmptyMarker( bool dummyBox=true )
{
  std_msgs::Header header;
  header.frame_id = "/base_link";
//  header.stamp = ros::Time::now();

  geometry_msgs::Pose pose;
  pose.orientation.w = 1.0;
  pose.position.y = -3.0 * marker_pos++;
  pose.position.x = -2.0;

  InteractiveMarker int_marker;
  int_marker.header = header;
  int_marker.pose = pose;
  int_marker.scale = 1.0;
  int_marker.frame_locked = true;

  return int_marker;
}

void saveMarker( InteractiveMarker int_marker )
{
  int_marker_array.markers.push_back(int_marker);
}

////////////////////////////////////////////////////////////////////////////////////


void make6DofMarker( bool fixed )
{
  InteractiveMarker int_marker = makeEmptyMarker();

  int_marker.name = "Simple 6-DOF Control";

  int_marker.scale = 1.0;
  int_marker.header.frame_id = "/move_rotate_frame";

  makeBoxControl(int_marker);

  InteractiveMarkerControl control;

  if ( fixed )
  {
    int_marker.name += "\n(fixed orientation)";
    control.orientation_mode = InteractiveMarkerControl::FIXED;
  }

  control.orientation.w = 1;
  control.orientation.x = 1;
  control.orientation.y = 0;
  control.orientation.z = 0;
  control.interaction_mode = InteractiveMarkerControl::ROTATE_AXIS;
  int_marker.controls.push_back(control);
  control.interaction_mode = InteractiveMarkerControl::MOVE_AXIS;
//  int_marker.controls.push_back(control);

  control.orientation.w = 1;
  control.orientation.x = 0;
  control.orientation.y = 1;
  control.orientation.z = 0;
  control.interaction_mode = InteractiveMarkerControl::ROTATE_AXIS;
  int_marker.controls.push_back(control);
  control.interaction_mode = InteractiveMarkerControl::MOVE_AXIS;
//  int_marker.controls.push_back(control);

  control.orientation.w = 1;
  control.orientation.x = 0;
  control.orientation.y = 0;
  control.orientation.z = 1;
  control.interaction_mode = InteractiveMarkerControl::ROTATE_AXIS;
  int_marker.controls.push_back(control);
  control.interaction_mode = InteractiveMarkerControl::MOVE_AXIS;
//  int_marker.controls.push_back(control);

  saveMarker( int_marker );
}

void makeRandomDofMarker( )
{
  InteractiveMarker int_marker = makeEmptyMarker();
  int_marker.name = "6-DOF\n(Arbitrary Axes)";
  int_marker.header.frame_id = "/move_rotate_frame";

  makeBoxControl(int_marker);

  InteractiveMarkerControl control;

  for ( int i=0; i<3; i++ )
  {
    control.orientation.w = rand(-1,1);
    control.orientation.x = rand(-1,1);
    control.orientation.y = rand(-1,1);
    control.orientation.z = rand(-1,1);
    control.interaction_mode = InteractiveMarkerControl::ROTATE_AXIS;
    int_marker.controls.push_back(control);
    control.interaction_mode = InteractiveMarkerControl::MOVE_AXIS;
    int_marker.controls.push_back(control);
  }

  saveMarker( int_marker );
}


void makeViewFacingMarker( )
{
  InteractiveMarker int_marker = makeEmptyMarker();
  int_marker.name = "View Facing 6-DOF";
  int_marker.header.frame_id = "/move_rotate_frame";

  makeBoxControl(int_marker);

  InteractiveMarkerControl control;

  control.orientation_mode = InteractiveMarkerControl::VIEW_FACING;
  control.interaction_mode = InteractiveMarkerControl::MOVE_ROTATE;
  int_marker.controls.push_back(control);

  saveMarker( int_marker );
}


void makeQuadrocopterMarker( )
{
  InteractiveMarker int_marker = makeEmptyMarker();
  int_marker.name = "Quadrocopter Mode\n(Dog Walk + Elevation)";
  int_marker.header.frame_id = "/move_rotate_frame";

  makeBoxControl(int_marker);

  InteractiveMarkerControl control;

  control.orientation.w = 1;
  control.orientation.x = 0;
  control.orientation.y = 1;
  control.orientation.z = 0;
  control.interaction_mode = InteractiveMarkerControl::MOVE_ROTATE;
  int_marker.controls.push_back(control);
  control.interaction_mode = InteractiveMarkerControl::MOVE_AXIS;
  int_marker.controls.push_back(control);

  saveMarker( int_marker );
}

void makeChessPieceMarker( )
{
  InteractiveMarker int_marker = makeEmptyMarker();
  int_marker.name = "Chess Piece\n(2D move)";
  int_marker.header.frame_id = "/move_rotate_frame";

  InteractiveMarkerControl control;

  control.orientation.w = 1;
  control.orientation.x = 0;
  control.orientation.y = 1;
  control.orientation.z = 0;
  control.interaction_mode = InteractiveMarkerControl::MOVE_PLANE;
  int_marker.controls.push_back(control);

  // make a box which also moves in the plane
  control.markers.push_back( makeBox(int_marker) );
  control.always_visible = true;
  int_marker.controls.push_back(control);

  saveMarker( int_marker );
}

void makePanTiltMarker( )
{
  InteractiveMarker int_marker = makeEmptyMarker();
  int_marker.name = "Pan / Tilt";
  int_marker.header.frame_id = "/move_rotate_frame";

  makeBoxControl(int_marker);

  InteractiveMarkerControl control;

  control.orientation.w = 1;
  control.orientation.x = 0;
  control.orientation.y = 1;
  control.orientation.z = 0;
  control.interaction_mode = InteractiveMarkerControl::ROTATE_AXIS;
  control.orientation_mode = InteractiveMarkerControl::FIXED;
  int_marker.controls.push_back(control);

  control.orientation.w = 1;
  control.orientation.x = 0;
  control.orientation.y = 0;
  control.orientation.z = 1;
  control.interaction_mode = InteractiveMarkerControl::ROTATE_AXIS;
  control.orientation_mode = InteractiveMarkerControl::INHERIT;
  int_marker.controls.push_back(control);

  saveMarker( int_marker );
}

void makeMenuMarker()
{
  InteractiveMarker int_marker = makeEmptyMarker();
  int_marker.name = "Context Menu\n(Right Click)";
  int_marker.header.frame_id = "/move_rotate_frame";

  InteractiveMarkerControl control;

  control.orientation.w = 1;
  control.orientation.x = 0;
  control.orientation.y = 1;
  control.orientation.z = 0;
  control.interaction_mode = InteractiveMarkerControl::ROTATE_AXIS;
  int_marker.controls.push_back(control);

  control.interaction_mode = InteractiveMarkerControl::MENU;
  control.always_visible = true;
  control.markers.push_back( makeBox(int_marker) );
  int_marker.controls.push_back(control);

  visualization_msgs::Menu menu;

  menu.title = "First Entry";
  int_marker.menu.push_back( menu );

  menu.title = "Second Entry";
  int_marker.menu.push_back( menu );

  menu.title = "Submenu";
  menu.entries.push_back("First Submenu Entry");
  menu.entries.push_back("Second Submenu Entry");
  int_marker.menu.push_back( menu );

  saveMarker( int_marker );
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "interactive_marker_test");
  ros::NodeHandle n;

  ros::Publisher marker_pub;
  marker_pub = n.advertise<InteractiveMarkerArray> ("interactive_marker_array", 0, true);
//  ros::Timer publish_timer = n.createTimer(ros::Duration(1), publishCallback);
  ros::Timer frame_timer = n.createTimer(ros::Duration(0.01), frameCallback);

//  srand( ros::Time::now().sec );

  tf::TransformBroadcaster tf_broadcaster;

  ros::Duration(0.1).sleep();

  make6DofMarker( false );
  make6DofMarker( true );
  makeRandomDofMarker( );
  makeViewFacingMarker( );
  makeQuadrocopterMarker( );
  makeChessPieceMarker( );
  makePanTiltMarker( );
  makeMenuMarker( );

  ROS_INFO( "Publishing %d markers", (int)int_marker_array.markers.size() );
  marker_pub.publish( int_marker_array );

  ros::spin();
}
