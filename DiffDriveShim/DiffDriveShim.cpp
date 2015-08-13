// DiffDriveShim.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gazebo_ros_diff_drive.h"


using namespace gazebo;

#include <iostream>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	//GazeboRosDiffDrive df;
	GazeboRosDiffDrive * pDf;


	ros::init(argc, argv, "gazebo_diff");
	ros::Time::init();
	ros::Duration  dur(0.5);	

	//ros::Duration  dur2(2.5);
	//ros::Time t = ros::Time::now();
	//ros::Time span;
	//span = t + dur2;
	//span.toSec();
	//printf("toSec:%f\n", dur2.toSec());
	//printf("diff is %u %u\n", span.sec - t.sec, span.nsec - t.nsec);
	//printf("%f %f\n", span.toSec() , span.toSec() - t.toSec());
	////cout << (ros::Time::now() + dur).toSec();
	//return 0;
	//

	pDf = new GazeboRosDiffDrive();

	pDf->setNodeHandle(new ros::NodeHandle());


	
	pDf->Load(true);

//	cout << "about to spin\n";
	ROS_INFO_NAMED("interop","about to loop...\n");
	int Kret = 0;
	int Qret = 0;

	while (ros::ok())
	{
		pDf->Tick();
		ROS_INFO_NAMED("interop", "Tick...");

		Kret=GetAsyncKeyState(0x4b);
		Qret = GetAsyncKeyState(0x51);

		//ROS_INFO_NAMED("interop", "Keystate:%d", Kret);

		if (Kret)
		{
			ROS_INFO_NAMED("interop", "Killing and restarting...");
			pDf->FiniChild();
			pDf->Reset();
			delete pDf;
			//ros::shutdown();
			ros::Duration(1).sleep();
			
			//ros::init(argc, argv, "gazebodiidrive");
			pDf = new GazeboRosDiffDrive();
			
			pDf->setNodeHandle(new ros::NodeHandle);
			pDf->Load(true);
			Kret = 0;
		}

		if (Qret)
		{
			pDf->FiniChild();
			delete pDf;
			ros::shutdown();
			exit(0);

		}


		//ros::spinOnce();
		dur.sleep();
	}
	
	return 0;
}

