//■▬▬▬▄■■▄▬▬▬▬▬▄■■■▄▬▬▬▬▬▄■■■▄▬▬▬▬▬▄■■■▄▬▬▬▬▬▄■■■▄▬▬▬▬▬●ஜ۩۞۩ஜ●▬▬▬▬▬▄■■■▄▬▬▬▬▄■■■▄▬▬▬▬▄■■■▄▬▬▬▬▄■■■▄▬▬▬▬▄■■▄▬▬▬▬■
/* ▄█▓▒░░▒▓█▄█▓▒░░░▒▓█▄█▓▒░░░▒▓█▄█▓▒░░░▒▓█▄█▓▒░░░▒▓█▄   Welcome   ▄█▓▒░░▒▓█▄█▓▒░▒▓▓█▄█▓▒░░▒▓█▄█▓▒░░▒▓█▄█▓▒░▒▓█▄ 
▄▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▓■ ●ஜ۩۞۩ஜ● ■▓▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀■
╠══════════════╦═══════════════════════════╦═════════════════════════════════════════════════════════════════════╣
║    Module    ║  MECH5080M - Team Project ║       Virtual Racing Building a Formula Student Car Simulator       ║
╠══════════════╬═══════════════════════════╬═══════════╦═════════════════════════════════════════════════════════╣
║    Author    ║     el18mf - Mathew F     ║ Group 135 ║      Alex B,  Curtis L, Jordan P, Albert (Qianli) L     ║
╠══════════════╬═══════════════════════════╩═══════════╩═════════════════════════════════════════════════════════╣
║              ║ Plugin for rFactor 2 to enable communication between Telemetry outputs from said software to    ║
║ Description  ║ the physical hardware in order to faciliate actuation. Created for Master's dissertation.       ║
║              ║ Sends Data Packages with order described in accompanying excel file via UDP port 10815.         ║
╠══════════════╬═════════════════════════════════════════════════════════════════════════════════════════════════╣
║              ║ V1) File: rFactor 2 Output -> .csv file -> Arduino (alex Code) -> Actuation (Too high Latency). ║
║    Plugin    ║ V2) Memory Buffer: Stored data in the memory buffer then accessed by arduino (missing data).    ║
║   Versions   ║ V3) TCP/UDP V1: Send data via TCP/UDP port (Detected as Intrusive by game/caused crashing.      ║
║              ║ V4) UDP V2: Aided in work-around by <redacted>* - Current Version.                              ║
║              ║ *Asked to keep said person & work-around anonymous to prevent proliferation of said work-around.║
╠══════════════╩═════════════════════════════════════════════════════════════════════════════════════════════════╣
║ Adapted from source code, information, data, and algorithms belonging to CUBE technology (tm) which form the   ║
║ the Example Plugin V8 for rFactor2, made available by Studio 397 in the form of a zip file within their forums.║
║        Download found in modding resources section here: https://www.studio-397.com/modding-resources/         ║
║            PROPRIETARY AND CONFIDENTIAL -  Copyright (c) 2018 Studio 397 B.V.  All rights reserved.            ║
║                                                                                                                ║
╠════════════════════════════════════════════════════ Notes ═════════════════════════════════════════════════════╣
║                                                                                                                ║
║  - Formatting: | Max Column - 114 | ===== Title ===== | _____Section_Split_____ |                              ║
║                                                                                                                ║
║  - Commenting: | If fits in 114 column max // on same line | If too long, // across multiple lines before |    ║
║                                                                                                                ║
║  - ctrl + / =  Visual Studio Code shortcut to comment selected line/s, eases                                   ║
║                enabling and disabling of features.                                                             ║
║                                                                                                                ║
║  - Use of Visual Studio Express 2012 (free via microsoft coding insider programmer) used to compile, but       ║
║    compiling possibly through Visual Studio Code via Bash terminal using:                                      ║
║                                                                                                                ║
║    1)  g++ -c -fPIC file.cpp -o file.o         //  Created object file that can be converted to a .dll         ║
║                                                                                                                ║
║    2a) g++ -shared -o file.dll file.o          //  Compilation of Object file into a .dll                      ║
║        g++ -shared -o file.dll file.o -lWs2_32 //  Missing Library Error Fix: Winsock library Manual link (UDP)║
║                                                                                                                ║
║  - Compiling done using Visual Studio Express 2012 which is free via Visual Studio Dev Essentials service      ║
║                                                                                                                ║
╠════════════════════════════════════════════════════ ASCII ═════════════════════════════════════════════════════╣
║                                                                                                                ║
║                 ┌───────────┬─────────────┬───────────┬───────────┬─────────────┬───────────┐                  ║
║                 │   Type    |  alt + No.  │  Symbol   │   Type    |  alt + No.  │  Symbol   │                  ║
║                 ├───────────┼─────────────┼───────────┼───────────┼─────────────┼───────────┤                  ║
║                 │           │     176     │     ░     │           │     174     │     «     │                  ║
║                 │           │     177     │     ▒     │           │     175     │     »     │                  ║
║                 │           │     178     │     ▓     │           │     176     │     ░     │                  ║
║                 │           │     179     │     │     │           │     177     │     ▒     │                  ║
║                 │           │     180     │     ┤     │           │     178     │     ▓     │                  ║
║                 │           │     185     │     ╣     │   Icons   │     219     │     █     │                  ║
║                 │           │     186     │     ║     │           │     220     │     ▄     │                  ║
║                 │           │     187     │     ╗     │           │     223     │     ▀     │                  ║
║                 │  Borders  │     188     │     ╝     │           │     254     │     ■     │                  ║
║                 │           │     191     │     ┐     │           │     184     │     ©     │                  ║
║                 │           │     192     │     └     ├───────────┼─────────────┼───────────┤                  ║
║                 │           │     193     │     ┴     │           │     201     │     ╔     │                  ║
║                 │           │     194     │     ┬     │           │     202     │     ╩     │                  ║
║                 │           │     195     │     ├     │           │     203     │     ╦     │                  ║
║                 │           │     196     │     ─     │  Borders  │     204     │     ╠     │                  ║
║                 │           │     197     │     ┼     │           │     205     │     ═     │                  ║
║                 │           │     200     │     ╚     │           │     206     │     ╬     │                  ║
║                 └───────────┴─────────────┴───────────┴───────────┴─────────────┴───────────┘                  ║
║                                                                                                                ║
╚════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝*/
//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▓■ ●ஜ۩۞۩ஜ● ■▓▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀

