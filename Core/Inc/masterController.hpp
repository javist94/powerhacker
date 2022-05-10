#ifndef INC_MASTERCONTROLLER_HPP_
#define INC_MASTERCONTROLLER_HPP_

#include <main.h>
#include <string>
#include <boardUserInterface.hpp>

enum class runStatus{
	scriptExec , serialControl, directControl
};

class masterController{
public:
	masterController();
	void digestUI(buttonTree);
	void digestUSB();
	void rotateChannel();
	std::string getBoardInfo();
	runStatus getMode(){ return currentState_; }
private:
	runStatus currentState_ = runStatus::directControl;
};

#endif
