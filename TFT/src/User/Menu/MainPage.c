#include "MainPage.h"
#include "includes.h"

void menuMain(void)
{
  // 1 title, ITEM_PER_PAGE items(icon+label)
  MENUITEMS mainPageItems = {
    // title
    LABEL_ROBOBEND,
    // icon              label
    {{ICON_ROBOBEND_PRODUCE, LABEL_ROBOBEND_PRODUCE},
     {ICON_ROBOBEND_INSERT, LABEL_ROBOBEND_INSERT},
     {ICON_ROBOBEND_REMOVE, LABEL_ROBOBEND_REMOVE},
     {ICON_BACKGROUND, LABEL_BACKGROUND},
     {ICON_BACKGROUND, LABEL_BACKGROUND},
     {ICON_BACKGROUND, LABEL_BACKGROUND},  
     {ICON_ROBOBEND_HELP, LABEL_ROBOBEND_HELP},
     {ICON_ROBOBEND_PARAMETERS, LABEL_ROBOBEND_PARAMETERS}}
  };

  KEY_VALUES key_num = KEY_IDLE;

  menuDrawPage(&mainPageItems);

  while (infoMenu.menu[infoMenu.cur] == menuMain)
  {
    key_num = menuKeyGetValue();
    switch (key_num)
    {
      case KEY_ICON_0:        
        break;

      case KEY_ICON_1:
        setDialogText(LABEL_ROBOBEND_INSERT, LABEL_ROBOBEND_INSERT_POPUP, LABEL_CONFIRM, LABEL_CANCEL);
        showDialog(DIALOG_TYPE_QUESTION, insertWire, NULL, NULL);    
        break;

      case KEY_ICON_2:  
        setDialogText(LABEL_ROBOBEND_REMOVE, LABEL_ROBOBEND_REMOVE_POPUP, LABEL_CONFIRM, LABEL_CANCEL);
        showDialog(DIALOG_TYPE_QUESTION, removeWire, NULL, NULL);       
        break;

      case KEY_ICON_3:        
        break;

      case KEY_ICON_4:        
        break;

      case KEY_ICON_5:        
        break;

      case KEY_ICON_6:
        break;

      case KEY_ICON_7:        
        break;

      default:
        break;
    }

    loopProcess();
  }
}

void insertWire()
{
  storeCmd(CUSTOM_0_GCODE);
  setDialogText(LABEL_ROBOBEND_INSERT, LABEL_BUSY, LABEL_CONFIRM, LABEL_BACKGROUND);
  showDialog(DIALOG_TYPE_INFO, NULL, NULL, NULL);
}

void removeWire()
{
  storeCmd(CUSTOM_1_GCODE);
  setDialogText(LABEL_ROBOBEND_REMOVE, LABEL_BUSY, LABEL_CONFIRM, LABEL_BACKGROUND);
  showDialog(DIALOG_TYPE_INFO, NULL, NULL, NULL);
}