#include <WinSock2.h>           // required library for UDP connection
#include <Windows.h>

#include "UDPlugin.hpp"          // corresponding header file
#include <math.h>               // for atan2, sqrt
#include <stdio.h>              // for sample output
#include <assert.h>
#include <io.h>
#include <sys/stat.h>        
#include <string.h>
#include <sys/types.h>
#include <time.h>               //  To get time for log & Output Files

#include <WS2tcpip.h>

#define TIME_LENGTH 26

// UDPlugin::UDPlugin(){}
// UDPlugin::~UDPlugin(){}

// plugin information
extern "C" __declspec( dllexport )  // Sets Plugin Name
const char * __cdecl GetPluginName()                   { return("UDPlugin - 2024.04.08"); } 

extern "C" __declspec( dllexport )  // Plugin Object Type - See PluginObjects.hpp lines 30-41 for all types
PluginObjectType __cdecl GetPluginType()               { return(PO_INTERNALS); }  

extern "C" __declspec( dllexport )  // InternalsPluginV01 functionality if return value changed, you must derive   
int __cdecl GetPluginVersion()                         { return(6); } // from the appropriate class (1-7)!   
                                                                        
extern "C" __declspec( dllexport )
PluginObject * __cdecl CreatePluginObject()            { return( (PluginObject *) new UDPlugin ); }

extern "C" __declspec( dllexport )
void __cdecl DestroyPluginObject( PluginObject *obj )  { delete( (UDPlugin *) obj ); }

//════════════════════════════════════════════════════ My Code ═══════════════════════════════════════════════════
//  look into adding using UDPlugin::functions in the class
//  Also try using namespace UDPlugin;
//═══════════════════════════════════════════════════ Functions ══════════════════════════════════════════════════


/*╔══════════════╦════════════════╗
  ║   Function   ║  WriteToFiles  ║
  ╠══════════════╬════════════════╩════════════════════════════════════════════════════════════════════════════╗
  ║ Description  ║ Writes timestamped message/data (Telemetry, Graphics, Scoring) to individual text files     ║
  ╠══════════════╬═════════════════════════════════════════════════════════════════════════════════════════════║
  ║  Parameters  ║ openStr: Mode in which to open files ("w" for write, "a" for append, etc.)                  ║
  ║              ║ msg: The message to be written                                                              ║
  ╚══════════════╩═════════════════════════════════════════════════════════════════════════════════════════════╝*/
void UDPlugin::WriteToFiles( const char * const openStr, const char * const msg )
{
	
	const char* TelemPath = "C:\\Users\\Mathew\\Desktop\\rF2_data_files\\Telemetry.txt";

  FILE *TelemFile;             // Pointer to FILE object for file access
  time_t curtime;                                           //  Variable to store the current time
  struct tm loctime;                                       //  Pointer to tm structure for converting time
  char thetime[TIME_LENGTH];

  int telem = fopen_s(&TelemFile, TelemPath, openStr );  // Open "Telemetry.txt" with the mode specified by openStr
  if(telem == 0)  {                            // Check if the file was successfully opened
    curtime = time(NULL);                        // Get the current time
  int telem2 = localtime_s(&loctime, &curtime);
  int telem3 = asctime_s(thetime, TIME_LENGTH, &loctime);    
  thetime[TIME_LENGTH - 2] = 0;                          
      
  fprintf(TelemFile, "[%s] %s\n", thetime, msg);            // Writes message to file with corresponding timestamp  
  fclose(TelemFile);                                        // Close file to flush stream & release resources
  }
  // // Uncomment to enable Graphics Output Data being written to a corresponding text file
  // fo = fopen( "GraphicsOutput.txt", openStr );
  // if( fo != NULL )  {                            // Check if the file was successfully opened
  //   curtime = time(NULL);                        // Get the current time
	// 	loctime = localtime(&curtime);               // Convert current time to local time
    
  //   fprintf( fo, "[%s] %s\n", asctime (loctime), msg);//Write the timestamped message to "TelemetryOutput.txt"  
  //   fclose( fo );                                    //Close the file to flush the stream and release resources
  // }
  
  // // Uncomment to enable Scoring Output Data being written to a corresponding text file
  // fo = fopen( "ScoringOutput.txt", openStr );
  // if( fo != NULL )  {                            // Check if the file was successfully opened
  //   curtime = time(NULL);                        // Get the current time
	// 	loctime = localtime(&curtime);               // Convert current time to local time
    
  //   fprintf( fo, "[%s] %s\n", asctime (loctime), msg);// Write the timestamped message to "TelemetryOutput.txt"  
  //   fclose( fo );                                   // Close the file to flush the stream and release resources
  // }

}
//  Mostly finished Code (not recording to log) and not comments

void UDPlugin::log(const char *msg) {          
    // Define the full path for the log file - Change to suit needs
    const char* logPath = "C:\\Users\\Mathew\\Desktop\\rF2_data_files\\UDPlugin.log";

    // Open or create a log file in append mode
    FILE *logFile;                                            //  Pointer to FILE object for log file access
    time_t curtime;                                           //  Variable to store the current time
    struct tm loctime;                                        //  Pointer to tm structure for converting time
    char thetime[TIME_LENGTH];

    // Open the log file in append mode ("a"). If the file doesn't exist, it will be created.
    int err = fopen_s(&logFile, logPath, "a");         //  change from UDPlugin.log
    if (err == 0) {                                           //  Check if the file was successfully opened
      curtime = time(NULL);                                   //  Get the current time
      int err2 = localtime_s(&loctime, &curtime);
      int err3 = asctime_s(thetime, TIME_LENGTH, &loctime);    
      thetime[TIME_LENGTH - 2] = 0;                          
		   
fprintf(logFile, "[%s] %s\n", thetime, msg);                  // Writes message to file with corresponding timestamp  
      fclose(logFile);                                        // Close file to flush stream & release resources
	}
}
//  Mostly finished Code and incomplete comments

