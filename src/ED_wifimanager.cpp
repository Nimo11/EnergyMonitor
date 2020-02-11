//-------------------------------------------------------------------------------------------
// Wifimanager
//--------------------------------------------------------------------------------------------
#include <ED_wifimanager.h>
#include "Global.h"

void setWifiManagerMenu()
{
  std::vector<const char *> menu = {"wifi", "info", "param","test", "sep", "restart"};
  wm.setMenu(menu);
  wm.setDebugOutput(Log.level==LogObject::DebugLevels::Verbose);

  wm.setConfigPortalBlocking(true);
}
