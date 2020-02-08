/*
 * Copyright 2020 nils
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#include "welcomepage.h"
#include "pagehandler.h"
#include <QtGlobal>
#include <QIntValidator>

WelcomePage::WelcomePage(QWidget *parent) : QWidget(parent), model(Model::getInstance()), esp(ESP32::getInstance()){

    inName = new QLineEdit(this);
    inMaxWeight = new QLineEdit(this);

    btNext = new QPushButton(this);
    lbError = new QLabel("", this);

    QLabel* lbName = new QLabel("Name: ", this);
    QLabel* lbWelcome = new QLabel("Wilkommen", this);
    QLabel* lbMaxWeight = new QLabel("Maximales Gewicht: ", this);
    QLabel* lbInfoText = new QLabel("Gib deine Basics ein.", this);

    lbName->setFixedWidth(150);
    lbMaxWeight->setFixedWidth(150);

    QFont font = lbWelcome->font();
    QGridLayout* layout = new QGridLayout(this);

    displayed = false;

    inMaxWeight->setValidator(new QIntValidator(0, 500, this));

    font.setPointSize(32);
    lbWelcome->setFont(font);
    lbWelcome->setAlignment(Qt::AlignHCenter);
    layout->addWidget(lbWelcome, 0, 0, 1, 3);

    font.setPointSize(24);
    lbInfoText->setFont(font);
    lbInfoText->setAlignment(Qt::AlignHCenter);
    layout->addWidget(lbInfoText, 1, 0, 1, 3);

    font.setPointSize(16);

    lbError->setFont(font);
    lbError->setAlignment(Qt::AlignHCenter);
    layout->addWidget(lbError, 2, 0, 1, 3);

    lbName->setFont(font);
    lbName->setAlignment(Qt::AlignLeft);
    layout->addWidget(lbName, 3, 0);
    layout->addWidget(inName, 3, 1, 1, 2);



    lbMaxWeight->setFont(font);
    lbMaxWeight->setAlignment(Qt::AlignLeft);
    layout->addWidget(lbMaxWeight, 4, 0);
    layout->addWidget(inMaxWeight, 4, 1, 1, 2);


    layout->addWidget(new ConnectPage("", false, &font, this), 5, 0, 1, 3);

    layout->addWidget(btNext, 11, 2, 1, 1);

    connect(btNext, &QPushButton::pressed, this, &WelcomePage::buttonNextPressed);

    inName->setText(model.getName());
    setLayout(layout);

    btNext->setFlat(true);

    btNext->setIcon(QIcon(":/icons/res/baseline_navigate_next_white.png"));

}

WelcomePage::~WelcomePage(){}

void WelcomePage::buttonNextPressed(){
    // 1. Validate
    if("" == inName->text() || "" == inMaxWeight->text()){
        lbError->setText("Name oder Gewicht fehlen");
        return;
    }
    // 2. Set Values
    model.setName(inName->text());
    model.setMaxWeight(inMaxWeight->text().toInt());

    // 3. Send Values

    PageHandler::getInstance().requestPage(page::mainPage);
}

void WelcomePage::show(){
    displayed = true;
    QWidget::show();
}

void WelcomePage::hide(){

    displayed = false;
    QWidget::hide();
}

bool WelcomePage::isDisplayed(){
    return displayed;
}
