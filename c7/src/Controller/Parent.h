#ifndef BAKUDAN_CONTROLLER_PARENT_H_
#define BAKUDAN_CONTROLLER_PARENT_H_

#include "App.h"

namespace Controller
{

class Parent
{
public:
	Parent();
	virtual ~Parent();
	virtual App::ControllerType type() const = 0;
};

} // namespace Controller

#endif
