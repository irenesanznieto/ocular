#include "../libraries/libraries/roisegmenter2D.h"

#include <fstream>
#include <iostream>

int main ()
{
    RoiSegmenter2D roiseg2D;

    TFG::HandLocPx msg_hand_loc_px;

    msg_hand_loc_px.header.seq=187;
    msg_hand_loc_px.header.stamp.sec=1390833331;
    msg_hand_loc_px.header.stamp.nsec=843339980;
    msg_hand_loc_px.header.frame_id="openni_depth_frame";
    msg_hand_loc_px.user_id=1;
    msg_hand_loc_px.name.push_back("left_hand");
    msg_hand_loc_px.name.push_back("right_hand");


    msg_hand_loc_px.points.push_back(50);
    msg_hand_loc_px.points.push_back(50);
    msg_hand_loc_px.points.push_back(200);
    msg_hand_loc_px.points.push_back(200);

    const TFG::HandLocPxConstPtr& msg_hand_loc_px_ptr = boost::make_shared<TFG::HandLocPx>(msg_hand_loc_px);


    roiseg2D.coordinates(msg_hand_loc_px_ptr);


    std::string sys_command="find . -print | grep 'sandbox/TFG/data/test/' > dummy.txt";
    system(sys_command.c_str());

    std::string path;
    std::ifstream myfile;
    myfile.open ("dummy.txt");
    myfile >>path;

    myfile.close();
    roiseg2D.setInputImage(path);
//    TFG::HandImage result_image=roiseg2D.segment();

}
