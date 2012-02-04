#include "client/ui/confirm.hh"

using namespace UI;

Confirm::Confirm(Gwen::Controls::Base* parent, std::string prompt, std::string a, std::string b)
    : option_a_this(NULL), option_b_this(NULL)
{
    window = new Gwen::Controls::WindowControl(parent);
    window->SetTitle("");
    window->SetSize(300, 100);
    window->Hide();
    
    Gwen::Controls::Label* prompt_label = new Gwen::Controls::Label(window);
    prompt_label->SetText(prompt);
    prompt_label->SizeToContents();

    option_b = new Gwen::Controls::Button(window);
    option_b->SetText(b);
    option_b->SetSize(100, 24);
    option_b->SetPos(184, 40);
    option_b->onPress.Add(this, &Confirm::option_b_OnPress);

    option_a = new Gwen::Controls::Button(window);
    option_a->SetText(a);
    option_a->SetSize(100, 24);
    option_a->SetPos(78, 40);
    option_a->onPress.Add(this, &Confirm::option_a_OnPress);
}

Confirm::~Confirm()
{
    delete window;
}

/*
void Confirm::SetOptionAHandler(Gwen::Event::Handler* self, void(Gwen::Event::Handler::*handler)(Gwen::Controls::Base*))

void Confirm::SetOptionBHandler(Gwen::Event::Handler* self, void(Gwen::Event::Handler::*handler)(Gwen::Controls::Base*))
{
    option_b_this = self;
    option_b_handler = handler;
}
*/

void Confirm::Show()
{
    window->SetPos((window->GetParent()->Width() - window->Width()) / 2, (window->GetParent()->Height() - window->Height()) / 2);
    window->Show();
}

void Confirm::Hide()
{
    window->Hide();
}

void Confirm::option_a_OnPress(Gwen::Controls::Base* sender)
{
    if(option_a_this) {
        (option_a_this->*option_a_handler)(sender);
    }
}

void Confirm::option_b_OnPress(Gwen::Controls::Base* sender)
{
    if(option_b_this) {
        (option_b_this->*option_b_handler)(sender);
    }
}