void UDPlugin::Startup(long version) 
{ 
  const char* SettingsPath = "C:\\Users\\Mathew\\Desktop\\rF2_data_files\\UDPlugin.ini";
  FILE *settings;
  // struct hostent *ptrh;
  data_version = 1;
  char portstring[10];

  ADDRINFO hints = { sizeof(addrinfo) };
  hints.ai_flags = AI_ALL;
  hints.ai_family = PF_INET;
  hints.ai_protocol = IPPROTO_IPV4;
  ADDRINFO *pResult = NULL;

  WriteToFiles("a", "--Starting Plugin--");   //  Writes Start-up message to enabled output files
  log("--Starting Plugin--" );                //  Records Shutdown into Log 

  // open socket
  s = socket(PF_INET, SOCK_DGRAM, 0);
  if (s < 0) {
    log("could not create datagram socket");
    return;
  }
  
  int err = fopen_s(&settings, SettingsPath, "r");
  if (err == 0) {
    log("reading settings");
    if (fscanf_s(settings, "%[^:]:%i", hostname, _countof(hostname), &port) != 2) {
      log("could not read host and port");}
      
    //ptrh = gethostbyname(hostname);
    log("settings read from file");
    int errcode = getaddrinfo(hostname, NULL, &hints, &pResult);

    fclose(settings);

    log("hostname is:");
    log(hostname);
    log("port is:");
    sprintf_s(portstring, "%i", port);
    log(portstring);
  }
  else {
    log("could not read settings, using defaults: localhost:6789");
    //ptrh = gethostbyname("localhost"); /* Convert host name to equivalent IP address and copy to sad. */

    int errcode = getaddrinfo("localhost", NULL, &hints, &pResult);


    port = 10815;
  }
  memset((char *)&sad, 0, sizeof(sad));       //  clear sockaddr structure 
  sad.sin_family = AF_INET;                   //  set family to Internet   
  sad.sin_port = htons((u_short)port);      //  originally 6788 but changed to 10815

  sad.sin_addr.S_un.S_addr = *((ULONG*)&(((sockaddr_in*)pResult->ai_addr)->sin_addr));    


  // memcpy(&sad.sin_addr, ptrh->h_addr, ptrh->h_length);
  // mEnabled = true;  // default HW control enabled to true
}
//  Mostly finished Code and incomplete comments

/*╔══════════════╦══════════════╗
  ║   Function   ║   Shutdown   ║
  ╠══════════════╬══════════════╩══════════════════════════════════════════════════════════════════════════════╗
  ║              ║                                                                                             ║
  ║ Description  ║ the physical hardware in order to faciliate actuation. Created for Master's dissertation.   ║
  ║              ║                                                                                             ║
  ╠══════════════╬═════════════════════════════════════════════════════════════════════════════════════════════║
  ║  Parameters  ║                                                                                             ║
  ╚══════════════╩═════════════════════════════════════════════════════════════════════════════════════════════╝*/
void UDPlugin::Shutdown() {
  if (s > 0) {                                  //  Checks to see if socket is active
    closesocket(s);                             //  If active, closes the socket
    s = 0;                                      //  Sets socket to equal 0
  }
    
  WriteToFiles( "a", "--Shutting Down--" );     //  Writes Shutdown message to enabled output files
  log("--Shutting Down--" );              //  Records Shutdown into Log 
} 
//  Mostly finished Code and incomplete comments

void UDPlugin::StartSession()
{
  WriteToFiles( "a", "--START SESSION--" );      //  Writes Session Start message to enabled output files
  log("--START SESSION--" );               //  Records Session Start into Log   
}
//  Mostly finished Code and incomplete comments

void UDPlugin::Load(){}   //  Not Used
void UDPlugin::Unload(){} //  Not Used


void UDPlugin::EndSession()
{
  WriteToFiles( "a", "--END SESSION--" );        //  Writes Session End message to enabled output files
  log("---END SESSION--" );                //  Records Session End into Log
}
//  Mostly finished Code and incomplete comments

void UDPlugin::EnterRealtime()
{
  // start up timer every time we enter realtime
  mET = 0.0f;                                 //  Reset elapsed time counter to 0 when entering real-time session
  WriteToFiles( "a", "---ENTER REALTIME---" ); //  Writes message to enabled output files when real-time entered
  log("---ENTER REALTIME---" );          //  Records real-time session entry into Log
}
//  Mostly finished Code and incomplete comments

void UDPlugin::ExitRealtime()
{
  mET = -1.0f;
  WriteToFiles( "a", "---EXIT REALTIME---" );    //  Writes real-time exit message to enabled output files
  log("---EXIT REALTIME---" );             //  Records real-time session exit into Log
}
//  Mostly finished Code and incomplete comments

