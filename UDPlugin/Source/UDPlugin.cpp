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
║              ║ V1) File: rFactor 2 Output -> .csv file -> Arduino (Alex Code) -> Actuation (Too high Latency). ║
║    Plugin    ║ V2) Memory Buffer: Stored data in the memory buffer then accessed by arduino (missing data).    ║
║   Versions   ║ V3) TCP/UDP V1: Send data via TCP/UDP port (Detected as Intrusive by game/caused crashing).     ║
║              ║ V4) UDP V2: Aided in work-around by <redacted>* - Current Version.                              ║
║              ║ *Asked to keep said person & work-around anonymous to prevent proliferation of said work-around.║
╠══════════════╩═════════════════════════════════════════════════════════════════════════════════════════════════╣
║ Adapted from source code, information, data, and algorithms belonging to CUBE technology (tm) which form the   ║
║ the Example Plugin V8 for rFactor2, made available by Studio 397 in the form of a zip file within their forums.║
║        Download found in modding resources section here: https://www.studio-397.com/modding-resources/         ║
║            PROPRIETARY AND CONFIDENTIAL -  Copyright (c) 2018 Studio 397 B.V.  All rights reserved.            ║
║                                                   ╔═══════╗                                                    ║
╠═══════════════════════════════════════════════════╝ Notes ╚════════════════════════════════════════════════════╣
║                                                                                                                ║
║	-	Tab Size:	4 | Plugin Language: C++ | Sends Data to C# Program | Data via UDP: Sent as ascii hexcode    ║
║                                                                                                                ║
║	-	Formatting:	| Max Column - 118 | ═════ Title ═════ | _____Section_Split_____                             ║
║                                                                                                                ║
║	-	Commenting:	| If fits in 118 column max // on same line | If too long, /* across multiple lines before   ║
║                                                                                                                ║
║	-	"ctrl + /":	Visual Studio Code shortcut to comment selected line/s, eases enabling and disabling of      ║
║					features.                                                                                    ║
║                                                                                                                ║
║	-	Compiling:	Use of Visual Studio Express 2012 (free via microsoft coding insider programmer) used to     ║
║					compile, but compiling possibly through Visual Studio Code via Bash terminal using (check if ║
║                   plugin compiles/error testing):  															 ║
║                                                                                                                ║
║		1)	g++ -c -fPIC file.cpp -o file.o			//  Created object file that can be converted to a .dll      ║
║                                                                                                                ║
║		2a)	g++ -shared -o file.dll file.o			//  Compilation of Object file into a .dll                   ║
║			g++ -shared -o file.dll file.o -lWs2_32	//  Missing Library: Winsock library Manual link (UDP)	     ║
║                                                                                                                ║
║	- 	Compiling done using Visual Studio Express 2012 which is free via Visual Studio Dev Essentials service:  ║
╠═══════════════════════════════════════════════════╝ ASCII ╚════════════════════════════════════════════════════╣
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
║				Feel free to collapse the above welcome comment to make it easier to navigate file               ║
╚════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝*/
//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▓■ ●ஜ۩۞۩ஜ● ■▓▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀


/*______________________________________________________________________________________________________________
════════════════════════════════════════════ Libraries & Definitions ════════════════════════════════════════════*/
//	Include necessary header files for UDP connection, Windows API, and standard libraries
#include <WinSock2.h>           // required library for UDP connection
#include <Windows.h>
#include "UDPlugin.hpp"         // corresponding header file
#include <math.h>               // for mathematical functions like atan2, sqrt
#include <stdio.h>              // for standard input/output operations
#include <assert.h>             // for assertion macros
#include <io.h>                 // for low-level I/O functions
#include <sys/stat.h>           // for file status functions
#include <string.h>             // for string manipulation functions
#include <sys/types.h>          // for data types used in system calls
#include <time.h>               // for time-related functions, such as getting current time
#include <cstring>				// For strlen
#include <limits>				// For INT_MAX

#include <WS2tcpip.h>           // additional library for TCP/IP functionality

#define TIME_LENGTH 26          // Define the length of the time string
//	UDPlugin::UDPlugin(){}
//	UDPlugin::~UDPlugin(){}

/*______________________________________________________________________________________________________________
══════════════════════════════════════════════ Plugin Information ══════════════════════════════════════════════*/

extern "C" __declspec( dllexport )  // Sets Plugin Name.
const char * __cdecl GetPluginName()                   { return("UDPlugin - 2024.04.08"); } 

extern "C" __declspec( dllexport )  // Plugin Object Type - See PluginObjects.hpp lines 30-41 for all types.
PluginObjectType __cdecl GetPluginType()               { return(PO_INTERNALS); }  

extern "C" __declspec( dllexport )  // InternalsPluginV01 functionality if return value changed, you must derive.   
int __cdecl GetPluginVersion()                         { return(6); } // from the appropriate class (1-7)!   
                                                                        
extern "C" __declspec( dllexport )
PluginObject * __cdecl CreatePluginObject()            { return( (PluginObject *) new UDPlugin ); }

extern "C" __declspec( dllexport )
void __cdecl DestroyPluginObject( PluginObject *obj )  { delete( (UDPlugin *) obj ); }

/*______________________________________________________________________________________________________________
═══════════════════════════════════════════════ File & Logging ════════════════════════════════════════════════*/

/*______________________________________________________________________________________________________________
╔═════════════╦══════════════╗
║   Function  ║ WriteToFiles ║
╠═════════════╬══════════════╩══════════════════════════════════════════════════════════════════════════════╗
║ Description ║ Writes timestamped message/data (Telemetry, Graphics, Scoring) to individual text files.    ║
╠═════════════╬═════════════════════════════════════════════════════════════════════════════════════════════╣
║  Parameters ║ openStr:	Mode in which to open files ("w" for write, "a" for append, etc.).              ║
║▀▀▀▀▀▀▀▀▀▀▀▀▀║ msg:		Contains the message to be written.                                             ║
╚═════════════╩═════════════════════════════════════════════════════════════════════════════════════════════╝*/
void UDPlugin::WriteToFiles( const char * const openStr, const char * const msg )
{
	FILE *TelemFile;             								//	Pointer to FILE object for file access.
	time_t curtime;                                       		//  Variable to store the current time.
	struct tm loctime;											//  Pointer to tm structure for converting time.
	char thetime[TIME_LENGTH];									//	Buffer to hold formatted time string

//	// 	Uncomment and change TelemPath to save to a specific location
	// 	const char* TelemPath = "C:\\Users\\Mathew\\Desktop\\rF2_data_files\\Telemetry.txt";
	// 	int telem = fopen_s(&TelemFile, TelemPath, openStr ); // Open 'Telemetry.txt', mode specified by openStr.

//	Saves to rFactor 2 steam folder under the name Telemetry.txt
	int telem = fopen_s(&TelemFile, "Telemetry.txt", openStr ); // Open Telemetry.txt, mode specified by openStr.

	if(telem == 0)  {											// Check if the file was successfully opened.
		curtime = time(NULL);                       			// Get the current time.
		int telem2 = localtime_s(&loctime, &curtime);			// Convert current time to local time
		int telem3 = asctime_s(thetime, TIME_LENGTH, &loctime);	// Convert local time to formatted string     
		thetime[TIME_LENGTH - 2] = 0;							// Remove newline character from time string                           
			
		fprintf(TelemFile, "[%s] %s\n", thetime, msg);	// Writes message to file with corresponding timestamp.  
		fclose(TelemFile);								// Close file to flush stream & release resources.
	}
	
// // Uncomment to enable Graphics Output Data being written to a corresponding text file.
// fo = fopen( "GraphicsOutput.txt", openStr );
// if( fo != NULL )  {                            // Check if the file was successfully opened.
//   curtime = time(NULL);                        // Get the current time.
// 	loctime = localtime(&curtime);               // Convert current time to local time.
    
// fprintf( fo, "[%s] %s\n", asctime (loctime), msg);//Write the timestamped message to "TelemetryOutput.txt".  
// fclose( fo );                                    //Close the file to flush the stream and release resources.
// }
  
// // Uncomment to enable Scoring Output Data being written to a corresponding text file
// fo = fopen( "ScoringOutput.txt", openStr );
// if( fo != NULL )  {                            // Check if the file was successfully opened.
//   curtime = time(NULL);                        // Get the current time.
// 	loctime = localtime(&curtime);               // Convert current time to local time.
    
//   fprintf( fo, "[%s] %s\n", asctime (loctime), msg);// Write the timestamped message to "TelemetryOutput.txt"  
//   fclose( fo );                                   // Close the file to flush the stream and release resources
// }

}
//	Finished Code & Comments


