/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*                        Copyright (c) James Pearman                          */
/*                                   2013                                      */
/*                            All Rights Reserved                              */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*    Module:     vexuser.c                                                    */
/*    Author:     James Pearman                                                */
/*    Created:    7 May 2013                                                   */
/*                                                                             */
/*    Revisions:                                                               */
/*                V1.00  04 July 2013 - Initial release                        */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*    The author is supplying this software for use with the VEX cortex        */
/*    control system. This file can be freely distributed and teams are        */
/*    authorized to freely use this program , however, it is requested that    */
/*    improvements or additions be shared with the Vex community via the vex   */
/*    forum.  Please acknowledge the work of the authors when appropriate.     */
/*    Thanks.                                                                  */
/*                                                                             */
/*    Licensed under the Apache License, Version 2.0 (the "License");          */
/*    you may not use this file except in compliance with the License.         */
/*    You may obtain a copy of the License at                                  */
/*                                                                             */
/*      http://www.apache.org/licenses/LICENSE-2.0                             */
/*                                                                             */
/*    Unless required by applicable law or agreed to in writing, software      */
/*    distributed under the License is distributed on an "AS IS" BASIS,        */
/*    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. */
/*    See the License for the specific language governing permissions and      */
/*    limitations under the License.                                           */
/*                                                                             */
/*    The author can be contacted on the vex forums as jpearman                */
/*    or electronic mail using jbpearman_at_mac_dot_com                        */
/*    Mentor for team 8888 RoboLancers, Pasadena CA.                           */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

#include <stdlib.h>

#include "ch.h"  		// needs for all ChibiOS programs
#include "hal.h" 		// hardware abstraction layer header
#include "vex.h"		// vex library header

// Digi IO configuration
static  vexDigiCfg  dConfig[kVexDigital_Num] = {
        { kVexDigital_1,    kVexSensorDigitalOutput, kVexConfigOutput,      0 },
        { kVexDigital_2,    kVexSensorDigitalOutput, kVexConfigOutput,      0 },
        { kVexDigital_3,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_4,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_5,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_6,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_7,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_8,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_9,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_10,   kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_11,   kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_12,   kVexSensorDigitalInput,  kVexConfigInput,       0 }
};

static  vexMotorCfg mConfig[kVexMotorNum] = {
        { kVexMotor_1,      kVexMotor393T,           kVexMotorNormal,       kVexSensorIME,         kImeChannel_1 },
        { kVexMotor_2,      kVexMotor393T,           kVexMotorNormal,       kVexSensorNone,        0 },
        { kVexMotor_3,      kVexMotor393T,           kVexMotorNormal,       kVexSensorNone,        0 },
        { kVexMotor_4,      kVexMotor393T,		       kVexMotorNormal,       kVexSensorNone,        0 },
        { kVexMotor_5,      kVexMotor393T,      	   kVexMotorNormal,       kVexSensorNone,        0 },
        { kVexMotor_6,      kVexMotor393T,      	   kVexMotorNormal,       kVexSensorNone,        0 },
        { kVexMotor_7,      kVexMotor393T,      	   kVexMotorNormal,       kVexSensorNone,        0 },
        { kVexMotor_8,      kVexMotor393T,      	   kVexMotorNormal,       kVexSensorNone,        0 },
        { kVexMotor_9,      kVexMotor393T,           kVexMotorNormal,       kVexSensorIME,         0 },
        { kVexMotor_10,     kVexMotor393T,           kVexMotorNormal,       kVexSensorIME,         kImeChannel_2 }
};


/*-----------------------------------------------------------------------------*/
/** @brief      User setup                                                     */
/*-----------------------------------------------------------------------------*/
/** @details
 *  The digital and motor ports can (should) be configured here.
 */
void
vexUserSetup()
{
	vexDigitalConfigure( dConfig, DIG_CONFIG_SIZE( dConfig ) );
	vexMotorConfigure( mConfig, MOT_CONFIG_SIZE( mConfig ) );
}

