#include "client/ui/main_menu.hh"

UI::MainMenu::MainMenu(Gwen::Controls::Base* pParent)
    : BaseClass(pParent)
{
    heading = new Gwen::Controls::Label(this);
    heading->SetText("battlecars");
    heading->SizeToContents();
    heading->SetPos(10, 10);
}