/*______________________________________________________________________________________________________________
╔═════════════╦═════╗
║   Function  ║ log ║
╠═════════════╬═════╩═══════════════════════════════════════════════════════════════════════════════════════╗
║ Description ║ Logs timestamped message/data to an individual .log file.                                   ║
╠═════════════╬═════════════════════════════════════════════════════════════════════════════════════════════╣
║  Parameters ║ msg: Contains the message to be written.                                                    ║
╚═════════════╩═════════════════════════════════════════════════════════════════════════════════════════════╝*/
void UDPlugin::log( const char * const openStr, const char *msg) {   

    // Define the full path for the log file - Change to suit needs
    // const char* logPath = "C:\\Users\\Mathew\\Desktop\\rF2_data_files\\UDPlugin.log";

    FILE *logFile;											//  Pointer to FILE object for log file access
    time_t curtime;											//  Variable to store the current time
    struct tm loctime;										//  Pointer to tm structure for converting time
    char thetime[TIME_LENGTH];								//	Buffer to hold formatted time string

    // Open the log file in append mode ("a"). If the file doesn't exist, it will be created.
    int err = fopen_s(&logFile, "UDPlugin.log", openStr);		//	Attempt to open or create log file    
    if (err == 0) {											//  Check if the file was successfully opened
      curtime = time(NULL);									//  Get the current time
      int err2 = localtime_s(&loctime, &curtime);			//	Convert current time to local time
      int err3 = asctime_s(thetime, TIME_LENGTH, &loctime); //	Convert local time to formatted string    
      thetime[TIME_LENGTH - 2] = 0;							//	Remove newline character from time string 
		   
fprintf(logFile, "[%s] %s\n", thetime, msg);				//	Writes message to file with corresponding timestamp  
      fclose(logFile);										//	Close file to flush stream & release resources
	}
}
//  Finished Code & Comments


/*______________________________________________________________________________________________________________
╔═════════════╦═══════╗
║   Function  ║ Error ║
╠═════════════╬═══════╩═════════════════════════════════════════════════════════════════════════════════════╗
║ Description ║ Logs any errors that occur into the .log file                                               ║
╠═════════════╬═════════════════════════════════════════════════════════════════════════════════════════════╣
║  Parameters ║ msg: Contains the message to be written                                                     ║
╚═════════════╩═════════════════════════════════════════════════════════════════════════════════════════════╝*/
void UDPlugin::Error(const char * const msg)	{log("a", msg);}	//  adds error message to log file

//═════════════════════════════════════════════ Startup & Stages ═══════════════════════════════════════════════
/*______________________________________________________________________________________________________________
╔═════════════╦═════════╗
║   Function  ║ Startup ║
╠═════════════╬═════════╩═══════════════════════════════════════════════════════════════════════════════════╗
║ Description ║ Initiates the plugin, acquired server settings file if applicable, then connects to the     ║
║▀▀▀▀▀▀▀▀▀▀▀▀▀║ the socket with either the given settings or default settings.                              ║
╠═════════════╬═════════════════════════════════════════════════════════════════════════════════════════════╣
║  Parameters ║ version: Contains current version of plugin * 1000                                          ║
╚═════════════╩═════════════════════════════════════════════════════════════════════════════════════════════╝*/
void UDPlugin::Startup(long version) 
{ 
	//  Change directory to relevant location if .ini has been created
	const char* SettingsPath = "C:\\Users\\Mathew\\Desktop\\rF2_data_files\\UDPlugin.ini";
	FILE *settings;				// Pointer to FILE object for settings file access
	// struct hostent *ptrh;	// Pointer to hostent structure (commented out, not used in this version)
	data_version = 1;			// Assigning data_version variable a value of 1
	char portstring[10];		// Character array to store port number as string

	ADDRINFO hints = { sizeof(addrinfo) };	// Initialize ADDRINFO structure with size
	hints.ai_flags = AI_ALL;				// Specify AI_ALL flag for address resolution
	hints.ai_family = PF_INET;				// Specify IPv4 address family
	hints.ai_protocol = IPPROTO_IPV4;		// Specify IPv4 protocol
	ADDRINFO *pResult = NULL;				// Pointer to ADDRINFO structure for address resolution result

	//	Records Startup into the output & Log files with timestamps
	char temp[90];							// Character array to store formatted startup message
											// (below) Format startup message with version number
	sprintf( temp, "--Starting Plugin-- (version %.3f)", (float) version / 1000.0f );	
	WriteToFiles( "w", temp);				// Write startup message to output files
	log("w", temp);							//  Records Startup into Log with timestamp 

	// open socket
	s = socket(PF_INET, SOCK_DGRAM, 0);					// Create datagram socket
	if (s < 0) {
		log("a", "could not create datagram socket");		// Log error message if socket creation fails
		return;
	}

	int err = fopen_s(&settings, SettingsPath, "r");	// Open settings file for reading
	if (err == 0) {
			
			log("a", "reading settings");	// Log message indicating settings file is being read
			
			if (fscanf_s(settings, "%[^:]:%i", hostname, _countof(hostname), &port) != 2)	{
				// Log error message if reading host and port from settings file fails
				log("a", "could not read host and port");
			}
				
			//ptrh = gethostbyname(hostname);	//  used with previous approach, kept for possible future use
			
			//	Log message indicating settings have been successfully read from file
			log("a", "settings read from file");
			
			int errcode = getaddrinfo(hostname, NULL, &hints, &pResult);	// Resolve host name to IP address

			fclose(settings);		// Close settings file

			log("a", "hostname is:");				// Log hostname 1/2
			log("a", hostname);						// Log hostname	2/2
			log("a", "port is:");					// Log port number
			sprintf_s(portstring, "%i", port);	// Convert port number to string
			log("a", portstring);					// Log port number
	}
	else	{
			// Log message indicating default settings are being used
			log("a", "could not read settings, using defaults: localhost:10815");
			
			//  used with previous approach, kept for possible future use
			//ptrh = gethostbyname("localhost");// Convert host name to equivalent IP address and copy to sad.  

			// Resolve default host name to IP address
			int errcode = getaddrinfo("localhost", NULL, &hints, &pResult);

			port = 10815;						// Set default port number
	}

	memset((char *)&sad, 0, sizeof(sad));       //  clear sockaddr structure 
	sad.sin_family = AF_INET;                   //  set family to Internet   
	sad.sin_port = htons((u_short)port);      	//  originally 6789 but changed to 10815

//	Assigns the IPv4 address obtained from address resolution to the sin_addr member of the sockaddr_in structure
	sad.sin_addr.S_un.S_addr = *((ULONG*)&(((sockaddr_in*)pResult->ai_addr)->sin_addr));    

	//  Old Code used with alternative method, could still possibly be useful for future applications.
	// memcpy(&sad.sin_addr, ptrh->h_addr, ptrh->h_length);
	// mEnabled = true;  // default HW control enabled to true
}
//  Finished Code & Comments


