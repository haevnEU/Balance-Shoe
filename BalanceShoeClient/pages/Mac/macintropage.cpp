/*
 * Copyright 2019 nils
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
#include "macintropage.h"

#if defined(Q_OS_MAC)

#include "core/windowhandler.h"  // Used to access another window

using namespace haevn::esp::pages;

MacIntroPage::MacIntroPage(QWidget *parent) : QWidget(parent){
    auto layout = new QVBoxLayout;
    auto labelName = new QLabel("Balance Shoe");
    auto buttonStartSetup = new QPushButton("Setup");
    auto font = labelName->font();

    font.setPointSize(64);

    labelName->setFont(font);
    font.setPointSize(32);
    buttonStartSetup->setFont(font);

    layout->addWidget(labelName);
    layout->addWidget(buttonStartSetup);

    layout->setAlignment(Qt::AlignCenter);
    setLayout(layout);
    connect(buttonStartSetup, &QPushButton::pressed, this, &MacIntroPage::buttonStartSetupPressed);
}

void MacIntroPage::buttonStartSetupPressed(){
    haevn::esp::core::WindowHandler::getWindowHandler().show(haevn::esp::core::windows::mainWindow);
}


#endif // defined(Q_OS_MAC)