void UDPlugin::UpdateTelemetry(const TelemInfoV01 &info) {
	log("starting telemetry\n"); // Records Telemetry start into Log

  // =====================================================================================================================
  // Declare a buffer to store telemetry data to be sent
  char buffer [200];
  
  // Get the size of the broadcast address structure
  int len = sizeof(sad);

  // Compute auxiliary vectors based on the telemetry orientation data
  TelemVect3 forwardVector = { -info.mOri[0].z, -info.mOri[1].z, -info.mOri[2].z };
  TelemVect3 upVector = {  info.mOri[0].y,  info.mOri[1].y,  info.mOri[2].y };
  TelemVect3 leftVector = {  info.mOri[0].x,  info.mOri[1].x,  info.mOri[2].x };

  // Calculate pitch, yaw, and roll from orientation data
  // These are normalized vectors, and the world Y coordinate is up.
  // So, pitch and roll (w.r.t. the world x-z plane) can be determined as follows:
  const double pitch = atan2( forwardVector.y, sqrt( ( forwardVector.x * forwardVector.x ) + ( forwardVector.z * forwardVector.z ) ) );
  const double yaw = atan2(info.mOri[0].z, info.mOri[2].z);
  const double  roll = atan2(    leftVector.y, sqrt( (    leftVector.x *    leftVector.x ) + (    leftVector.z *    leftVector.z ) ) );
  const double radsToDeg = 57.296;

  // Format telemetry data into a string buffer
	// sprintf(buffer, "0, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, 0, 0, 0, %ld, %ld, %.3f, %.3f, 0, %.3f, %.3f, 0, %.3f, 0, 0\r\n", info.mLocalRotAccel.z, - info.mLocalRotAccel.x, info.mLocalRotAccel.y, yaw, pitch, roll, - info.mLocalAccel.z, - info.mLocalAccel.x, info.mLocalAccel.y, - info.mLocalVel.z, - info.mLocalVel.x, info.mLocalVel.y, - info.mPos.z, - info.mPos.x, info.mPos.y, info.mGear, info.mID, - info.mLocalVel.z, info.mEngineRPM, info.mEngineWaterTemp, info.mFuel, info.mEngineOilTemp);
	// //                                                                                                                                                                              RotAccZ,               RotAccX,                 RotAccY,               yaw, pitch, roll, SurgeAcc,             SwayAcc,              HeaveAcc,           forward velocity,   right velocity,     up velocity,                                                 currentgear,playerID, speed,              engineRPM,       engine temp,           fuel,       oil temp
  //sprintf(buffer, "%.3f, %.3f, %.3f, %.3f, %.3f, %.3f\r\n", roll * radsToDeg,  pitch * radsToDeg, info.mLocalAccel.y, yaw * radsToDeg, - info.mLocalAccel.x, - info.mLocalAccel.z);
	//                                                          Roll,               Pitch,              HeaveAcc,           Yaw,                SwayAcc,            SurgeAcc
  sprintf(buffer, "%.3f\r\n", roll * radsToDeg);

  // Send telemetry data via UDP broadcast
  // s: Socket descriptor for sending data
  // buffer: Buffer containing the telemetry data
  // strlen(buffer): Length of the telemetry data in the buffer
  // 0: Flags (here, no special flags are specified)
  // (sockaddr*)&brdcastaddr: Pointer to the broadcast address structure
  // len: Size of the broadcast address structure
  int ret = sendto(s, buffer, strlen(buffer), 0, (sockaddr*)&sad, len);
// =====================================================================================================================
// Old Code

	// StartStream();
	// StreamData((char *)&type_telemetry, sizeof(char));
	// StreamData((char *)&info.mGear, sizeof(long));

	// StreamData((char *)&info.mEngineRPM, sizeof(double));
	// StreamData((char *)&info.mEngineMaxRPM, sizeof(double));
	// StreamData((char *)&info.mEngineWaterTemp, sizeof(double));
	// StreamData((char *)&info.mEngineOilTemp, sizeof(double));
	// StreamData((char *)&info.mClutchRPM, sizeof(double));
	// StreamData((char *)&info.mOverheating, sizeof(bool));
	// StreamData((char *)&info.mFuel, sizeof(double));

	// StreamData((char *)&info.mPos.x, sizeof(double));
	// StreamData((char *)&info.mPos.y, sizeof(double));
	// StreamData((char *)&info.mPos.z, sizeof(double));

// //  Data output in order:  pitch, yaw, roll, Sway/lateral acceleration, Surge/Longitudinal Acceleration, MPH
//   TelemVect3 forwardVector = { -info.mOri[0].z, -info.mOri[1].z, -info.mOri[2].z };
//   TelemVect3 upVector = {  info.mOri[0].y,  info.mOri[1].y,  info.mOri[2].y };
//   TelemVect3 leftVector = {  info.mOri[0].x,  info.mOri[1].x,  info.mOri[2].x };

//   const double radsToDeg = 57.296;  // Radians to Degree conversion 

// //  Calculating and streaming pitch (Order 1)
// 	const double pitch = atan2( forwardVector.y, sqrt( ( forwardVector.x * forwardVector.x) + ( forwardVector.z * forwardVector.z ) ) );
//   const double pitch_out = pitch * radsToDeg;
// 	StreamData((char *)&pitch_out, sizeof(double));

// //  Calculating and streaming Yaw (Order 2)
//   const double yaw = atan2(info.mOri[0].z, info.mOri[2].z);
//   const double yaw_out = yaw * radsToDeg;
// 	StreamData((char *)&yaw_out, sizeof(double));

// //  Calculating and streaming Yaw (Order 3)
//   const double  roll = atan2(leftVector.y, sqrt( (leftVector.x*leftVector.x) + (leftVector.z * leftVector.z )));
//   const double roll_out = roll * radsToDeg;
// 	StreamData((char *)&roll_out, sizeof(double));

// //  Calculating and streaming Yaw (Order 4)
//   const double SwayAcc = -info.mLocalAccel.x;
// 	StreamData((char *)&SwayAcc, sizeof(double));
  
// //  Calculating and streaming Yaw (Order 5)
//   const double SurgeAcc = (info.mLocalAccel.z * -1);
// 	StreamData((char *)&SurgeAcc, sizeof(double));

//   //  Calculating and streaming Speed (Order 6)
// 	const double metersPerSec = sqrt((info.mLocalVel.x * info.mLocalVel.x) +	(info.mLocalVel.y * info.mLocalVel.y) +	(info.mLocalVel.z * info.mLocalVel.z));
// 	StreamData((char *)&metersPerSec, sizeof(double));



//  roll * radsToDeg,  pitch * radsToDeg, info.mLocalAccel.y, yaw * radsToDeg, - info.mLocalAccel.x, - info.mLocalAccel.z);
//     Roll,               Pitch,              HeaveAcc,           Yaw,                SwayAcc,            SurgeAcc

  // StreamData((char *)&info.mLapStartET, sizeof(double));
	// StreamData((char *)&info.mLapNumber, sizeof(long));

	// StreamData((char *)&info.mUnfilteredThrottle, sizeof(double));
	// StreamData((char *)&info.mUnfilteredBrake, sizeof(double));
	// StreamData((char *)&info.mUnfilteredSteering, sizeof(double));
	// StreamData((char *)&info.mUnfilteredClutch, sizeof(double));

	// StreamData((char *)&info.mLastImpactET, sizeof(double));
	// StreamData((char *)&info.mLastImpactMagnitude, sizeof(double));
	// StreamData((char *)&info.mLastImpactPos.x, sizeof(double));
	// StreamData((char *)&info.mLastImpactPos.y, sizeof(double));
	// StreamData((char *)&info.mLastImpactPos.z, sizeof(double));
	// for (long i = 0; i < 8; i++) {
	// 	StreamData((char *)&info.mDentSeverity[i], sizeof(byte));
	// }

	// for (long i = 0; i < 4; i++) {
	// 	const TelemWheelV01 &wheel = info.mWheel[i];
	// 	StreamData((char *)&wheel.mDetached, sizeof(bool));
	// 	StreamData((char *)&wheel.mFlat, sizeof(bool));
	// 	StreamData((char *)&wheel.mBrakeTemp, sizeof(double));
	// 	StreamData((char *)&wheel.mPressure, sizeof(double));
	// 	StreamData((char *)&wheel.mRideHeight, sizeof(double));
	// 	StreamData((char *)&wheel.mTemperature[0], sizeof(double));
	// 	StreamData((char *)&wheel.mTemperature[1], sizeof(double));
	// 	StreamData((char *)&wheel.mTemperature[2], sizeof(double));
	// 	StreamData((char *)&wheel.mWear, sizeof(double));
	// }
	// EndStream();
	log("ending telemetry\n");  //  Records End of Telemetry Data Stream into Log
}