/*______________________________________________________________________________________________________________
╔═════════════╦══════════╗
║   Function  ║ Shutdown ║
╠═════════════╬══════════╩══════════════════════════════════════════════════════════════════════════════════╗
║ Description ║ Closes the UDP socket and shuts down the plugin.                                            ║
╚═════════════╩═════════════════════════════════════════════════════════════════════════════════════════════╝*/
void UDPlugin::Shutdown() {
  if (s > 0) {									//  Checks to see if socket is active
    closesocket(s);								//  If active, closes the socket
    s = 0;										//  Sets socket to equal 0
  }
    
  WriteToFiles( "a", "--Shutting Down--" );		//  Writes Shutdown message to enabled output files
  log("a", "--Shutting Down--" );              		//  Records Shutdown into Log 
} 
//  Finished Code & Comments


/*______________________________________________________________________________________________________________
╔═════════════╦══════════════╗
║   Function  ║ StartSession ║
╠═════════════╬══════════════╩══════════════════════════════════════════════════════════════════════════════╗
║ Description ║ Executes code/commands when session starts - Logging session start in files currently       ║
╚═════════════╩═════════════════════════════════════════════════════════════════════════════════════════════╝*/
void UDPlugin::StartSession()
{
	WriteToFiles( "a", "--START SESSION--" );	//  Writes Session Start message to enabled output files
	log("a", "--START SESSION--" );					//  Records Session Start into Log   
}
//  Finished Code & Comments


/*______________________________________________________________________________________________________________
╔═════════════╦════════════╗
║   Function  ║ EndSession ║
╠═════════════╬════════════╩════════════════════════════════════════════════════════════════════════════════╗
║ Description ║ Executes code/commands when session ends - Loggs session end in files.						║
╚═════════════╩═════════════════════════════════════════════════════════════════════════════════════════════╝*/
void UDPlugin::EndSession()
{
	WriteToFiles( "a", "--END SESSION--" );	//  Writes Session End message to enabled output files
	log("a", "---END SESSION--" );				//  Records Session End into Log
}
//  Finished Code & Comments


/*______________________________________________________________________________________________________________
╔═════════════╦═══════════════╗
║   Function  ║ EnterRealtime ║
╠═════════════╬═══════════════╩═════════════════════════════════════════════════════════════════════════════╗
║ Description ║ Executes code when entering Real-time - Logs real-time start & resets elapsed time counter. ║
╚═════════════╩═════════════════════════════════════════════════════════════════════════════════════════════╝*/
void UDPlugin::EnterRealtime()
{
	// start up timer every time we enter realtime
	mET = 0.0f;								//  Reset elapsed time counter to 0 when entering real-time session
	WriteToFiles( "a", "---ENTER REALTIME---" );//  Writes message to enabled output files when real-time entered
	log("a", "---ENTER REALTIME---" );			//  Records real-time session entry into Log
}
//  Finished Code & Comments


/*______________________________________________________________________________________________________________
╔═════════════╦══════════════╗
║   Function  ║ ExitRealtime ║
╠═════════════╬══════════════╩══════════════════════════════════════════════════════════════════════════════╗
║ Description ║ Executes code when exiting Real-time - Logs real-time start & set elapsed time counter to -1║
╚═════════════╩═════════════════════════════════════════════════════════════════════════════════════════════╝*/
void UDPlugin::ExitRealtime()
{
	mET = -1.0f;									//  RSet elapsed time counter to -1 when exiting real-time session
	WriteToFiles( "a", "---EXIT REALTIME---" );		//  Writes real-time exit message to enabled output files
	log("a", "---EXIT REALTIME---" );					//  Records real-time session exit into Log
}
//  Finished Code & Comments