/*-----------------------------------------------------------------------------*/
/** @brief      User initialize                                                */
/*-----------------------------------------------------------------------------*/
/** @details
 *  This function is called after all setup is complete and communication has
 *  been established with the master processor.
 *  Start other tasks and initialize user variables here
 */
void
vexUserInit()
{

}

/*-----------------------------------------------------------------------------*/
/** @brief      Autonomous                                                     */
/*-----------------------------------------------------------------------------*/
/** @details
 *  This thread is started when the autonomous period is started
 */
msg_t
vexAutonomous( void *arg )
{
  (void)arg;

  // Must call this
  vexTaskRegister("auton");

  while(1)
  {
    // Don't hog cpu
    vexSleep( 25 );
  }

  return (msg_t)0;
}

#define MotorDriveL     kVexMotor_2
#define MotorDriveR     kVexMotor_3

// uncomment these to enable them - WARNING: this will make driving unresponsive!
//#define DO_ENCODER      
//#define DO_SONAR        
//#define DO_LCD          
//#define DO_LED          
//#define DO_HUMAN
/*-----------------------------------------------------------------------------*/
/** @brief      Driver control                                                 */
/*-----------------------------------------------------------------------------*/
/** @details
 *  This thread is started when the driver control period is started
 */
msg_t
vexOperator( void *arg )
{
#ifdef DO_LED  
  int16_t		blink = 0;
#endif  
#ifdef DO_HUMAN    
  int16_t		human=0;
#endif
	(void)arg;

	// Must call this
	vexTaskRegister("operator");

#ifdef DO_ENCODER
  int32_t count;
    vexEncoderInit();
    vexEncoderAdd(kVexQuadEncoder_1, kVexDigital_3,kVexDigital_4);
    vexEncoderStart(kVexQuadEncoder_1);	
    vexEncoderSet(kVexQuadEncoder_1,5000);
#endif
  
#ifdef DO_SONAR
    int16_t distance;
    vexSonarAdd(kVexSonar_1,kVexDigital_5,kVexDigital_6);
    vexSonarStart(kVexSonar_1);
    vexSonarRun();
#endif
  
	vex_printf("Starting\r\n");

	// Run until asked to terminate
	while(!chThdShouldTerminate())
	{

#ifdef DO_LED    
//    vex_printf("Blink: %d\r\n",blink%2 );
    vexDigitalPinSet( kVexDigital_1, blink%2 );
    blink++;
		vexSleep( 1000 );
    vexDigitalPinSet( kVexDigital_1, 0);
//    vexDigitalPinSet( kVexDigital_2, kVexDigitalLow);
#endif

#ifdef DO_HUMAN    
    human=vexDigitalPinGet( kVexDigital_12 );
    if(human==kVexDigitalHigh)
    {
      vex_printf("HUMAN\r\n");
    } else
    {
      vex_printf("\r\n");
    }
#endif    
    
    
#ifdef DO_LCD
    vexLcdPrintf( VEX_LCD_DISPLAY_2, VEX_LCD_LINE_1, "%4.2fV   %8.1f", vexSpiGetMainBattery() / 1000.0, chTimeNow() / 1000.0 );
    vexLcdPrintf( VEX_LCD_DISPLAY_2, VEX_LCD_LINE_2, "L %3d R %3d", vexMotorGet( MotorDriveL ), vexMotorGet( MotorDriveR ) );
#endif
    
#ifdef DO_ENCODER
    count=vexEncoderGet(kVexQuadEncoder_1);
    vex_printf("Count: %d\r\n",count);
    vexSleep( 500 );
#endif

#ifdef DO_SONAR
    distance=vexSonarGetInch(kVexSonar_1);
    vex_printf("Distance: %d\r\n",distance);
    vexSleep( 500 );
#endif

		// Tank drive
		// left drive
		vexMotorSet( kVexMotor_3, vexControllerGet( Ch3 ) );
		// right drive
//		vexMotorSet( kVexMotor_2, vexControllerGet( Ch2 ) );
		vexMotorSet( kVexMotor_2, 250 );

		// Don't hog cpu
		vexSleep( 25 );
	}

	return (msg_t)0;
}



