#include "LearnerRecognizerNode.h"

LearnerRecognizerNode::LearnerRecognizerNode()
{
    object_pub=nh.advertise<std_msgs::Int32>("object_id", 1);

    descriptors2D=nh.subscribe<TFG::HandImage>("descriptors2D", 1, &LearnerRecognizerNode::descriptors2D_cb, this);

    descriptors3D=nh.subscribe<sensor_msgs::PointCloud2>("descriptors3D",1,&LearnerRecognizerNode::descriptors3D_cb, this);

    event_sub=nh.subscribe<TFG::EventHandler>("event", 1, &LearnerRecognizerNode::setEvent, this);

    //Inintialize the number of view to be taken for each template
    this->number_views.push_back(5); //the total number of views to be extracted of each object
    this->number_views.push_back(5); //the total number of views to be extracted of each object

    this->alg2D.set_number_views(this->number_views[0]); //pass the number of views to the algorithm 2D

    this->alg3D.set_number_views(this->number_views[1]); //pass the number of views to the algorithm 2D

    //Initialize the iterator of the number of views
    this->number_views_it.push_back(0);
    this->number_views_it.push_back(0);

    //default mode: recognize
    this->learn.push_back(false);
    this->learn.push_back(false);

    this->object_id.push_back(-1);
    this->object_id.push_back(-1);

}


void LearnerRecognizerNode::setEvent(const TFG::EventHandlerConstPtr & msg)
{
    if (msg->event=="learn")
    {
        if (msg->last_event=="recognize")   //If last event was recognize
        {
            this->learn[0]=true;
            //This is a new object to learn
            this->alg2D.set_new_object(true);

            this->learn[1]=true;
            this->alg3D.set_new_object(true);

        }
        else
        {
            this->alg2D.set_new_object(false);  //We are still learning views of the object
            this->alg3D.set_new_object(false);  //We are still learning views of the object
        }

    }
    else if (msg->event=="recognize")   //If the event is recognize
    {
        if (this->number_views_it[0]<this->number_views[0])   //If the 2D learning is still in process, carry on learning
        {
            this->learn[0]=true;
        }
        if (this->number_views_it[1]<this->number_views[1])   //If the 3D learning is still in process, carry on learning
        {
            this->learn[1]=true;
        }
        else
        {
            this->learn[0]=false;
            this->learn[1]=false;

        }
    }
}


void LearnerRecognizerNode::descriptors2D_cb(const TFG::HandImageConstPtr & msg)
{
    if(this->learn[0])
    {
        // take each view and train the algorithm with it, until the iterator is larger than the total number of views to be taken
        if (number_views_it[0]<number_views[0])
        {
            std::cerr<<"*** 2D *** ----> TRAINING OBJECT "<<alg2D.get_number_template()<<"VIEW  "<< number_views_it[0]<<std::endl;
            alg2D.add_descriptors(*msg);
            number_views_it[0] ++;
            sleep(1);

        }
        else if (number_views_it[0]==number_views[0])
        {
            //when the iterator is equal to the total number of views, reset the iterator
            number_views_it[0]=0;

            //stop the learning until a new recognize - learn events happen
            this->learn[0]=false;

            //stop the training, all the views have already been trained
            std::cerr<<"TRAINING COMPLETED, PLEASE TAKE YOUR HAND CLOSER TO THE BODY TO START THE RECOGNITION"<<std::endl;

        }
        else
            std::cerr<<"Iterator of number of views greater than the total number of views"<<std::endl;
    }


    else if (!this->learn[0])      //If the mode is recognize
    {
        //    match & publish the resulting object ID
        this->object_id[0]=alg2D.match2D(msg);
    }
}



void LearnerRecognizerNode::descriptors3D_cb(const sensor_msgs::PointCloud2ConstPtr & msg)
{
    if(this->learn[1])
    {
        // take each view and train the algorithm with it, until the iterator is larger than the total number of views to be taken
        if (number_views_it[1]<number_views[1])
        {
            std::cerr<<"*** 3D *** ----> TRAINING OBJECT "<<alg3D.get_number_template()<<"VIEW  "<< number_views_it[1]<<std::endl;

            alg3D.add_descriptors(msg, number_views_it[1]);
            number_views_it[1] ++;
            sleep(1);

        }
        else if (number_views_it[1]==number_views[1])
        {
            //when the iterator is equal to the total number of views, reset the iterator
            number_views_it[1]=0;

            //stop the learning until a new recognize - learn events happen
            this->learn[1]=false;

            //stop the training, all the views have already been trained
            std::cerr<<"TRAINING COMPLETED, PLEASE TAKE YOUR HAND CLOSER TO THE BODY TO START THE RECOGNITION"<<std::endl;

        }
        else
            std::cerr<<"Iterator of number of views greater than the total number of views"<<std::endl;
    }


    else if (!this->learn[1])      //If the mode is recognize
    {
        //    match & publish the resulting object ID
        object_id[1]=alg3D.match3D(msg);

        this->resulting_id();
    }
}


void LearnerRecognizerNode::resulting_id()
{
    //choose the object id and publish it
    if(this->object_id[0]==this->object_id[1])
        object_pub.publish(object_id[0]);
    else
        object_pub.publish(object_id[1]);

}