//══════════════════════════════════════════════ Data Output ═══════════════════════════════════════════════════
/*______________________________________________________________________________________________________________
╔═════════════╦═════════════════╗
║   Function  ║ UpdateTelemetry ║
╠═════════════╬═════════════════╩═══════════════════════════════════════════════════════════════════════════╗
║ Description ║ Sends Telemetry Data included via UDP server to C# program. Data sent in the form of ascii  ║
║▀▀▀▀▀▀▀▀▀▀▀▀▀║ Hexcode. Also records specified Telemetry data to Telemetry.txt file.                       ║
╠═════════════╬═════════════════════════════════════════════════════════════════════════════════════════════╣
║  Parameters ║ TelemInfoV01 &info: Enables fetching of Telemetry Data                                      ║
╚═════════════╩═════════════════════════════════════════════════════════════════════════════════════════════╝*/
void UDPlugin::UpdateTelemetry(const TelemInfoV01 &info) {
	
	log("a", "starting telemetry\n"); // Records Telemetry start into Log

	// =====================================================================================================================
	// Declare a buffer to store telemetry data to be sent
	char buffer [200];

	// Get the size of the broadcast address structure
	int len = sizeof(sad);

	// Our world coordinate system is left-handed, with +y pointing up.
	// The local vehicle coordinate system is as follows:
	//   +x points out the left side of the car (from the driver's perspective)
	//   +y points out the roof
	//   +z points out the back of the car
	// Rotations are as follows:
	//   +x pitches up
	//   +y yaws to the right
	//   +z rolls to the right
	// Note that ISO vehicle coordinates (+x forward, +y right, +z upward) are
	// right-handed.  If you are using that system, be sure to negate any rotation
	// or torque data because things rotate in the opposite direction.  In other
	// words, a -z velocity in rFactor is a +x velocity in ISO, but a -z rotation
	// in rFactor is a -x rotation in ISO!!!

	// Compute auxiliary vectors based on the telemetry orientation data
	TelemVect3 forwardVector = { -info.mOri[0].z, -info.mOri[1].z, -info.mOri[2].z };
	TelemVect3 upVector = {  info.mOri[0].y,  info.mOri[1].y,  info.mOri[2].y };
	TelemVect3 leftVector = {  info.mOri[0].x,  info.mOri[1].x,  info.mOri[2].x };

	// Calculate pitch, yaw, and roll from orientation data
	// These are normalized vectors, and the world Y coordinate is up.
	// So, pitch and roll (w.r.t. the world x-z plane) can be determined as follows:
	const double pitch = atan2(forwardVector.y, sqrt((forwardVector.x * forwardVector.x) + (forwardVector.z * forwardVector.z)));
	const double yaw = atan2(info.mOri[0].z, info.mOri[2].z);
	const double roll = atan2(leftVector.y, sqrt((leftVector.x * leftVector.x) + (leftVector.z * leftVector.z)));
	const double radsToDeg = 57.296;	// Radians to Degree conversion 
	
	/*	Final Data points to output - Remember to prefix info. when adding to the sprintf: 
	Albert
		// Driver input
		double mUnfilteredThrottle;    	// 	ranges  0.0-1.0 (accelerator pedal)
		double mUnfilteredBrake;       	// 	ranges  0.0-1.0	(brake pedal)
		double mUnfilteredSteering;    	// 	ranges -1.0-1.0 (left to right - Steering Wheel)
		double mUnfilteredClutch;      	// 	ranges  0.0-1.0	(clutch pedal)
		mUnfilteredBrake mUnfilteredSteering mUnfilteredClutch
		// Misc
  		double mSteeringShaftTorque;   	// 	torque around steering shaft
		double mRotation;              // radians/sec (Wheel Turning Angles??)

	Alex & Albert
		//	Pitch - Remember to multiply by radsToDeg to change from radians to degree output
		const double pitch = atan2(forwardVector.y, sqrt((forwardVector.x * forwardVector.x) + (forwardVector.z * forwardVector.z)));

		//	Yaw - Remember to multiply by radsToDeg to change from radians to degree output
		const double yaw = atan2(info.mOri[0].z, info.mOri[2].z);

		//	Roll - Remember to multiply by radsToDeg to change from radians to degree output
		const double roll = atan2(leftVector.y, sqrt((leftVector.x * leftVector.x) + (leftVector.z * leftVector.z)));
		
		TelemVect3 mLocalAccel;			// acceleration (meters/sec^2) in local vehicle coordinates
		mLocalAccel.y;					//	Heave acceleration - Refers to vertical acceleration, usually along the z-axis.
		- mLocalAccel.x;				//	Sway acceleration  - Associated with lateral movement, typically along the y-axis.
		- mLocalAccel.z;				//	Surge acceleration - Relates to longitudinal movement, generally along the x-axis.

	*/
	// 	Format telemetry data into a string buffer - May give "warning C4267: 'argument' : conversion from 'size_t' to 'int', possible loss of data" during compilation, however should only reach the size of 125 which is far below the max int size
	sprintf(buffer, "%.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f\r\n", roll * radsToDeg,  pitch * radsToDeg, info.mLocalAccel.y, yaw * radsToDeg, - info.mLocalAccel.x, - info.mLocalAccel.z, info.mUnfilteredThrottle, info.mUnfilteredBrake, info.mUnfilteredSteering, info.mUnfilteredClutch, info.mSteeringShaftTorque,   info.mRotation);
	//                                                      									|     1. Roll     |     2. Pitch      |    3. HeaveAcc    |      4. Yaw    |       5. SwayAcc    |      6. SurgeAcc    |    7. Throttle Pedal    |    8. Brake Pedal    |    9. Steering Wheel    |    10. Clutch Pedal   | 11. Steering Shaft Force | 12.Wheel Rotation | 

	// Send telemetry data via UDP broadcast - Remind: Data is transmitted in ascii (Hex) 
		// s: 							Socket descriptor for sending data
		// buffer: 						Buffer containing the telemetry data
		// strlen(buffer): 				Length of the telemetry data in the buffer
		// 0: 							Flags (here, no special flags are specified)
		// (sockaddr*)&brdcastaddr: 	Pointer to the broadcast address structure
		// len: 						Size of the broadcast address structure
	int ret = sendto(s, buffer, strlen(buffer), 0, (sockaddr*)&sad, len);

	// =====================================================================================================================
	//	Writes the beginning of telemetry output to the output file
	WriteToFiles( "a", "--Telemetry Output--");	
	
	//	Below records Telemetry data to Telemetry.txt file
	//	Open or create a file named "Telemetry.txt" in append mode ("a")
	FILE *TelemFile = fopen("Telemetry.txt", "a");	
	if	(TelemFile != NULL)
	{
		// Delta time is variable, as we send out the info once per frame
		fprintf(TelemFile, "DT=%.4f | ET=%.4f\n", info.mDeltaTime, info.mElapsedTime);
		fprintf(TelemFile, "Lap=%d \n StartET=%20.f\n", info.mLapNumber, info.mLapStartET);
		fprintf(TelemFile, "Vehicle=%s\n", info.mVehicleName);
		fprintf(TelemFile, "Track=%s\n", info.mTrackName);
		fprintf(TelemFile, "Pos = (%.3f, %.3f, %.3f)\n\n", info.mPos.x, info.mPos.y, info.mPos.z);

	//	Forward is roughly in the -z direction (although current pitch of car may cause some y-direction velocity)
		fprintf(TelemFile, "LocalVel=(%.2f,%.2f,%.2f)\n", info.mLocalVel.x, info.mLocalVel.y, info.mLocalVel.z);
		fprintf(TelemFile, "LocalAccel=(%.1f,%.1f,%.1f)\n\n", info.mLocalAccel.x, info.mLocalAccel.y, 
				info.mLocalAccel.z);

		// Orientation matrix is left-handed
		fprintf(TelemFile, "[%6.3f,%6.3f,%6.3f]\n", info.mOri[0].x, info.mOri[0].y, info.mOri[0].z);
		fprintf(TelemFile, "[%6.3f,%6.3f,%6.3f]\n", info.mOri[1].x, info.mOri[1].y, info.mOri[1].z);
		fprintf(TelemFile, "[%6.3f,%6.3f,%6.3f]\n", info.mOri[2].x, info.mOri[2].y, info.mOri[2].z);
		fprintf(TelemFile, "LocalRot=(%.3f,%.3f,%.3f)\n", info.mLocalRot.x, info.mLocalRot.y, info.mLocalRot.z);
		fprintf(TelemFile, "LocalRotAccel=(%.2f,%.2f,%.2f)\n\n", info.mLocalRotAccel.x, 
				info.mLocalRotAccel.y, info.mLocalRotAccel.z);

		// Vehicle status
		fprintf(TelemFile, "Gear=%d RPM=%.1f RevLimit=%.1f\n", info.mGear, info.mEngineRPM, info.mEngineMaxRPM);
		fprintf(TelemFile, "Water=%.1f Oil=%.1f\n", info.mEngineWaterTemp, info.mEngineOilTemp);
		fprintf(TelemFile, "ClutchRPM=%.1f\n\n", info.mClutchRPM);

		// Driver input
		fprintf(TelemFile, "UnfilteredThrottle=%.1f%%\n", 100.0 * info.mUnfilteredThrottle);
		fprintf(TelemFile, "UnfilteredBrake=%.1f%%\n", 100.0 * info.mUnfilteredBrake);
		fprintf(TelemFile, "UnfilteredSteering=%.1f%%\n", 100.0 * info.mUnfilteredSteering);
		fprintf(TelemFile, "UnfilteredClutch=%.1f%%\n\n", 100.0 * info.mUnfilteredClutch);

		// Filtered input
		fprintf(TelemFile, "FilteredThrottle=%.1f%%\n", 100.0 * info.mFilteredThrottle);
		fprintf(TelemFile, "FilteredBrake=%.1f%%\n", 100.0 * info.mFilteredBrake);
		fprintf(TelemFile, "FilteredSteering=%.1f%%\n", 100.0 * info.mFilteredSteering);
		fprintf(TelemFile, "FilteredClutch=%.1f%%\n\n", 100.0 * info.mFilteredClutch);

		// Misc
		fprintf(TelemFile, "SteeringShaftTorque=%.1f\n", info.mSteeringShaftTorque);
		fprintf(TelemFile, "Front3rdDeflection=%.3f Rear3rdDeflection=%.3f\n\n", 
				info.mFront3rdDeflection, info.mRear3rdDeflection);

		// Aerodynamics
		fprintf(TelemFile, "FrontWingHeight=%.3f FrontRideHeight=%.3f RearRideHeight=%.3f\n", 
				info.mFrontWingHeight, info.mFrontRideHeight, info.mRearRideHeight);
		fprintf(TelemFile, "Drag=%.1f FrontDownforce=%.1f RearDownforce=%.1f\n\n", info.mDrag, info.mFrontDownforce,
				 info.mRearDownforce);

		// Other
		fprintf(TelemFile, "Fuel=%.1f ScheduledStops=%d Overheating=%d Detached=%d\n", info.mFuel, 
				info.mScheduledStops, info.mOverheating, info.mDetached);

		fprintf(TelemFile, "Dents=(%d,%d,%d,%d,%d,%d,%d,%d)\n\n", info.mDentSeverity[0], info.mDentSeverity[1], 
				info.mDentSeverity[2], info.mDentSeverity[3], info.mDentSeverity[4], info.mDentSeverity[5], 
				info.mDentSeverity[6], info.mDentSeverity[7]);

		fprintf(TelemFile, "LastImpactET=%.1f Mag=%.1f, Pos=(%.1f,%.1f,%.1f)\n\n", info.mLastImpactET, 
				info.mLastImpactMagnitude,	info.mLastImpactPos.x, info.mLastImpactPos.y, info.mLastImpactPos.z );

		// Wheels
		for( long i = 0; i < 4; ++i )
		{
			const TelemWheelV01 &wheel = info.mWheel[i];
			fprintf(TelemFile, "Wheel=%s\n", (i==0)?"FrontLeft":(i==1)?"FrontRight":(i==2)?"RearLeft":"RearRight");

			fprintf(TelemFile, " SuspensionDeflection=%.3f RideHeight=%.3f\n", wheel.mSuspensionDeflection, 
					wheel.mRideHeight );

			fprintf(TelemFile, " SuspForce=%.1f BrakeTemp=%.1f BrakePressure=%.3f\n", wheel.mSuspForce, 
					wheel.mBrakeTemp, wheel.mBrakePressure );

			fprintf(TelemFile, " TelemFilerwardRotation=%.1f Camber=%.3f\n", -wheel.mRotation, wheel.mCamber );

			fprintf(TelemFile, " LateralPatchVel=%.2f LongitudinalPatchVel=%.2f\n", wheel.mLateralPatchVel, 
					wheel.mLongitudinalPatchVel );

			fprintf(TelemFile, " LateralGroundVel=%.2f LongitudinalGroundVel=%.2f\n", wheel.mLateralGroundVel, 
					wheel.mLongitudinalGroundVel );

			fprintf(TelemFile, " LateralForce=%.1f LongitudinalForce=%.1f\n", wheel.mLateralForce, 
					wheel.mLongitudinalForce );

			fprintf(TelemFile, " TireLoad=%.1f GripFract=%.3f TirePressure=%.1f\n", wheel.mTireLoad, 
					wheel.mGripFract, wheel.mPressure );

			fprintf(TelemFile, " TireTemp(l/c/r)=%.1f/%.1f/%.1f\n", wheel.mTemperature[0], 
					wheel.mTemperature[1], wheel.mTemperature[2] );

			fprintf(TelemFile, " Wear=%.3f TerrainName=%s SurfaceType=%d\n", wheel.mWear, 
					wheel.mTerrainName, wheel.mSurfaceType );
					
			fprintf(TelemFile, " Flat=%d Detached=%d\n\n", wheel.mFlat, wheel.mDetached );
		}

		// Compute some auxiliary info based on the above
		TelemVect3 forwardVector = { -info.mOri[0].z, -info.mOri[1].z, -info.mOri[2].z };
		TelemVect3    leftVector = {  info.mOri[0].x,  info.mOri[1].x,  info.mOri[2].x };

		// These are normalized vectors, and remember that our world Y coordinate is up.  So you can
		// determine the current pitch and roll (w.r.t. the world x-z plane) as follows:
		const double pitch = atan2(forwardVector.y, sqrt((forwardVector.x * forwardVector.x) +
									(forwardVector.z * forwardVector.z)));

		const double  roll = atan2(leftVector.y, sqrt((leftVector.x * leftVector.x) + 
									(leftVector.z * leftVector.z)));

		const double radsToDeg = 57.296;
		fprintf(TelemFile, "Pitch = %.1f deg, Roll = %.1f deg\n", pitch * radsToDeg, roll * radsToDeg);

		const double metersPerSec = sqrt( ( info.mLocalVel.x * info.mLocalVel.x ) +
										( info.mLocalVel.y * info.mLocalVel.y ) +
										( info.mLocalVel.z * info.mLocalVel.z ) );
		fprintf(TelemFile, "Speed = %.1f KPH, %.1f MPH\n\n", metersPerSec * 3.6, metersPerSec * 2.237 );

		if (info.mElectricBoostMotorState != 0)
		{
			fprintf( TelemFile, "ElectricBoostMotor:");
			char const* const states[] = {"N/A", "Inactive", "Propulsion", "Regeneration"};
			fprintf( TelemFile, " State = %s\n", states[info.mElectricBoostMotorState]);
			fprintf( TelemFile, " Torque = %g nm\n", info.mElectricBoostMotorTorque);
			fprintf( TelemFile, " RPM = %g\n", info.mElectricBoostMotorRPM);
			fprintf( TelemFile, " Motor Temperature = %g C\n", info.mElectricBoostMotorTemperature);

			if (info.mElectricBoostMotorTemperature != 0) {
				fprintf( TelemFile, " Water Temperature = %g C\n", info.mElectricBoostWaterTemperature);
			}
		}

		// Close file
		fclose( TelemFile );
	}
	
	log("a", "ending telemetry\n");  //  Records End of Telemetry Data Stream into Log
}
//  Finished Code & Comments


