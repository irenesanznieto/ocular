#include "LearnerRecognizerNode.h"

LearnerRecognizerNode::LearnerRecognizerNode()
{

    object_pub=nh.advertise<ocular::RecognizedObject>("object_id", 1);

    descriptors2D=nh.subscribe<ocular::HandImage>("descriptors2D", 1, &LearnerRecognizerNode::descriptors2D_cb, this);

    descriptors3D=nh.subscribe<sensor_msgs::PointCloud2>("descriptors3D",1,&LearnerRecognizerNode::descriptors3D_cb, this);

    event_sub=nh.subscribe<ocular::EventHandler>("event", 1, &LearnerRecognizerNode::setEvent, this);


    //Inintialize the number of view to be taken for each template
    this->number_views2D=10; //the total number of views to be extracted of each object
    this->number_views3D=10; //the total number of views to be extracted of each object


    //Set the number of views to be taken for each object and load the previous templates;
    this->alg2D.set_number_views(this->number_views2D); //pass the number of views to the algorithm 2D
    this->alg2D.load_templates();


    //Set the number of views to be taken for each object and load the previous templates;
    this->alg3D.set_number_views(this->number_views3D); //pass the number of views to the algorithm 3D
    this->alg3D.load_templates();


    //Initialize the iterator of the number of views
    this->number_views_it_2D=0;
    this->number_views_it_3D=0;

    //default mode: recognize
    this->learn_2D=false;
    this->learn_3D=false;


    this->object_id_2D.push_back(std::make_pair(-1,-1));
    this->object_id_3D.push_back(std::make_pair(-1,-1));
    this->object_id=-1;

    learning_2D=false;
    learning_3D=false;
}


void LearnerRecognizerNode::setEvent(const ocular::EventHandlerConstPtr & msg)
{
    std::cerr<<"setevent: "<<msg->event<<std::endl<<std::flush;

    if (msg->event=="learn" )
    {
        if (msg->last_event=="recognize")   //If last event was recognize
        {
            this->learn_2D=true;
            this->learn_3D=true;
        }
    }
    else if (msg->event=="recognize" && !learning_2D && !learning_3D)   //If the event is recognize
    {
        this->learn_2D=false;
        this->learn_3D=false;
    }

}


void LearnerRecognizerNode::descriptors2D_cb(const ocular::HandImageConstPtr & msg)
{
//    std::cerr<<"descriptors2d"<<std::endl<<std::flush;

    if(this->learn_2D)
    {
//        std::cerr<<"learn2D"<<std::endl<<std::flush;

        // take each view and train the algorithm with it, until the iterator is larger than the total number of views to be taken

//        std::cerr<<"2D: "<<number_views_it_2D<<" / "<<number_views2D<<std::endl<<std::flush;

        if (number_views_it_2D<number_views2D)
        {
            int result=-1;
            do{
                learning_2D=true;
                std::cerr<<"*** 2D *** ----> TRAINING OBJECT "<<alg2D.get_number_template()<<" VIEW  "<< number_views_it_2D<<std::endl<<std::flush;
//                std::cerr<<"image is empty?: "<<msg->image.empty()<<std::endl<<std::flush;
                result=alg2D.add_descriptors(*msg);
            }while(result<0);

            number_views_it_2D ++;
            sleep(1);

        }
        else if (number_views_it_2D==number_views2D)
        {
            //when the iterator is equal to the total number of views, reset the iterator
            number_views_it_2D=0;

            //stop the learning until a new recognize - learn events happen
            this->learn_2D=false;

            learning_2D=false;

            alg2D.next_object();

            //stop the training, all the views have already been trained
            std::cerr<<"TRAINING 2D COMPLETED"<<std::endl<<std::flush;

        }
        else
            std::cerr<<"Iterator of number of views greater than the total number of views"<<std::endl<<std::flush;
    }


    else if (!this->learn_2D)      //If the mode is recognize
    {

        std::pair <int, float> dummy=alg2D.match(msg);

//        if(dummy.first==last_object_id_2D.first)
//        {
//            this->object_id_2D=dummy;
//            last_object_id_2D=dummy;
//        }
//        else{
//            this->object_id_2D.first=-1;
//            this->object_id_2D.second=-1;
//        }

        this->object_id_2D.push_back(dummy);
        this->resulting_id("2D");

    }
}



void LearnerRecognizerNode::descriptors3D_cb(const sensor_msgs::PointCloud2ConstPtr & msg)
{

//    std::cerr<<"descriptors3d"<<std::endl<<std::flush;

    if(this->learn_3D)
    {
//        std::cerr<<"learn3d"<<std::endl<<std::flush;

        // take each view and train the algorithm with it, until the iterator is larger than the total number of views to be taken

//        std::cerr<<"3D: "<<number_views_it_3D<<" / "<<number_views3D<<std::endl<<std::flush;
        if (number_views_it_3D<number_views3D)
        {
            int result=-1;
            do{
                learning_3D=true;
                std::cerr<<"*** 3D *** ----> TRAINING OBJECT "<<alg3D.get_number_template()<<" VIEW  "<< number_views_it_3D<<std::endl<<std::flush;
                result=alg3D.add_descriptors(*msg);
            }while(result<0);

            number_views_it_3D ++;
            sleep(1);

        }
        else if (number_views_it_3D==number_views3D)
        {
            //when the iterator is equal to the total number of views, reset the iterator
            number_views_it_3D=0;

            //stop the learning until a new recognize - learn events happen
            this->learn_3D=false;

            learning_3D=false;

            alg3D.next_object();

            //stop the training, all the views have already been trained
            std::cerr<<"TRAINING 3D COMPLETED"<<std::endl<<std::flush;
        }
        else
            std::cerr<<"Iterator of number of views greater than the total number of views"<<std::endl<<std::flush;
    }


    else if (!this->learn_3D)      //If the mode is recognize
    {
        std::pair <int, float> dummy=alg3D.match(msg);

//        if(dummy.first==last_object_id_3D.first)
//            this->object_id_3D=dummy;
//        else{
//            this->object_id_3D.first=-1;
//            this->object_id_3D.second=-1;
//        }
//        last_object_id_3D=dummy;


        this->object_id_3D.push_back(dummy);

        this->resulting_id("3D");
    }
}


void LearnerRecognizerNode::resulting_id(std::string name)
{

//    if(object_id_2D.size()==5 && object_id_3D.size()==5)
//    {
//        std::vector<int> count;
//        int number_templates=alg2D.get_number_templates();

//        for (int i=0; i<number_templates;i++)
//            count.push_back(std::count (object_id_2D.begin(), object_id_2D.end(), i));

////        object_pub.publish(this->object);
//    }
//    else{
//        if(name=="2D")
//        {

//        }

//        if(name=="3D")
//        {

//        }

//    }
        object.object_id[0]=object_id_2D[0].first;
        object.object_id[1]=object_id_3D[0].first;
        object.ratio[0]=object_id_2D[0].second;
        object.ratio[1]=object_id_3D[0].second;

        object_id_2D.clear();
        object_id_3D.clear();
        object_pub.publish(this->object);

}
