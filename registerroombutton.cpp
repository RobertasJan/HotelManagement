#include "registerroombutton.h"

RegisterRoomButton::RegisterRoomButton (const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    // setting size
    setFixedSize(100,30);
}