/*______________________________________________________________________________________________________________
╔═════════════╦═════════════════╗
║   Function  ║ UpdateTelemetry ║
╠═════════════╬═════════════════╩═══════════════════════════════════════════════════════════════════════════╗
║ Description ║ Old approach to transmitting data via UDP protocal - Kept for posterity                     ║
╠═════════════╬═════════════════════════════════════════════════════════════════════════════════════════════╣
║  Parameters ║ TelemInfoV01 &info: Enables fetching of Telemetry Data                                      ║
╚═════════════╩═════════════════════════════════════════════════════════════════════════════════════════════╝*/
/*void UDPlugin::UpdateTelemetry(const TelemInfoV01 &info) {
	log("a", "starting telemetry\n"); // Records Telemetry start into Log

	StartStream();
	StreamData((char *)&type_telemetry, sizeof(char));
	StreamData((char *)&info.mGear, sizeof(long));

	StreamData((char *)&info.mEngineRPM, sizeof(double));
	StreamData((char *)&info.mEngineMaxRPM, sizeof(double));
	StreamData((char *)&info.mEngineWaterTemp, sizeof(double));
	StreamData((char *)&info.mEngineOilTemp, sizeof(double));
	StreamData((char *)&info.mClutchRPM, sizeof(double));
	StreamData((char *)&info.mOverheating, sizeof(bool));
	StreamData((char *)&info.mFuel, sizeof(double));

	StreamData((char *)&info.mPos.x, sizeof(double));
	StreamData((char *)&info.mPos.y, sizeof(double));
	StreamData((char *)&info.mPos.z, sizeof(double));

	//  Data output in order:  pitch, yaw, roll, Sway/lateral acceleration, Surge/Longitudinal Acceleration, MPH
	TelemVect3 forwardVector = { -info.mOri[0].z, -info.mOri[1].z, -info.mOri[2].z };
	TelemVect3 upVector = {  info.mOri[0].y,  info.mOri[1].y,  info.mOri[2].y };
	TelemVect3 leftVector = {  info.mOri[0].x,  info.mOri[1].x,  info.mOri[2].x };

	const double radsToDeg = 57.296;  // Radians to Degree conversion 

	//  Calculating and streaming pitch (Order 1)
	const double pitch = atan2( forwardVector.y, sqrt( ( forwardVector.x * forwardVector.x) + ( forwardVector.z * forwardVector.z ) ) );
	const double pitch_out = pitch * radsToDeg;
	StreamData((char *)&pitch_out, sizeof(double));

	//  Calculating and streaming Yaw (Order 2)
	const double yaw = atan2(info.mOri[0].z, info.mOri[2].z);
	const double yaw_out = yaw * radsToDeg;
	StreamData((char *)&yaw_out, sizeof(double));

	//  Calculating and streaming Yaw (Order 3)
	const double  roll = atan2(leftVector.y, sqrt( (leftVector.x*leftVector.x) + (leftVector.z * leftVector.z )));
	const double roll_out = roll * radsToDeg;
	StreamData((char *)&roll_out, sizeof(double));

	//  Calculating and streaming Yaw (Order 4)
	const double SwayAcc = -info.mLocalAccel.x;
	StreamData((char *)&SwayAcc, sizeof(double));

	//  Calculating and streaming Yaw (Order 5)
	const double SurgeAcc = (info.mLocalAccel.z * -1);
	StreamData((char *)&SurgeAcc, sizeof(double));

	//  Calculating and streaming Speed (Order 6)
	const double metersPerSec = sqrt((info.mLocalVel.x * info.mLocalVel.x) +	(info.mLocalVel.y * info.mLocalVel.y) +	(info.mLocalVel.z * info.mLocalVel.z));
	StreamData((char *)&metersPerSec, sizeof(double));

	roll * radsToDeg,  pitch * radsToDeg, info.mLocalAccel.y, yaw * radsToDeg, - info.mLocalAccel.x, - info.mLocalAccel.z);
	// Roll,               Pitch,              HeaveAcc,           Yaw,                SwayAcc,            SurgeAcc

	StreamData((char *)&info.mLapStartET, sizeof(double));
	StreamData((char *)&info.mLapNumber, sizeof(long));

	StreamData((char *)&info.mUnfilteredThrottle, sizeof(double));
	StreamData((char *)&info.mUnfilteredBrake, sizeof(double));
	StreamData((char *)&info.mUnfilteredSteering, sizeof(double));
	StreamData((char *)&info.mUnfilteredClutch, sizeof(double));

	StreamData((char *)&info.mLastImpactET, sizeof(double));
	StreamData((char *)&info.mLastImpactMagnitude, sizeof(double));
	StreamData((char *)&info.mLastImpactPos.x, sizeof(double));
	StreamData((char *)&info.mLastImpactPos.y, sizeof(double));
	StreamData((char *)&info.mLastImpactPos.z, sizeof(double));
	for (long i = 0; i < 8; i++) {
		StreamData((char *)&info.mDentSeverity[i], sizeof(byte));
	}

	for (long i = 0; i < 4; i++) {
		const TelemWheelV01 &wheel = info.mWheel[i];
		StreamData((char *)&wheel.mDetached, sizeof(bool));
		StreamData((char *)&wheel.mFlat, sizeof(bool));
		StreamData((char *)&wheel.mBrakeTemp, sizeof(double));
		StreamData((char *)&wheel.mPressure, sizeof(double));
		StreamData((char *)&wheel.mRideHeight, sizeof(double));
		StreamData((char *)&wheel.mTemperature[0], sizeof(double));
		StreamData((char *)&wheel.mTemperature[1], sizeof(double));
		StreamData((char *)&wheel.mTemperature[2], sizeof(double));
		StreamData((char *)&wheel.mWear, sizeof(double));
	}
	EndStream();

	log("a", "ending telemetry\n");  //  Records End of Telemetry Data Stream into Log
}*/
//	Alternative Telemetry Code - Kept for Posterity


