#!/bin/bash

mkdir bw
mkdir hz

# BANDWIDTH: 
nohup xterm -e "source /opt/ros/groovy/setup.bash; source /home/peko/repositories/rosbuild_ws/setup.bash; rostopic bw /ocular/CONVERTER/hand_location > bw/bw_converter_hand_location.txt" &

sleep 0.3

nohup xterm -e "source /opt/ros/groovy/setup.bash; source /home/peko/repositories/rosbuild_ws/setup.bash; rostopic bw /ocular/EVENTHANDLER/event > bw/bw_eventhandler_event.txt" &

sleep 0.3

nohup xterm -e "source /opt/ros/groovy/setup.bash; source /home/peko/repositories/rosbuild_ws/setup.bash; rostopic bw /ocular/FE2D/descriptors2D > bw/bw_FE2D_descriptors2D.txt" &

sleep 0.3
nohup xterm -e "source /opt/ros/groovy/setup.bash; source /home/peko/repositories/rosbuild_ws/setup.bash; rostopic bw /ocular/FE3D/descriptors3D > bw/bw_FE3D_descriptors3D.txt" &

sleep 0.3

nohup xterm -e "source /opt/ros/groovy/setup.bash; source /home/peko/repositories/rosbuild_ws/setup.bash; rostopic bw /ocular/ROI2D/segmented_image > bw/bw_ROI2D_segmented_image.txt" &

sleep 0.3

nohup xterm -e "source /opt/ros/groovy/setup.bash; source /home/peko/repositories/rosbuild_ws/setup.bash; rostopic bw /ocular/ROI2D/segmented_image_with_keypoints > bw/bw_ROI2D_segmented_image_with_keypoints.txt" &

sleep 0.3


nohup xterm -e "source /opt/ros/groovy/setup.bash; source /home/peko/repositories/rosbuild_ws/setup.bash; rostopic bw /ocular/ROI3D/segmented_coordinates_px > bw/bw_ROI3D_segmented_coordinates_px.txt" &

sleep 0.3


nohup xterm -e "source /opt/ros/groovy/setup.bash; source /home/peko/repositories/rosbuild_ws/setup.bash; rostopic bw /ocular/ROI3D/segmented_pc > bw/bw_ROI3D/segmented_pc.txt" &

sleep 0.3

nohup xterm -e "source /opt/ros/groovy/setup.bash; source /home/peko/repositories/rosbuild_ws/setup.bash; rostopic bw /ocular/object_id > bw/bw_object_id.txt" &

sleep 0.3

#PUBLISHING RATE: 


nohup xterm -e "source /opt/ros/groovy/setup.bash; source /home/peko/repositories/rosbuild_ws/setup.bash; rostopic hz /ocular/CONVERTER/hand_location > hz/hz_converter_hand_location.txt" &

sleep 0.3

nohup xterm -e "source /opt/ros/groovy/setup.bash; source /home/peko/repositories/rosbuild_ws/setup.bash; rostopic hz /ocular/EVENTHANDLER/event > hz/hz_eventhandler_event.txt" &

sleep 0.3

nohup xterm -e "source /opt/ros/groovy/setup.bash; source /home/peko/repositories/rosbuild_ws/setup.bash; rostopic hz /ocular/FE2D/descriptors2D > hz/hz_FE2D_descriptors2D.txt" &

sleep 0.3
nohup xterm -e "source /opt/ros/groovy/setup.bash; source /home/peko/repositories/rosbuild_ws/setup.bash; rostopic hz /ocular/FE3D/descriptors3D > hz/hz_FE3D_descriptors3D.txt" &

sleep 0.3

nohup xterm -e "source /opt/ros/groovy/setup.bash; source /home/peko/repositories/rosbuild_ws/setup.bash; rostopic hz /ocular/ROI2D/segmented_image > hz/hz_ROI2D_segmented_image.txt" &

sleep 0.3

nohup xterm -e "source /opt/ros/groovy/setup.bash; source /home/peko/repositories/rosbuild_ws/setup.bash; rostopic hz /ocular/ROI2D/segmented_image_with_keypoints > hz/hz_ROI2D_segmented_image_with_keypoints.txt" &

sleep 0.3


nohup xterm -e "source /opt/ros/groovy/setup.bash; source /home/peko/repositories/rosbuild_ws/setup.bash; rostopic hz /ocular/ROI3D/segmented_coordinates_px > hz/hz_ROI3D_segmented_coordinates_px.txt" &

sleep 0.3


nohup xterm -e "source /opt/ros/groovy/setup.bash; source /home/peko/repositories/rosbuild_ws/setup.bash; rostopic hz /ocular/ROI3D/segmented_pc > hz/hz_ROI3D_segmented_pc.txt" &

sleep 0.3

nohup xterm -e "source /opt/ros/groovy/setup.bash; source /home/peko/repositories/rosbuild_ws/setup.bash; rostopic hz /ocular/object_id > hz/hz_object_id.txt" 


exit 0 
