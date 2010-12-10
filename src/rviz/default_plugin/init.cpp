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

#include "rviz/plugin/type_registry.h"

#include "axes_display.h"
#include "camera_display.h"
#include "grid_display.h"
#include "laser_scan_display.h"
#include "map_display.h"
#include "marker_display.h"
#include "pose_array_display.h"
#include "point_cloud_display.h"
#include "point_cloud2_display.h"
#include "path_display.h"
#include "polygon_display.h"
#include "grid_cells_display.h"
#include "odometry_display.h"
#include "robot_model_display.h"
#include "tf_display.h"
#include "pose_display.h"
#include "point_cloud_transformers.h"
#include "image_display.h"
#include "gripper_click_display.h"

using namespace rviz;

extern "C" void rvizPluginInit(rviz::TypeRegistry* reg)
{
  reg->registerDisplay<AxesDisplay>("rviz::AxesDisplay");
  reg->registerDisplay<CameraDisplay>("rviz::CameraDisplay");
  reg->registerDisplay<GridDisplay>("rviz::GridDisplay");
  reg->registerDisplay<LaserScanDisplay>("rviz::LaserScanDisplay");
  reg->registerDisplay<MapDisplay>("rviz::MapDisplay");
  reg->registerDisplay<MarkerDisplay>("rviz::MarkerDisplay");
  reg->registerDisplay<PoseArrayDisplay>("rviz::PoseArrayDisplay");
  reg->registerDisplay<PointCloudDisplay>("rviz::PointCloudDisplay");
  reg->registerDisplay<PointCloud2Display>("rviz::PointCloud2Display");
  reg->registerDisplay<PathDisplay>("rviz::PathDisplay");
  reg->registerDisplay<PolygonDisplay>("rviz::PolygonDisplay");
  reg->registerDisplay<PoseDisplay>("rviz::PoseDisplay");
  reg->registerDisplay<GridCellsDisplay>("rviz::GridCellsDisplay");
  reg->registerDisplay<OdometryDisplay>("rviz::OdometryDisplay");
  reg->registerDisplay<RobotModelDisplay>("rviz::RobotModelDisplay");
  reg->registerDisplay<TFDisplay>("rviz::TFDisplay");
  reg->registerDisplay<ImageDisplay>("rviz::ImageDisplay");
  reg->registerDisplay<GripperClickDisplay>("rviz::GripperClickDisplay");

  reg->registerClass<XYZPCTransformer>("rviz::PointCloudTransformer", "rviz::XYZPCTransformer", "XYZ");
  reg->registerClass<IntensityPCTransformer>("rviz::PointCloudTransformer", "rviz::IntensityPCTransformer", "Intensity");
  reg->registerClass<RGB8PCTransformer>("rviz::PointCloudTransformer", "rviz::RGB8PCTransformer", "RGB8");
  reg->registerClass<RGBF32PCTransformer>("rviz::PointCloudTransformer", "rviz::RGBF32PCTransformer", "RGBF32");
  reg->registerClass<FlatColorPCTransformer>("rviz::PointCloudTransformer", "rviz::FlatColorPCTransformer", "Flat Color");
  reg->registerClass<AxisColorPCTransformer>("rviz::PointCloudTransformer", "rviz::AxisColorPCTransformer", "Axis");
}