/*______________________________________________________________________________________________________________
╔═════════════╦═══════════════╗
║   Function  ║ UpdateScoring ║
╠═════════════╬═══════════════╩═════════════════════════════════════════════════════════════════════════════╗
║ Description ║ Used with old UDP code - Kept for posterity                                                 ║
╠═════════════╬═════════════════════════════════════════════════════════════════════════════════════════════╣
║  Parameters ║ ScoringInfoV01 &info: Enables extraction of Scoring Data 									║
╚═════════════╩═════════════════════════════════════════════════════════════════════════════════════════════╝*/
void UDPlugin::UpdateScoring(const ScoringInfoV01 &info) {
	// //log("a", "starting update");
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
	// //log("a", "ending update\n");
}
//	Alternative Scoring Code - Kept for Posterity

/*______________________________________________________________________________________________________________
╔═════════════╦════════════════╗
║   Function  ║ UpdateGraphics ║
╠═════════════╬════════════════╩════════════════════════════════════════════════════════════════════════════╗
║ Description ║ Not Implemented fully - Not needed for now                                                  ║
╠═════════════╬═════════════════════════════════════════════════════════════════════════════════════════════╣
║  Parameters ║ GraphicsInfoV01 &info: Enables extraction of Graphics Data 									║
╚═════════════╩═════════════════════════════════════════════════════════════════════════════════════════════╝*/
//	void ExampleInternalsPlugin::UpdateGraphics( const GraphicsInfoV01 &info )
//	{
//		FILE *TelemFile = fopen( "GraphicsOutput.txt", "a" );
//		if( TelemFile != NULL )
//		{
//     	// Print Graphics Info
//     		fprintf(TelemFile, "CamPos=(%.1f,%.1f,%.1f)\n", info.mCamPos.x, info.mCamPos.y, info.mCamPos.z);
//     		fprintf(TelemFile, "CamOri[0]=(%.1f,%.1f,%.1f)\n", info.mCamOri[0].x, info.mCamOri[0].y, info.mCamOri[0].z);
//     		fprintf(TelemFile, "CamOri[1]=(%.1f,%.1f,%.1f)\n", info.mCamOri[1].x, info.mCamOri[1].y, info.mCamOri[1].z);
//     		fprintf(TelemFile, "CamOri[2]=(%.1f,%.1f,%.1f)\n", info.mCamOri[2].x, info.mCamOri[2].y, info.mCamOri[2].z);
//     		fprintf(TelemFile, "HWND=%d\n", info.mHWND );
//     		fprintf(TelemFile, "Ambient Color=(%.1f,%.1f,%.1f)\n\n", info.mAmbientRed, info.mAmbientGreen, info.mAmbientBlue);
//     		// Close file
//     		fclose(TelemFile);
//		}
//	}
//	Finished Code & Comments - Not needed so not implemented fully

