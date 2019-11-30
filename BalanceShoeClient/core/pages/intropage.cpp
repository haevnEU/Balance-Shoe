#include "intropage.h"
#include "windowhandler.h"  // Used to access another window

using namespace haevn::esp::pages;

IntroPage::IntroPage(QWidget *parent) : QWidget(parent){
    auto layout = new QVBoxLayout;
    auto labelName = new QLabel("Balance Shoe");
    auto buttonStartSetup = new QPushButton("Setup");
    auto font = labelName->font();

    font.setPointSize(64);

    labelName->setFont(font);
    font.setPointSize(32);
    buttonStartSetup->setFont(font);

    layout->addWidget(labelName);
    layout->addItem(new QSpacerItem(10, 500));
    layout->addWidget(buttonStartSetup);

    layout->setAlignment(Qt::AlignCenter);
    setLayout(layout);
    connect(buttonStartSetup, &QPushButton::pressed, this, &IntroPage::buttonStartSetupPressed);
}

void IntroPage::buttonStartSetupPressed(){
    haevn::esp::pages::WindowHandler::getWindowHandler().show(haevn::esp::pages::windows::mainWindow);
}
