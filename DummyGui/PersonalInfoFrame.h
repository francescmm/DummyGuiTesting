#ifndef PERSONALINFOFRAME_H
#define PERSONALINFOFRAME_H

#include <QFrame>

class PersonalInfoFrame : public QFrame
{
    Q_OBJECT

    public:
        explicit PersonalInfoFrame (QWidget *parent = nullptr);

    friend class MainWindowTest;
};

#endif // PERSONALINFOFRAME_H
