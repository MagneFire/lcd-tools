#include "lcd-tools.h"
#include "catfish-tools.h"

#include <CLI/CLI.hpp>

#include <QSettings>

const char* CONFIG_FILE = "/etc/asteroid/machine.conf";

using namespace AsteroidOS::LCD_Tools;

int main( int argc, char** argv ) {
	CLI::App app{"lcd-tools: Various controls for the second display devices"};
	LcdTools* lcdTools = nullptr;

	QSettings m_settings(CONFIG_FILE, QSettings::IniFormat);
	const QString machineCodename = m_settings.value("Identity/MACHINE", "unknown").toString();

	if (machineCodename == "catfish") {
		lcdTools = new CatfishLcdTools();
	} else if (machineCodename == "koi") {
		// lcdTools = new KoiLcdTools();
		std::cerr << "lcd-tools is not supported on this watch!" << std::endl;
		return 0;
	} else {
		// lcdTools = new LcdTools();
		std::cerr << "lcd-tools is not supported on this watch!" << std::endl;
		return 0;
	}

	app.add_flag_callback("--sync-time",[&]() { lcdTools->SyncTime(); },"Sync lcd time with linux time");
	app.add_flag_callback("--prepare-timepiece",[&]() { lcdTools->PrepareTimepiece(); },"Start timepiece only mode");
	app.add_flag_callback("--enable-stepcounter",[&]() { lcdTools->EnableStepCounter(); },"Enable the step counter");
	app.add_flag_callback("--disable-stepcounter",[&]() { lcdTools->DisableStepCounter(); },"Disable the step counter");
	app.add_flag_callback("--enable-heartrate",[&]() { lcdTools->EnableHeartRate(); },"Enable the heart rate sensor");
	app.add_flag_callback("--disable-heartrate",[&]() { lcdTools->DisableHeartRate(); },"Disable the heart rate sensor");
	app.add_flag_callback("--enable-motion",[&]() { lcdTools->EnableMotion(); },"Enable motion");
	app.add_flag_callback("--disable-motion",[&]() { lcdTools->DisableMotion(); },"Disable motion");

	try{
		app.parse(argc,argv);
		if (argc <= 1)
			throw CLI::CallForAllHelp();
	} catch (const CLI::ParseError &e){
		if (lcdTools) {
			delete lcdTools;
		}

		return app.exit(e);
	}
	return 0;
}
