add_subdirectory(default_plugin)

include_directories(.)

# Find the combined swig flags for this project
rosbuild_invoke_rospack(${PROJECT_NAME} ${PROJECT_NAME} SWIG_FLAGS "export" "--lang=swig" "--attrib=flags")
set(SWIG_FLAGS ${${PROJECT_NAME}_SWIG_FLAGS})

# Find the wxswig executable
rosbuild_find_ros_package(wxswig)
set(WXSWIG_EXECUTABLE ${wxswig_PACKAGE_PATH}/bin/swig)

# find wxWidgets with required flags
find_package(wxWidgets REQUIRED COMPONENTS std propgrid aui)
include(${wxWidgets_USE_FILE})
include_directories( ${wxWidgets_INCLUDE_DIRS} )

# Build the SVN version number into the source so it can be printed at run-time.
set(VERSION_FILE ${PROJECT_SOURCE_DIR}/build/version.cpp)

# execute_process(COMMAND          svnversion -n ${PROJECT_SOURCE_DIR}
#                 OUTPUT_VARIABLE  SVN_VERSION)
execute_process(COMMAND          cat .git/refs/heads/master
                OUTPUT_VARIABLE  SVN_VERSION)
configure_file(version.cpp.in ${VERSION_FILE} @ONLY)

# Add a custom command for generating the swig output files
set(SWIG_INTERFACE_FILE ${PROJECT_SOURCE_DIR}/src/rviz/rviz.i)
set(SWIG_OUTPUT_PYTHON_FILE ${PROJECT_SOURCE_DIR}/lib/rviz.py)

if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" GREATER 2.4)
  set(SWIG_OUTPUT_CPP_FILE ${PROJECT_SOURCE_DIR}/src/rviz/rviz_swig_generated.cpp)
  set(SWIG_COMMAND ${WXSWIG_EXECUTABLE} ${SWIG_FLAGS} -o ${SWIG_OUTPUT_CPP_FILE} -outdir ${PROJECT_SOURCE_DIR}/lib -module ${PROJECT_NAME} ${SWIG_INTERFACE_FILE})
else("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" GREATER 2.4)
  set(SWIG_OUTPUT_CPP_FILE rviz_swig_generated.cpp)
  set(SWIG_COMMAND ${WXSWIG_EXECUTABLE} ${SWIG_FLAGS} -o ${CMAKE_CURRENT_SOURCE_DIR}/${SWIG_OUTPUT_CPP_FILE} -outdir ${PROJECT_SOURCE_DIR}/lib -module ${PROJECT_NAME} ${SWIG_INTERFACE_FILE})
endif("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" GREATER 2.4)

set_source_files_properties(${SWIG_OUTPUT_CPP_FILE} PROPERTIES GENERATED true)
add_custom_command(OUTPUT   ${SWIG_OUTPUT_CPP_FILE}
                            ${SWIG_OUTPUT_PYTHON_FILE}
                   COMMAND  ${SWIG_COMMAND}
                   DEPENDS  ${SWIG_INTERFACE_FILE}
                            display.i
                            visualization_manager.i
                            visualization_panel.i
                            visualization_frame.i
                            helpers/color.i
                            visualization_manager.h
                            visualization_panel.h
                            visualization_frame.h
                            generated/rviz_generated.h
                            display.h
                            helpers/color.h
                            status_level.h)

# We create one lib with the C++...
rosbuild_add_library(${PROJECT_NAME} plugin/plugin.cpp
                                    plugin/plugin_manager.cpp
                                    plugin/type_registry.cpp
                                    properties/edit_enum_property.cpp
                                    properties/property.cpp
                                    properties/property_manager.cpp
                                    image/ros_image_texture.cpp
                                    tools/tool.cpp
                                    tools/move_tool.cpp
                                    tools/pose_tool.cpp
                                    tools/goal_tool.cpp
                                    tools/initial_pose_tool.cpp
                                    tools/selection_tool.cpp
                                    tools/interaction_tool.cpp
                                    mesh_loader.cpp
                                    splash_screen.cpp
                                    loading_dialog.cpp
                                    render_panel.cpp
                                    displays_panel.cpp
                                    views_panel.cpp
                                    time_panel.cpp
                                    selection_panel.cpp
                                    tool_properties_panel.cpp
                                    wx_log_rosout.cpp
                                    frame_manager.cpp
                                    visualization_manager.cpp
                                    visualization_frame.cpp
                                    visualization_panel.cpp
                                    plugin_manager_dialog.cpp
                                    display.cpp
                                    display_wrapper.cpp
                                    view_controller.cpp
                                    view_controllers/xy_orbit_view_controller.cpp
                                    view_controllers/orbit_view_controller.cpp
                                    view_controllers/fps_view_controller.cpp
                                    view_controllers/fixed_orientation_ortho_view_controller.cpp
                                    common.cpp
                                    ros_topic_property.cpp
                                    tf_frame_property.cpp
                                    new_display_dialog.cpp
                                    robot/tf_link_updater.cpp
                                    robot/robot_link.cpp
                                    robot/robot.cpp
                                    selection/selection_manager.cpp
                                    selection/selection_handler.cpp
                                    generated/rviz_generated.cpp
                                    ${VERSION_FILE})
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} ${OGRE_LIBRARIES})
rosbuild_link_boost(${PROJECT_NAME} thread signals filesystem system program_options)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_PATH})

# ...and another with the SWIG code.
rosbuild_add_library(python_${PROJECT_NAME} ${SWIG_OUTPUT_CPP_FILE})
target_link_libraries(python_${PROJECT_NAME} ${PROJECT_NAME} ${PYTHON_LIBRARIES})

# swig python needs a shared library named _<modulename>.[so|dll|...]
# this renames the output file to conform to that by prepending an underscore and removing the "lib" prefix
set_target_properties(python_${PROJECT_NAME}
                      PROPERTIES OUTPUT_NAME _${PROJECT_NAME}
                      PREFIX "")

rosbuild_add_executable(executable visualizer_app.cpp)
target_link_libraries(executable ${PROJECT_NAME} ${wxWidgets_LIBRARIES})
set_target_properties(executable
                      PROPERTIES OUTPUT_NAME ${PROJECT_NAME}
                      PREFIX "")