//═════════════════════════════════════════ Alt Data Streaming ═════════════════════════════════════════════════
/*______________________________________________________________________________________________________________
Functions for streaming data
╔═════════════╦═════════════╗
║   Function  ║ StartStream ║
╠═════════════╬═════════════╩═══════════════════════════════════════════════════════════════════════════════╗
║ Description ║ Used with old UDP code - Kept for posterity                                                 ║
╚═════════════╩═════════════════════════════════════════════════════════════════════════════════════════════╝*/
void UDPlugin::StartStream() {
	
	// 	Initialize data packet and sequence number
	data_packet = 0;
	data_sequence++;

	// 	Populate data array with version, packet number, and sequence number
	data[0] = data_version;								//	Version of the data stream
	data[1] = data_packet;								//	Packet number
	memcpy(&data[2], &data_sequence, sizeof(short));	//	Sequence number
	
	//	Set data offset for further data population
	data_offset = 4;	//	Offset for subsequent data writing
}
//  Finished Code & Comments - Data Streaming for Alternative Data streaming method


/*______________________________________________________________________________________________________________
╔══════════════╦════════════╗
║   Function   ║ StreamData ║
╠══════════════╬════════════╩════════════════════════════════════════════════════════════════════════════════╗
║ Description  ║ Used with old UDP code - Kept for posterity                                                 ║
╠══════════════╬═════════════════════════════════════════════════════════════════════════════════════════════╣
║  Parameters  ║ *data_ptr: Data pointer      	                                                           ║
║              ║ length: Length of data 		                                                               ║
╚══════════════╩═════════════════════════════════════════════════════════════════════════════════════════════╝*/
void UDPlugin::StreamData(char *data_ptr, int length) {
	int i;

	//	Iterate through the data_ptr and copy it to the data array
	for (i = 0; i < length; i++) {
		//	Check if data array is full (reached the maximum packet size)
		if (data_offset + i == 512) {

			//	Send the current data packet
			sendto(s, data, 512, 0, (struct sockaddr *) &sad, sizeof(struct sockaddr));

			//	Increment packet number and reset data array for the next packet
			data_packet++;	
			data[0] = data_version;
			data[1] = data_packet;
			memcpy(&data[2], &data_sequence, sizeof(short));
			data_offset = 4;
			
			//	Increment packet number and reset data array for the next packet
			length = length - i;
			data_ptr += i;
			i = 0;	//	Increment packet number and reset data array for the next packet
		}
		data[data_offset + i] = data_ptr[i];	// Copy data from data_ptr to data array
	}
	data_offset = data_offset + length;			// Update data_offset for the next data population
}
//  Finished Code & Comments - Data Streaming for Alternative Data streaming method


/*______________________________________________________________________________________________________________
╔══════════════╦═════════════════╗
║   Function   ║ StreamVarString ║
╠══════════════╬═════════════════╩═══════════════════════════════════════════════════════════════════════════╗
║ Description  ║ Used with old UDP code - Kept for posterity                                                 ║
╠══════════════╬═════════════════════════════════════════════════════════════════════════════════════════════╣
║  Parameters  ║ *data_ptr: Data Pointer                                                                     ║
╚══════════════╩═════════════════════════════════════════════════════════════════════════════════════════════╝*/
void UDPlugin::StreamVarString(char *data_ptr) {
	int i = 0;
	while (data_ptr[i] != 0) {				//	Find the length of the variable-length string
		i++;
	}
	//	Stream the length of the string followed by the string data
	StreamData((char *)&i, sizeof(int));	// Stream the length of the string
	StreamString(data_ptr, i);				// Stream the string data
}
//  Finished Code & Comments - Data Streaming for Alternative Data streaming method


/*______________________________________________________________________________________________________________
╔══════════════╦══════════════╗
║   Function   ║ StreamString ║
╠══════════════╬══════════════╩══════════════════════════════════════════════════════════════════════════════╗
║ Description  ║ Used with old UDP code - Kept for posterity                                                 ║
╠══════════════╬═════════════════════════════════════════════════════════════════════════════════════════════╣
║  Parameters  ║ *data_ptr: Data Pointer                                                                     ║
║              ║ length: Length of Data                                                                      ║
╚══════════════╩═════════════════════════════════════════════════════════════════════════════════════════════╝*/
void UDPlugin::StreamString(char *data_ptr, int length) {
	int i;
	for (i = 0; i < length; i++) {		//	Iterate through the string characters
		if (data_offset + i == 512) {	//	Check if data array is full (reached the maximum packet size)
			
			//	Send the current data packet
			sendto(s, data, 512, 0, (struct sockaddr *) &sad, sizeof(struct sockaddr));
			
			//	Increment packet number and reset data array for the next packet
			data_packet++;	
			data[0] = data_version;
			data[1] = data_packet;
			memcpy(&data[2], &data_sequence, sizeof(short)); 
			data_offset = 4;
			
			//	Update remaining length and data pointer
			length = length - i;
			data_ptr += i;
			i = 0;	//	Reset i to 0 for the next iteration
		}
		//	Copy character from data_ptr to data array
		data[data_offset + i] = data_ptr[i];
		if (data_ptr[i] == 0) {	//	Check for end of string

			//	Move data_offset to the end of the string and return
			data_offset = data_offset + i + 1;
			return;
		}
	}
	data_offset = data_offset + length;	//	Update data_offset for the next data population
}
//  Finished Code & Comments - Data Streaming for Alternative Data streaming method


