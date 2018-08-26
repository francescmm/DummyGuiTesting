#include "PersonalInfoFrame.h"
#include <QCheckBox>
#include <QRadioButton>
#include <QVBoxLayout>

PersonalInfoFrame::PersonalInfoFrame(QWidget *parent)
   : QFrame (parent)
{
   checkbox = new QCheckBox("Checkbox Text");

   radiobutton = new QRadioButton("RadioButton Text");

   auto layout = new QVBoxLayout();
   layout->addWidget (checkbox);
   layout->addWidget (radiobutton);

   setLayout (layout);
}
