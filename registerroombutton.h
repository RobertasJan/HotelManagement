#ifndef REGISTERROOMBUTTON_H
#define REGISTERROOMBUTTON_H

#include <QPushButton>


class RegisterRoomButton : public QPushButton
{
    Q_OBJECT
public:
    RegisterRoomButton(const QString& text, QWidget *parent = 0);
};

#endif // REGISTERROOMBUTTON_H