/*______________________________________________________________________________________________________________
╔══════════════╦═══════════╗
║   Function   ║ EndStream ║
╠══════════════╬═══════════╩═════════════════════════════════════════════════════════════════════════════════╗
║ Description  ║ Used with old UDP code - Kept for posterity                                                 ║
╚══════════════╩═════════════════════════════════════════════════════════════════════════════════════════════╝*/
void UDPlugin::EndStream() {
	//		Check if there is any data in the data array to be sent
	if (data_offset > 4) {
		//	Send the remaining data as a packet
		sendto(s, data, data_offset, 0, (struct sockaddr *) &sad, sizeof(struct sockaddr));
	}
}
//  Finished Code & Comments - Data Streaming for Alternative Data streaming method

//______________________________________________________________________________________________________________
//═══════════════════════════════════════════ Extra Features ═══════════════════════════════════════════════════
/*______________________________________________________________________________________________________________
╔═════════════╦════════════════╗
║   Function  ║ CheckHWControl ║
╠═════════════╬════════════════╩════════════════════════════════════════════════════════════════════════════╗
║ Description ║ Checks if Hardware control is enabled. Enabled: return = True / Disabled: return = False    ║
╠═════════════╬═════════════════════════════════════════════════════════════════════════════════════════════╣
║  Parameters ║ controlName: Name of hardware being controlled                                              ║
║             ║ &fRetVal: return value                                                                      ║
╚═════════════╩═════════════════════════════════════════════════════════════════════════════════════════════╝*/
bool UDPlugin::CheckHWControl( const char * const controlName, double &fRetVal ) {
	
	// only if enabled, of course
	if( !mEnabled ) 
		return( false );

	// Note that incoming value is the game's computation, in case you're interested.

	// No control allowed over actual vehicle inputs - Due to cheating possibility
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
		if((headSwitcheroo > 1.0) && (headSwitcheroo < 1.5 )) {
			fRetVal = 1.0;
		} 
		else {
			fRetVal = 0.0;
		return( true );
		}
	}

	return( false );
}
//  Finished Code & Comments

/*______________________________________________________________________________________________________________
╔══════════════╦═══════════════╗
║   Function   ║ ForceFeedback ║
╠══════════════╬═══════════════╩═════════════════════════════════════════════════════════════════════════════╗
║ Description  ║ Enables reading & manipulation of Force Feedback                                            ║
╠══════════════╬═════════════════════════════════════════════════════════════════════════════════════════════╣
║  Parameters  ║ &forceValue: Value of FFB torque force value                                                ║
╚══════════════╩═════════════════════════════════════════════════════════════════════════════════════════════╝*/
bool UDPlugin::ForceFeedback( double &forceValue )
  {
    // CHANGE COMMENTS TO ENABLE FORCE EXAMPLE
    return( false );

	//	I think the bounds are -11500 to 11500 ...
	//	forceValue = 11500.0 * sinf( mET );
	//	return( true );
  }
//  Finished Code & Comments

/*______________________________________________________________________________________________________________
╔══════════════╦═══════════════════╗
║   Function   ║ RequestCommentary ║
╠══════════════╬═══════════════════╩═════════════════════════════════════════════════════════════════════════╗
║ Description  ║ Enables manually triggering game commentary			      							     ║
╠══════════════╬═════════════════════════════════════════════════════════════════════════════════════════════╣
║  Parameters  ║ CommentaryRequestInfoV01 &info: Enables use and data acess of commentary related variables  ║
╚══════════════╩═════════════════════════════════════════════════════════════════════════════════════════════╝*/
bool UDPlugin::RequestCommentary( CommentaryRequestInfoV01 &info )
{
    // This function requests commentary information to be provided to the plugin.

    // COMMENT OUT TO ENABLE EXAMPLE
    return (false); // Disable this function and return false by default.

    // Check if the plugin is enabled
    if( !mEnabled )
        return( false ); // If not enabled, return false.

    // Note: function is called twice per second

    // Trigger a green flag event every 20 seconds
    const double timeMod20 = fmod( mET, 20.0 ); // Calculate the remainder of mET divided by 20
    if( timeMod20 > 19.0 ) // If the remainder is greater than 19, it's almost 20 seconds
    {
        // Populate the CommentaryRequestInfoV01 structure with green flag event data
        strcpy( info.mName, "GreenFlag" ); // Set the event name to "GreenFlag"
        info.mInput1 = 0.0; // Set input 1 value to 0.0
        info.mInput2 = 0.0; // Set input 2 value to 0.0
        info.mInput3 = 0.0; // Set input 3 value to 0.0
        info.mSkipChecks = true; // Skip checks for this event
        return true; // Return true to indicate that commentary information is provided
    }

    // If no event triggered, return false
    return false;
}

/*______________________________________________________________________________________________________________
╔══════════════╦═══════════════════════╗
║   Function   ║ WantsToDisplayMessage ║
╠══════════════╬═══════════════════════╩═════════════════════════════════════════════════════════════════════╗
║ Description  ║ Enables custom message display in-game. 													   ║
╠══════════════╬═════════════════════════════════════════════════════════════════════════════════════════════╣
║  Parameters  ║ MessageInfoV01 &msgInfo: Enables access to variables and data regarding in-game messaging.  ║
╚══════════════╩═════════════════════════════════════════════════════════════════════════════════════════════╝*/
bool UDPlugin::WantsToDisplayMessage(MessageInfoV01 &msgInfo) {return false;}
//  Finished Code & Comments

/*______________________________________________________________________________________________________________
╔══════════════╦════════════════════╗
║   Function   ║ WantsToViewVehicle ║
╠══════════════╬════════════════════╩════════════════════════════════════════════════════════════════════════╗
║ Description  ║ Allows control of the in-game player camera.                                                ║
╠══════════════╬═════════════════════════════════════════════════════════════════════════════════════════════╣
║  Parameters  ║ CameraControlInfoV01 &camControl: Enables access to variables and data related to the camera║
╚══════════════╩═════════════════════════════════════════════════════════════════════════════════════════════╝*/
unsigned char UDPlugin::WantsToViewVehicle(CameraControlInfoV01 &camControl) {return 0;}
//  Finished Code & Comments

//═══════════════════════════════════════════ Unused Functions ═════════════════════════════════════════════════
void UDPlugin::Load(){}   //  Not Currently Used - Kept for posterity
void UDPlugin::Unload(){} //  Not Currently Used - Kept for posterity