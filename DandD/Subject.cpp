#include "Subject.h"

void Subject::notify() {
	for (auto observer : observers) {
		observer->update();
	}
}

void Subject::Attach(Observer *observer) {
	observers.push_back(observer);
	observer->subject = this;
}

void Subject::confirmMessage()
{
	message = ""; //! message that will get writting to GameLog
}
