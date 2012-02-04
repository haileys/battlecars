#ifndef UI_CONFIRM_HH
#define UI_CONFIRM_HH

#include <Gwen/Controls/WindowControl.h>
#include <Gwen/Controls/TabControl.h>
#include <Gwen/Controls/ListBox.h>
#include <Gwen/Controls/Layout/Position.h>
#include <Gwen/Utility.h>
#include <Gwen/Events.h>
#include <string>

namespace UI
{

class Confirm : public Gwen::Event::Handler
{
    Gwen::Controls::WindowControl* window;
    Gwen::Controls::Button* option_a;
    Gwen::Controls::Button* option_b;
    
    Gwen::Event::Handler* option_a_this;
    void(Gwen::Event::Handler::*option_a_handler)(Gwen::Controls::Base*);
    
    Gwen::Event::Handler* option_b_this;
    void(Gwen::Event::Handler::*option_b_handler)(Gwen::Controls::Base*);
    
    void option_a_OnPress(Gwen::Controls::Base* sender);
    void option_b_OnPress(Gwen::Controls::Base* sender);
    
public:
    Confirm(Gwen::Controls::Base* parent, std::string prompt, std::string a, std::string b);
    ~Confirm();
    
    template<typename T>
    void SetOptionAHandler(Gwen::Event::Handler* self, void(T::*handler)(Gwen::Controls::Base*))
    {
        option_a_this = self;
        option_a_handler = static_cast<Gwen::Event::Handler::Function>(handler);
    }
    
    template<typename T>
    void SetOptionBHandler(Gwen::Event::Handler* self, void(T::*handler)(Gwen::Controls::Base*))
    {
        option_b_this = self;
        option_b_handler = static_cast<Gwen::Event::Handler::Function>(handler);
    }
    
    void Show();
    void Hide();
};

}

#endif