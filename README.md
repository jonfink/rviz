# RVIZ for Mac (with cocoa!)

While the work [here](https://github.com/wjwwood/ros-osx/wiki) goes a long way towards explaining how to get RVIZ working on a Mac (especially in terms of getting macports sorted out to compile all the necessary dependencies into universal binaries), it relies on **old** Carbon support with wxWidgets-2.8 which is rapidly disappearing (e.g. when one moves to 10.6-Snow Leopard and then to 10.7-Lion).  wxWidgets-2.9.2 has decent Cocoa support (here to stay on Mac platforms) so it seems that RViz on Mac with full Cocoa support is a worthy goal.

In essence, the deviations in this version of RViz from the one [developed by Willow Garage](https://code.ros.org/svn/ros-pkg/stacks/visualization/trunk/rviz) are only to support wxWidgets-2.9 (which means using the version of propgrid that is now in the main wxWidgets code base).

## Dependency Instructions

For now, follow [https://code.ros.org/svn/ros-pkg/stacks/visualization/trunk/rviz](https://code.ros.org/svn/ros-pkg/stacks/visualization/trunk/rviz) but drop the +carbon variants.  Really, just make sure that you have universal (or i386) builds of everything.  While I think a full 64-bit compile is doable down the road, there may still be troubles getting Ogre to work properly.

For Ogre, I just download and use the precompiled SDK from their [website](http://www.ogre3d.org/) (currently using 1.7.3).

## Build instructions

...

## Comments on Stability

There are still some details of the new propgrid stuff that don't quite work right -- this causes the occasional crash.  I'm hoping there are some other developers out there who can help find/debug/fix some of these errors (skipping the macports install of wxWidgets and building a version with debug flags enabled is invaluable for this).

Also, please use the [github issues button](https://github.com/jonfink/rviz/issues) to track problems/solutions.