void UDPlugin::Error(const char * const msg)	{log(msg);}
//	Finished Code - Incomplete Comments

void UDPlugin::UpdateScoring(const ScoringInfoV01 &info) {
	// //log("starting update");
	// StartStream();
	// StreamData((char *)&type_scoring, sizeof(char));

	// // session data (changes mostly with changing sessions)
	// StreamString((char *)&info.mTrackName, 64);
	// StreamData((char *)&info.mSession, sizeof(long));

	// // event data (changes continuously)
	// StreamData((char *)&info.mCurrentET, sizeof(double));
	// StreamData((char *)&info.mEndET, sizeof(double));
	// StreamData((char *)&info.mLapDist, sizeof(double));
	// StreamData((char *)&info.mNumVehicles, sizeof(long));

	// StreamData((char *)&info.mGamePhase, sizeof(byte));
	// StreamData((char *)&info.mYellowFlagState, sizeof(byte));
	// StreamData((char *)&info.mSectorFlag[0], sizeof(byte));
	// StreamData((char *)&info.mSectorFlag[1], sizeof(byte));
	// StreamData((char *)&info.mSectorFlag[2], sizeof(byte));
	// StreamData((char *)&info.mStartLight, sizeof(byte));
	// StreamData((char *)&info.mNumRedLights, sizeof(byte));

	// // scoring data (changes with new sector times)
	// for (long i = 0; i < info.mNumVehicles; i++) {
	// 	VehicleScoringInfoV01 &vinfo = info.mVehicle[i];
	// 	StreamData((char *)&vinfo.mPos.x, sizeof(double));
	// 	StreamData((char *)&vinfo.mPos.z, sizeof(double));
	// 	StreamData((char *)&vinfo.mPlace, sizeof(char));
	// 	StreamData((char *)&vinfo.mLapDist, sizeof(double));
	// 	StreamData((char *)&vinfo.mPathLateral, sizeof(double));
	// 	const double metersPerSec = sqrt((vinfo.mLocalVel.x * vinfo.mLocalVel.x) +
	// 		(vinfo.mLocalVel.y * vinfo.mLocalVel.y) +
	// 		(vinfo.mLocalVel.z * vinfo.mLocalVel.z));
	// 	StreamData((char *)&metersPerSec, sizeof(double));
	// 	StreamString((char *)&vinfo.mVehicleName, 64);
	// 	StreamString((char *)&vinfo.mDriverName, 32);
	// 	StreamString((char *)&vinfo.mVehicleClass, 32);
	// 	StreamData((char *)&vinfo.mTotalLaps, sizeof(short));
	// 	StreamData((char *)&vinfo.mBestSector1, sizeof(double));
	// 	StreamData((char *)&vinfo.mBestSector2, sizeof(double));
	// 	StreamData((char *)&vinfo.mBestLapTime, sizeof(double));
	// 	StreamData((char *)&vinfo.mLastSector1, sizeof(double));
	// 	StreamData((char *)&vinfo.mLastSector2, sizeof(double));
	// 	StreamData((char *)&vinfo.mLastLapTime, sizeof(double));
	// 	StreamData((char *)&vinfo.mCurSector1, sizeof(double));
	// 	StreamData((char *)&vinfo.mCurSector2, sizeof(double));
	// 	StreamData((char *)&vinfo.mTimeBehindLeader, sizeof(double));
	// 	StreamData((char *)&vinfo.mLapsBehindLeader, sizeof(long));
	// 	StreamData((char *)&vinfo.mTimeBehindNext, sizeof(double));
	// 	StreamData((char *)&vinfo.mLapsBehindNext, sizeof(long));
	// 	StreamData((char *)&vinfo.mNumPitstops, sizeof(short));
	// 	StreamData((char *)&vinfo.mNumPenalties, sizeof(short));
	// 	StreamData((char *)&vinfo.mInPits, sizeof(bool));
	// 	StreamData((char *)&vinfo.mSector, sizeof(char));
	// 	StreamData((char *)&vinfo.mFinishStatus, sizeof(char));
	// }
	// StreamVarString((char *)info.mResultsStream);
	// EndStream();
	// //log("ending update\n");
}
//  Mostly finished Code and incomplete comments

//	Functions for streaming data
void UDPlugin::StartStream() {
	data_packet = 0;
	data_sequence++;
	data[0] = data_version;
	data[1] = data_packet;
	memcpy(&data[2], &data_sequence, sizeof(short));
	data_offset = 4;
}
//  Mostly finished Code and incomplete comments

