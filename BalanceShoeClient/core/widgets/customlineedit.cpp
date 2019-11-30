#include "customlineedit.h"

#if defined(Q_OS_ANDROID)

using namespace haevn::esp::widgets;

CustomLineEdit::CustomLineEdit(QWidget* parent) : QLineEdit(parent){
    setAttribute(Qt::WA_AcceptTouchEvents);
}

void CustomLineEdit::focusInEvent(QFocusEvent *e){
  QLineEdit::focusInEvent(e);
    QInputMethod* kb = QGuiApplication::inputMethod();
    kb->show();
  emit(focussed(true));
}

void CustomLineEdit::focusOutEvent(QFocusEvent *e){
  QLineEdit::focusOutEvent(e);

  QInputMethod* kb = QGuiApplication::inputMethod();
  kb->hide();

  emit(focussed(false));
}

#endif // defined(Q_OS_ANDROID)
