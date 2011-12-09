#ifndef UI_MAIN_MENU_HH
#define UI_MAIN_MENU_HH

#include <Gwen/Platform.h>
#include <Gwen/Controls/Label.h>

namespace UI
{
    
class MainMenu : public Gwen::Controls::Base
{
    Gwen::Controls::Label* heading;

    GWEN_CONTROL(MainMenu, Gwen::Controls::Base);
};

}

#endif