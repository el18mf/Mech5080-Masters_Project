#pragma once

// #ifndef _INTERNALS_EXAMPLE_H
// #define _INTERNALS_EXAMPLE_H

#include "InternalsPlugin.hpp"

// This is used for the app to use the plugin for its intended purpose
class UDPlugin : public InternalsPluginV06  // REMINDER: exported function GetPluginVersion() should return 1 if you are deriving from this InternalsPluginV01, 2 for InternalsPluginV02, etc.
{
 public:
  UDPlugin() {}     // Constructor
  ~UDPlugin() {}    // Destructor

  // These are the functions derived from base class InternalsPlugin
  // that can be implemented.
  void Startup(long version);  // game startup
  void Shutdown();               // game shutdown

  void Load();                   // scene/track load
	void Unload();                 // scene/track unload
  
  void EnterRealtime();          // entering realtime
  void ExitRealtime();           // exiting realtime

  void StartSession();           // session has started
  void EndSession();             // session has ended

  // GAME OUTPUT
  long WantsTelemetryUpdates() {return(1); }            // 1 = ENABLE TELEMETRY EXAMPLE!
  void UpdateTelemetry(const TelemInfoV01 &info);

  bool WantsGraphicsUpdates() {return( false ); }       // TRUE = ENABLE GRAPHICS EXAMPLE!
  //  Extended Game Output
  // void UpdateGraphics( const GraphicsInfoV01 &info );
  virtual void UpdateGraphics(const GraphicsInfoV02 &info)          {} // update plugin with extended graphics info

  // GAME INPUT
  bool HasHardwareInputs() { return( false ); } // CHANGE TO TRUE TO ENABLE HARDWARE EXAMPLE!
  void UpdateHardware( const double fDT ) { mET += fDT; } // update the hardware with the time between frames
  void EnableHardware() { mEnabled = true; }             // message from game to enable hardware
  void DisableHardware() { mEnabled = false; }           // message from game to disable hardware

  // See if the plugin wants to take over a hardware control.  If the plugin takes over the
  // control, this method returns true and sets the value of the double pointed to by the
  // second arg.  Otherwise, it returns false and leaves the double unmodified.
  bool CheckHWControl( const char * const controlName, double &fRetVal );

  bool ForceFeedback( double &forceValue );  // SEE FUNCTION BODY TO ENABLE FORCE EXAMPLE

  // SCORING OUTPUT
  bool WantsScoringUpdates() { return(true); } // TRUE = ENABLE SCORING!
  void UpdateScoring( const ScoringInfoV01 &info );

  // COMMENTARY INPUT
  bool RequestCommentary( CommentaryRequestInfoV01 &info );  // SEE FUNCTION BODY TO ENABLE COMMENTARY EXAMPLE

  // MESSAGE BOX INPUT
	bool WantsToDisplayMessage(MessageInfoV01 &msgInfo);

	// CAMERA CONTROL
	unsigned char WantsToViewVehicle(CameraControlInfoV01 &camControl);

	// ERROR FEEDBACK
	virtual void Error(const char * const msg); // Called with explanation message if there was some sort of error in a plugin callback

	// VIDEO EXPORT (sorry, no example code at this time)
	virtual bool WantsVideoOutput() { return(false); }                            // whether we want to export video
	virtual bool VideoOpen(const char * const szFilename, float fQuality, unsigned short usFPS, unsigned long fBPS,
		unsigned short usWidth, unsigned short usHeight, char *cpCodec = NULL) {
		return(false);
	}                                                                             // open video output file
	virtual void VideoClose() {}                                                  // close video output file
	virtual void VideoWriteAudio(const short *pAudio, unsigned int uNumFrames) {} // write some audio info
	virtual void VideoWriteImage(const unsigned char *pImage) {}                  // write video image

 private:

  void WriteToFiles( const char * const openStr, const char * const msg );
  double mET;  // Event Time | needed for the hardware example
  bool mEnabled; // needed for the hardware example
	
  // constant types
	static const char type_telemetry = 1;
	static const char type_scoring = 2;

	void StartStream();
	void StreamData(char *data_ptr, int length);
	void StreamString(char *data_ptr, int length);
	void StreamVarString(char *data_ptr);
	void EndStream();
	void log(const char *msg);

	SOCKET s; // socket to send data to
	struct sockaddr_in sad;
	char data[512];
	int data_offset;
	byte data_version;
	byte data_packet;
	short data_sequence;
	char hostname[256];
	int port;
};


// #endif // _INTERNALS_EXAMPLE_H

