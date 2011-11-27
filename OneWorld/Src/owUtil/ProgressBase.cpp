
#include <owUtil/ProgressBase.h>
#include <osg/Notify>

using namespace owUtil;

ProgressBase::ProgressBase() :
osg::Referenced( true ),
_canceled(false),
_needsRetry(false)
{
    //NOP
}

bool ProgressBase::reportProgress(double /*current*/, double /*total*/, const std::string& /*msg*/) 
{
    return false;
}

/******************************************************************************/
ConsoleProgressCallback::ConsoleProgressCallback() :
ProgressBase()
{
    //NOP
}

bool
ConsoleProgressCallback::reportProgress(double current, double total, const std::string& msg)
{
    if (total > 0)
    {
	double percentComplete = (current / total) * 100.0;
	std::cout << "Completed " << percentComplete << "% " << current << " of " << total << std::endl;
    }
    else
    {
	std::cout << msg << std::endl;
    }
    return false;
}
