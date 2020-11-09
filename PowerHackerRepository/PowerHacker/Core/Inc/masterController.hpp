#include <main.h>
#include <boardUserInterface.hpp>

enum class runStatus{
	scriptExec , serialControl, directControl
};

class masterController{
public:
	masterController();
	void digestUI(buttonTree);
	void rotateChannel();
	runStatus getMode(){ return currentState_; }
private:
	runStatus currentState_ = runStatus::directControl;
};
