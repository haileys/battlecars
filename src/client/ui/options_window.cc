#include "client/ui/options_window.hh"

using namespace UI;

OptionsWindow::OptionsWindow(Game& _game, Gwen::Controls::Canvas* _canvas)
    : game(_game), canvas(_canvas)
{
    window = new Gwen::Controls::WindowControl(canvas);
    window->SetTitle("Options");
    window->SetPos(240, 240);
    window->SetSize(640, 400);
    //window->DisableResizing();
    window->Hide();

    {
        // name stuff
        Gwen::Controls::Label* lbl = new Gwen::Controls::Label(window);
        lbl->SetText("Nickname:");
        lbl->SetPos(0, 0);
        lbl->SizeToContents();

        nickname = new Gwen::Controls::TextBox(window);
        nickname->SetPos(0, 20);
        nickname->SetText(Gwen::Utility::StringToUnicode(game.config.Name()));
        nickname->SetSize(320, 32);
    }

    apply = new Gwen::Controls::Button(window);
    apply->SetText("Apply");
    apply->SetSize(80, 32);
    apply->SetPos(456, 332);
    apply->onPress.Add(this, &OptionsWindow::apply_OnPress);

    close = new Gwen::Controls::Button(window);
    close->SetText("Close");
    close->SetSize(80, 32);
    close->SetPos(544, 332);
    close->onPress.Add(this, &OptionsWindow::close_OnPress);
}

OptionsWindow::~OptionsWindow()
{
    delete window;
}

void OptionsWindow::Show()
{    
    window->Show();
}

void OptionsWindow::apply_OnPress(Gwen::Controls::Base* sender)
{
    game.config.SetName(Gwen::Utility::UnicodeToString(nickname->GetText()));
    game.config.Write();
}

void OptionsWindow::close_OnPress(Gwen::Controls::Base* sender)
{
    window->Hide();
}