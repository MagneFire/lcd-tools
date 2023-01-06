#ifndef ASTEROIDOS_LCD_TOOLS_H
#define ASTEROIDOS_LCD_TOOLS_H

namespace AsteroidOS::LCD_Tools {
	class LcdTools {
	public:
		LcdTools() {};
		virtual ~LcdTools() {};
		virtual int SyncTime() = 0;
		virtual int PrepareTimepiece() = 0;
		virtual int DisableStepCounter() = 0;
		virtual int EnableStepCounter() = 0;
		virtual int DisableHeartRate() = 0;
		virtual int EnableHeartRate() = 0;
		virtual int DisableMotion() = 0;
		virtual int EnableMotion() = 0;
	};
}
#endif //ASTEROIDOS_LCD_TOOLS_H
