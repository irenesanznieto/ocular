#ifndef TRIGGER_H
#define TRIGGER_H

#include <ros/ros.h>


/**Trigger class
*/

class Trigger 
{
	public: 
	
	/** Default constructor */	
		Trigger(); 
		
	/** A bool variable
	 *  It will be true when the distance hand-body is below a certain threshold
	 */
		bool on; 


	private: 

		ros::NodeHandle it;	//!< ROS nodehandler
		ros::Subscriber hand_info_sub;	//!< Subscriber to the hand information
		
		void hand_body_distance();	//!< This funcion will determine the triggering

};
#endif // TRIGGER_H
