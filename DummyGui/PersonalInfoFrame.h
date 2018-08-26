#ifndef PERSONALINFOFRAME_H
#define PERSONALINFOFRAME_H

#include <QFrame>

class QCheckBox;
class QRadioButton;

class PersonalInfoFrame : public QFrame
{
      Q_OBJECT

   public:
      explicit PersonalInfoFrame (QWidget *parent = nullptr);

   private:
      QCheckBox *checkbox = nullptr;
      QRadioButton *radiobutton = nullptr;

      friend class MainWindowTest;
};

#endif // PERSONALINFOFRAME_H