void UDPlugin::StreamData(char *data_ptr, int length) {
	int i;

	for (i = 0; i < length; i++) {
		if (data_offset + i == 512) {
			sendto(s, data, 512, 0, (struct sockaddr *) &sad, sizeof(struct sockaddr));
			data_packet++;
			data[0] = data_version;
			data[1] = data_packet;
			memcpy(&data[2], &data_sequence, sizeof(short));
			data_offset = 4;
			length = length - i;
			data_ptr += i;
			i = 0;
		}
		data[data_offset + i] = data_ptr[i];
	}
	data_offset = data_offset + length;
}
//  Mostly finished Code and incomplete comments

void UDPlugin::StreamVarString(char *data_ptr) {
	int i = 0;
	while (data_ptr[i] != 0) {
		i++;
	}
	StreamData((char *)&i, sizeof(int));
	StreamString(data_ptr, i);
}
//  Mostly finished Code and incomplete comments

void UDPlugin::StreamString(char *data_ptr, int length) {
	int i;

	for (i = 0; i < length; i++) {
		if (data_offset + i == 512) {
			sendto(s, data, 512, 0, (struct sockaddr *) &sad, sizeof(struct sockaddr));
			data_packet++;
			data[0] = data_version;
			data[1] = data_packet;
			memcpy(&data[2], &data_sequence, sizeof(short));
			data_offset = 4;
			length = length - i;
			data_ptr += i;
			i = 0;
		}
		data[data_offset + i] = data_ptr[i];
		if (data_ptr[i] == 0) {
			// found end of string, so this is where we stop
			data_offset = data_offset + i + 1;
			return;
		}
	}
	data_offset = data_offset + length;
}
//  Mostly finished Code and incomplete comments

void UDPlugin::EndStream() {
	if (data_offset > 4) {
		sendto(s, data, data_offset, 0, (struct sockaddr *) &sad, sizeof(struct sockaddr));
	}
}
//  Mostly finished Code and incomplete comments

//	Had to call due to errors during compilation
bool UDPlugin::CheckHWControl( const char * const controlName, double &fRetVal ) { return false;}

bool UDPlugin::ForceFeedback( double &forceValue )
  {
    // CHANGE COMMENTS TO ENABLE FORCE EXAMPLE
    return( false );

    // I think the bounds are -11500 to 11500 ...
  //  forceValue = 11500.0 * sinf( mET );
  //  return( true );
  }

bool UDPlugin::RequestCommentary( CommentaryRequestInfoV01 &info )
  {
    // COMMENT OUT TO ENABLE EXAMPLE
    return( false );

    // only if enabled, of course
    if( !mEnabled )
      return( false );

    // Note: function is called twice per second

    // Say green flag event for no particular reason every 20 seconds ...
    const double timeMod20 = fmod( mET, 20.0 );
    if( timeMod20 > 19.0 )
    {
      strcpy( info.mName, "GreenFlag" );
      info.mInput1 = 0.0;
      info.mInput2 = 0.0;
      info.mInput3 = 0.0;
      info.mSkipChecks = true;
      return( true );
    }
  }

bool UDPlugin::WantsToDisplayMessage(MessageInfoV01 &msgInfo) {return false;}
//	Finished Code - Incomplete Comments

unsigned char UDPlugin::WantsToViewVehicle(CameraControlInfoV01 &camControl) {return 0;}
//	Finished Code - Incomplete Comments


/* Example Plugin Code that is changed----------------------------------------------------------------------------------------------------------

  //###########################################################################
  //#                                                                         #
  //# Module: Internals Example Source File                                   #
  //#                                                                         #
  //# Description: Declarations for the Internals Example Plugin              #
  //#                                                                         #
  //#                                                                         #
  //# This source code module, and all information, data, and algorithms      #
  //# associated with it, are part of CUBE technology (tm).                   #
  //#                 PROPRIETARY AND CONFIDENTIAL                            #
  //# Copyright (c) 2018 Studio 397 B.V.  All rights reserved.                #
  //#                                                                         #
  //###########################################################################

  #include "Example.hpp"          // corresponding header file

  // ExampleInternalsPlugin class


  void ExampleInternalsPlugin::Startup( long version )
  {
    char temp[80];
    sprintf( temp, "-STARTUP- (version %.3f)", (float) version / 1000.0f );

    // Open ports, read configs, whatever you need to do.  For now, I'll just clear out the
    // example output data files.
    WriteToFiles( "w", temp );

    // default HW control enabled to true
    mEnabled = true;
  }


  Example Plugin Shutdown
  void ExampleInternalsPlugin::Shutdown()
  {
    WriteToFiles( "a", "-SHUTDOWN-" );
  }


  void ExampleInternalsPlugin::StartSession()
  {
    WriteToFiles( "a", "--STARTSESSION--" );
  }


  void ExampleInternalsPlugin::EndSession()
  {
    WriteToFiles( "a", "--ENDSESSION--" );
  }


  void ExampleInternalsPlugin::EnterRealtime()
  {
    // start up timer every time we enter realtime
    mET = 0.0;
    WriteToFiles( "a", "---ENTERREALTIME---" );
  }

  void ExampleInternalsPlugin::UpdateTelemetry( const TelemInfoV01 &info )
  {
    // Use the incoming data, for now I'll just write some of it to a file to a) make sure it
    // is working, and b) explain the coordinate system a little bit (see header for more info)
    FILE *fo = fopen( "TelemetryOutput.txt", "a" );
    if( fo != NULL )  {
      // Delta time is variable, as we send out the info once per frame
      fprintf( fo, "DT=%.4f  ET=%.4f\n", info.mDeltaTime, info.mElapsedTime );
      fprintf( fo, "Lap=%d StartET=%.3f\n", info.mLapNumber, info.mLapStartET );
      fprintf( fo, "Vehicle=%s\n", info.mVehicleName );
      fprintf( fo, "Track=%s\n", info.mTrackName );
      fprintf( fo, "Pos=(%.3f,%.3f,%.3f)\n", info.mPos.x, info.mPos.y, info.mPos.z );

      // Forward is roughly in the -z direction (although current pitch of car may cause some y-direction velocity)
      fprintf( fo, "LocalVel=(%.2f,%.2f,%.2f)\n", info.mLocalVel.x, info.mLocalVel.y, info.mLocalVel.z );
      fprintf( fo, "LocalAccel=(%.1f,%.1f,%.1f)\n", info.mLocalAccel.x, info.mLocalAccel.y, info.mLocalAccel.z );

      // Orientation matrix is left-handed
      fprintf( fo, "[%6.3f,%6.3f,%6.3f]\n", info.mOri[0].x, info.mOri[0].y, info.mOri[0].z );
      fprintf( fo, "[%6.3f,%6.3f,%6.3f]\n", info.mOri[1].x, info.mOri[1].y, info.mOri[1].z );
      fprintf( fo, "[%6.3f,%6.3f,%6.3f]\n", info.mOri[2].x, info.mOri[2].y, info.mOri[2].z );
      fprintf( fo, "LocalRot=(%.3f,%.3f,%.3f)\n", info.mLocalRot.x, info.mLocalRot.y, info.mLocalRot.z );
      fprintf( fo, "LocalRotAccel=(%.2f,%.2f,%.2f)\n", info.mLocalRotAccel.x, info.mLocalRotAccel.y, info.mLocalRotAccel.z );

      // Vehicle status
      fprintf( fo, "Gear=%d RPM=%.1f RevLimit=%.1f\n", info.mGear, info.mEngineRPM, info.mEngineMaxRPM );
      fprintf( fo, "Water=%.1f Oil=%.1f\n", info.mEngineWaterTemp, info.mEngineOilTemp );
      fprintf( fo, "ClutchRPM=%.1f\n", info.mClutchRPM );

      // Driver input
      fprintf( fo, "UnfilteredThrottle=%.1f%%\n", 100.0 * info.mUnfilteredThrottle );
      fprintf( fo, "UnfilteredBrake=%.1f%%\n", 100.0 * info.mUnfilteredBrake );
      fprintf( fo, "UnfilteredSteering=%.1f%%\n", 100.0 * info.mUnfilteredSteering );
      fprintf( fo, "UnfilteredClutch=%.1f%%\n", 100.0 * info.mUnfilteredClutch );

      // Filtered input
      fprintf( fo, "FilteredThrottle=%.1f%%\n", 100.0 * info.mFilteredThrottle );
      fprintf( fo, "FilteredBrake=%.1f%%\n", 100.0 * info.mFilteredBrake );
      fprintf( fo, "FilteredSteering=%.1f%%\n", 100.0 * info.mFilteredSteering );
      fprintf( fo, "FilteredClutch=%.1f%%\n", 100.0 * info.mFilteredClutch );

      // Misc
      fprintf( fo, "SteeringShaftTorque=%.1f\n", info.mSteeringShaftTorque );
      fprintf( fo, "Front3rdDeflection=%.3f Rear3rdDeflection=%.3f\n", info.mFront3rdDeflection, info.mRear3rdDeflection );

      // Aerodynamics
      fprintf( fo, "FrontWingHeight=%.3f FrontRideHeight=%.3f RearRideHeight=%.3f\n", info.mFrontWingHeight, info.mFrontRideHeight, info.mRearRideHeight );
      fprintf( fo, "Drag=%.1f FrontDownforce=%.1f RearDownforce=%.1f\n", info.mDrag, info.mFrontDownforce, info.mRearDownforce );

      // Other
      fprintf( fo, "Fuel=%.1f ScheduledStops=%d Overheating=%d Detached=%d\n", info.mFuel, info.mScheduledStops, info.mOverheating, info.mDetached );
      fprintf( fo, "Dents=(%d,%d,%d,%d,%d,%d,%d,%d)\n", info.mDentSeverity[0], info.mDentSeverity[1], info.mDentSeverity[2], info.mDentSeverity[3],
                                                        info.mDentSeverity[4], info.mDentSeverity[5], info.mDentSeverity[6], info.mDentSeverity[7] );
      fprintf( fo, "LastImpactET=%.1f Mag=%.1f, Pos=(%.1f,%.1f,%.1f)\n", info.mLastImpactET, info.mLastImpactMagnitude,
              info.mLastImpactPos.x, info.mLastImpactPos.y, info.mLastImpactPos.z );

      // Wheels
      for( long i = 0; i < 4; ++i )
      {
        const TelemWheelV01 &wheel = info.mWheel[i];
        fprintf( fo, "Wheel=%s\n", (i==0)?"FrontLeft":(i==1)?"FrontRight":(i==2)?"RearLeft":"RearRight" );
        fprintf( fo, " SuspensionDeflection=%.3f RideHeight=%.3f\n", wheel.mSuspensionDeflection, wheel.mRideHeight );
        fprintf( fo, " SuspForce=%.1f BrakeTemp=%.1f BrakePressure=%.3f\n", wheel.mSuspForce, wheel.mBrakeTemp, wheel.mBrakePressure );
        fprintf( fo, " ForwardRotation=%.1f Camber=%.3f\n", -wheel.mRotation, wheel.mCamber );
        fprintf( fo, " LateralPatchVel=%.2f LongitudinalPatchVel=%.2f\n", wheel.mLateralPatchVel, wheel.mLongitudinalPatchVel );
        fprintf( fo, " LateralGroundVel=%.2f LongitudinalGroundVel=%.2f\n", wheel.mLateralGroundVel, wheel.mLongitudinalGroundVel );
        fprintf( fo, " LateralForce=%.1f LongitudinalForce=%.1f\n", wheel.mLateralForce, wheel.mLongitudinalForce );
        fprintf( fo, " TireLoad=%.1f GripFract=%.3f TirePressure=%.1f\n", wheel.mTireLoad, wheel.mGripFract, wheel.mPressure );
        fprintf( fo, " TireTemp(l/c/r)=%.1f/%.1f/%.1f\n", wheel.mTemperature[0], wheel.mTemperature[1], wheel.mTemperature[2] );
        fprintf( fo, " Wear=%.3f TerrainName=%s SurfaceType=%d\n", wheel.mWear, wheel.mTerrainName, wheel.mSurfaceType );
        fprintf( fo, " Flat=%d Detached=%d\n", wheel.mFlat, wheel.mDetached );
      }

      // Compute some auxiliary info based on the above
      TelemVect3 forwardVector = { -info.mOri[0].z, -info.mOri[1].z, -info.mOri[2].z };
      TelemVect3    leftVector = {  info.mOri[0].x,  info.mOri[1].x,  info.mOri[2].x };

      // These are normalized vectors, and remember that our world Y coordinate is up.  So you can
      // determine the current pitch and roll (w.r.t. the world x-z plane) as follows:
      const double pitch = atan2( forwardVector.y, sqrt( ( forwardVector.x * forwardVector.x ) + ( forwardVector.z * forwardVector.z ) ) );
      const double  roll = atan2(    leftVector.y, sqrt( (    leftVector.x *    leftVector.x ) + (    leftVector.z *    leftVector.z ) ) );
      const double radsToDeg = 57.296;
      fprintf( fo, "Pitch = %.1f deg, Roll = %.1f deg\n", pitch * radsToDeg, roll * radsToDeg );

      const double metersPerSec = sqrt( ( info.mLocalVel.x * info.mLocalVel.x ) +
                                        ( info.mLocalVel.y * info.mLocalVel.y ) +
                                        ( info.mLocalVel.z * info.mLocalVel.z ) );
      fprintf( fo, "Speed = %.1f KPH, %.1f MPH\n\n", metersPerSec * 3.6, metersPerSec * 2.237 );

      if (info.mElectricBoostMotorState != 0)
      {
        fprintf( fo, "ElectricBoostMotor:");
        char const* const states[] = {"N/A", "Inactive", "Propulsion", "Regeneration"};
        fprintf( fo, " State = %s\n", states[info.mElectricBoostMotorState]);
        fprintf( fo, " Torque = %g nm\n", info.mElectricBoostMotorTorque);
        fprintf( fo, " RPM = %g\n", info.mElectricBoostMotorRPM);
        fprintf( fo, " Motor Temperature = %g C\n", info.mElectricBoostMotorTemperature);
        if (info.mElectricBoostMotorTemperature != 0)
          fprintf( fo, " Water Temperature = %g C\n", info.mElectricBoostWaterTemperature);
      }

      // Close file
      fclose( fo );
    }
  }

  void ExampleInternalsPlugin::UpdateGraphics( const GraphicsInfoV01 &info )
  {
    // Use the incoming data, for now I'll just write some of it to a file to a) make sure it
    // is working, and b) explain the coordinate system a little bit (see header for more info)
    FILE *fo = fopen( "GraphicsOutput.txt", "a" );
    if( fo != NULL ) {
      // Print stuff
      fprintf( fo, "CamPos=(%.1f,%.1f,%.1f)\n", info.mCamPos.x, info.mCamPos.y, info.mCamPos.z );
      fprintf( fo, "CamOri[0]=(%.1f,%.1f,%.1f)\n", info.mCamOri[0].x, info.mCamOri[0].y, info.mCamOri[0].z );
      fprintf( fo, "CamOri[1]=(%.1f,%.1f,%.1f)\n", info.mCamOri[1].x, info.mCamOri[1].y, info.mCamOri[1].z );
      fprintf( fo, "CamOri[2]=(%.1f,%.1f,%.1f)\n", info.mCamOri[2].x, info.mCamOri[2].y, info.mCamOri[2].z );
      fprintf( fo, "HWND=%d\n", info.mHWND );
      fprintf( fo, "Ambient Color=(%.1f,%.1f,%.1f)\n\n", info.mAmbientRed, info.mAmbientGreen, info.mAmbientBlue );

      // Close file
      fclose( fo );
    }
  }

  bool ExampleInternalsPlugin::RequestCommentary( CommentaryRequestInfoV01 &info )
  {
    // COMMENT OUT TO ENABLE EXAMPLE
    return( false );

    // only if enabled, of course
    if( !mEnabled )
      return( false );

    // Note: function is called twice per second

    // Say green flag event for no particular reason every 20 seconds ...
    const double timeMod20 = fmod( mET, 20.0 );
    if( timeMod20 > 19.0 )
    {
      strcpy( info.mName, "GreenFlag" );
      info.mInput1 = 0.0;
      info.mInput2 = 0.0;
      info.mInput3 = 0.0;
      info.mSkipChecks = true;
      return( true );
    }

    return( false );
  }

    bool ExampleInternalsPlugin::CheckHWControl( const char * const controlName, double &fRetVal )
  {
    // only if enabled, of course
    if( !mEnabled )
      return( false );

    // Note that incoming value is the game's computation, in case you're interested.

    // Sorry, no control allowed over actual vehicle inputs ... would be too easy to cheat!
    // However, you can still look at the values.

    // Note: since the game calls this function every frame for every available control, you might consider
    // doing a binary search if you are checking more than 7 or 8 strings, just to keep the speed up.
    if( _stricmp( controlName, "LookLeft" ) == 0 )
    {
      const double headSwitcheroo = fmod( mET, 2.0 );
      if( headSwitcheroo < 0.5 )
        fRetVal = 1.0;
      else
        fRetVal = 0.0;
      return( true );
    }
    else if( _stricmp( controlName, "LookRight" ) == 0 )
    {
      const double headSwitcheroo = fmod( mET, 2.0 );
      if( ( headSwitcheroo > 1.0 ) && ( headSwitcheroo < 1.5 ) )
        fRetVal = 1.0;
      else
        fRetVal = 0.0;
      return( true );
    }

    return( false );
  }


  bool ExampleInternalsPlugin::ForceFeedback( double &forceValue )
  {
    // CHANGE COMMENTS TO ENABLE FORCE EXAMPLE
    return( false );

    // I think the bounds are -11500 to 11500 ...
  //  forceValue = 11500.0 * sinf( mET );
  //  return( true );
  }
----------------------------------------------------------------------------------------------------------*/