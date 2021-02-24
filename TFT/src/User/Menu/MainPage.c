#include "MainPage.h"
#include "includes.h"

char * _rbPopupMessage = "PLACEHOLDER";
FP_MENU _rbPopupNextMenu;

void menuMain2(void)
{
  // 1 title, ITEM_PER_PAGE items(icon+label)
  MENUITEMS mainPageItems = {
    // title
    LABEL_ROBOBEND,
    // icon              label
    {{ICON_RB_PRODUCE, LABEL_ROBOBEND_PRODUCE},
     {ICON_RB_INSERT_WIRE, LABEL_ROBOBEND_INSERT},
     {ICON_RB_REMOVE_WIRE, LABEL_ROBOBEND_REMOVE},
     {ICON_BACKGROUND, LABEL_BACKGROUND},
     {ICON_BACKGROUND, LABEL_BACKGROUND},
     {ICON_BACKGROUND, LABEL_BACKGROUND},  
     {ICON_RB_HELP, LABEL_ROBOBEND_HELP},
     {ICON_RB_PARAMETERS, LABEL_ROBOBEND_PARAMETERS}}
  };

  KEY_VALUES key_num = KEY_IDLE;

  menuDrawPage(&mainPageItems);

  while (infoMenu.menu[infoMenu.cur] == menuMain)
  {
    key_num = menuKeyGetValue();
    switch (key_num)
    {
      case KEY_ICON_0:   
        infoMenu.menu[++infoMenu.cur] = menuPrint;      
        break;

      case KEY_ICON_1:
        _rbPopupMessage = "Procéder au chargement du fil ?";
        _rbPopupNextMenu = menuInsertWire;
        infoMenu.menu[++infoMenu.cur] = popupValidation;   
        break;

      case KEY_ICON_2:     
        _rbPopupMessage = "Retirer le fil ?";
        _rbPopupNextMenu = menuRemoveWire;
        infoMenu.menu[++infoMenu.cur] = popupValidation;    
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
        //infoMenu.menu[++infoMenu.cur] = menuSettings;     
        break;

      default:
        break;
    }

    loopProcess();
  }
}

void menuMain(void)
{
  GUI_Clear(infoSettings.bg_color);
  GUI_SetTextMode(GUI_TEXTMODE_TRANS);
  GUI_SetColor(WHITE);

  uint cellWidth = LCD_WIDTH / 3;
  uint cellHeight = LCD_HEIGHT / 2;
  uint offsetWidth = (cellWidth - ICON_WIDTH) / 2;
  uint offsetHeight = (cellHeight - ICON_HEIGHT) / 2;

  GUI_RECT btnProduceRect = {offsetWidth, offsetHeight, offsetWidth+ICON_WIDTH, offsetHeight+ICON_HEIGHT+BYTE_HEIGHT};
  GUI_RECT btnInsertRect = {offsetWidth+cellWidth, offsetHeight, offsetWidth+cellWidth+ICON_WIDTH, offsetHeight+ICON_HEIGHT+BYTE_HEIGHT};
  GUI_RECT btnRemoveRect = {offsetWidth+cellWidth*2, offsetHeight, offsetWidth+cellWidth*2+ICON_WIDTH, offsetHeight+ICON_HEIGHT+BYTE_HEIGHT};

  GUI_RECT btnHelpRect = {offsetWidth*2+cellWidth, offsetHeight+cellHeight, offsetWidth*2+cellWidth+ICON_WIDTH, offsetHeight+cellHeight+ICON_HEIGHT};
  GUI_RECT btnParametersRect = {offsetWidth+cellWidth*2, offsetHeight+cellHeight, offsetWidth+cellWidth*2+ICON_WIDTH, offsetHeight+cellHeight+ICON_HEIGHT};

  // Icons.
  ICON_ReadDisplay(btnProduceRect.x0, btnProduceRect.y0, ICON_RB_PRODUCE);
  ICON_ReadDisplay(btnInsertRect.x0, btnInsertRect.y0, ICON_RB_INSERT_WIRE);
  ICON_ReadDisplay(btnRemoveRect.x0, btnRemoveRect.y0, ICON_RB_REMOVE_WIRE);
  ICON_ReadDisplay(btnHelpRect.x0, btnHelpRect.y0, ICON_RB_HELP);
  ICON_ReadDisplay(btnParametersRect.x0, btnParametersRect.y0, ICON_RB_PARAMETERS);

  // Logo size: 152 x 22
  ICON_ReadDisplay(30, cellHeight + (cellHeight - 22) / 2, ICON_RB_ROBOBEND);
  
  // Labels.
  GUI_DispStringCenter(cellWidth / 2,  cellHeight - BYTE_HEIGHT, (uint8_t *)"Fabriquer");
  GUI_DispStringCenter(cellWidth + cellWidth / 2,  cellHeight - BYTE_HEIGHT, (uint8_t *)"Insérer fil");
  GUI_DispStringCenter(2*cellWidth + cellWidth / 2,  cellHeight - BYTE_HEIGHT, (uint8_t *)"Retirer fil");

  const GUI_RECT btnRect[] = { btnProduceRect, btnInsertRect, btnRemoveRect, btnHelpRect, btnParametersRect };

  while (infoMenu.menu[infoMenu.cur] == menuMain)
  {
    uint16_t key_num = KEY_GetValue(5, btnRect);
    switch (key_num)
    {
      // Produce.
      case 0:   
        infoMenu.menu[++infoMenu.cur] = menuPrint;          
        break;

      // Insert.
      case 1:
        _rbPopupMessage = "Procéder au chargement du fil ?";
        _rbPopupNextMenu = menuInsertWire;
        infoMenu.menu[++infoMenu.cur] = popupValidation;      
        break;

      // Remove.
      case 2:
          _rbPopupMessage = "Retirer le fil ?";
          _rbPopupNextMenu = menuRemoveWire;
          infoMenu.menu[++infoMenu.cur] = popupValidation;       
        break;

      // Help.
      case 3:        
        break;

      // Parameters.
      case 4:        
        break;

      default:
        break;
    }

    loopProcess();
  }
}

void popupValidation()
{
  uint radius = 20;
  uint start_x = 50;
  uint start_y = 50;
  uint end_x = 430;
  uint end_y = 140;
  uint start_x_icon_back = start_x - radius;
  uint start_x_icon_ok = LCD_WIDTH - ICON_WIDTH -  start_x + radius;
  uint start_y_icon = 175;

  GUI_Clear(infoSettings.bg_color);
  GUI_SetColor(WHITE);
  GUI_FillCircle(start_x, start_y, radius);
  GUI_FillCircle(start_x, end_y, radius);
  GUI_FillCircle(end_x, start_y, radius);
  GUI_FillCircle(end_x, end_y, radius);
  GUI_FillRect(start_x - radius, start_y, end_x + radius + 1, end_y);
  GUI_FillRect(start_x, start_y - radius, end_x, end_y + radius + 1);

  GUI_SetTextMode(GUI_TEXTMODE_TRANS);
  GUI_SetColor(BLACK);
  GUI_DispStringCenter(LCD_WIDTH / 2,  start_y + (end_y - start_y) / 2 - BYTE_HEIGHT / 2, (uint8_t *)_rbPopupMessage);

  GUI_RECT btnBackRect = {start_x_icon_back, start_y_icon, start_x_icon_back + ICON_WIDTH, start_y_icon + ICON_HEIGHT};
  GUI_RECT btnOkRect = {start_x_icon_ok, start_y_icon, start_x_icon_ok + ICON_WIDTH, start_y_icon + ICON_HEIGHT};

  ICON_ReadDisplay(start_x_icon_back, start_y_icon, ICON_BACK);
  ICON_ReadDisplay(start_x_icon_ok, start_y_icon, ICON_OK);

  const GUI_RECT btnRect[] = { btnBackRect, btnOkRect };

  while (infoMenu.menu[infoMenu.cur] == popupValidation)
  {
    uint16_t key_num = KEY_GetValue(2, btnRect);
    switch (key_num)
    {
      case 0:
        GUI_RestoreColorDefault();
        infoMenu.cur--;       
        break;

      case 1:
        GUI_RestoreColorDefault();
        infoMenu.menu[++infoMenu.cur] = _rbPopupNextMenu;      
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
  infoMenu.menu[++infoMenu.cur] = menuInsertWire;
}

void menuInsertWire(void)
{ 
  uint padding = 40;
  uint radius = 20;
  uint start_x = padding;
  uint start_y = padding;
  uint end_x = LCD_WIDTH - padding;
  uint end_y = LCD_HEIGHT - padding;

  GUI_Clear(infoSettings.bg_color);
  GUI_SetColor(WHITE);
  GUI_FillCircle(start_x, start_y, radius);
  GUI_FillCircle(start_x, end_y, radius);
  GUI_FillCircle(end_x, start_y, radius);
  GUI_FillCircle(end_x, end_y, radius);
  GUI_FillRect(start_x - radius, start_y, end_x + radius + 1, end_y);
  GUI_FillRect(start_x, start_y - radius, end_x, end_y + radius + 1);

  GUI_SetTextMode(GUI_TEXTMODE_TRANS);
  GUI_SetColor(BLACK);

  // 9 lines max
  // 34 char max per line
  uint text_start_x = start_x;
  uint text_start_y = start_y - BYTE_HEIGHT/2;
  GUI_DispString(text_start_x, text_start_y+0*BYTE_HEIGHT, (uint8_t *)"LED ");
  GUI_SetColor(BLUE);
  GUI_DispString(text_start_x+4*BYTE_WIDTH, text_start_y+0*BYTE_HEIGHT, (uint8_t *)"bleue");
  GUI_SetColor(BLACK);
  GUI_DispString(text_start_x, text_start_y+1*BYTE_HEIGHT, (uint8_t *)"-continue : commencez l'insertion");
  GUI_DispString(text_start_x, text_start_y+2*BYTE_HEIGHT, (uint8_t *)"-clignotante : continuez à insérer");
  GUI_DispString(text_start_x, text_start_y+3*BYTE_HEIGHT, (uint8_t *)"LED ");
  GUI_SetColor(GREEN);
  GUI_DispString(text_start_x+4*BYTE_WIDTH, text_start_y+3*BYTE_HEIGHT, (uint8_t *)"verte");
  GUI_SetColor(BLACK);
  GUI_DispString(text_start_x+9*BYTE_WIDTH, text_start_y+3*BYTE_HEIGHT, (uint8_t *)" : insertion terminée");
  GUI_DispString(text_start_x, text_start_y+4*BYTE_HEIGHT, (uint8_t *)"LED ");
  GUI_SetColor(RED);
  GUI_DispString(text_start_x+4*BYTE_WIDTH, text_start_y+4*BYTE_HEIGHT, (uint8_t *)"rouge");
  GUI_SetColor(BLACK);
  GUI_DispString(text_start_x+9*BYTE_WIDTH, text_start_y+4*BYTE_HEIGHT, (uint8_t *)" : stop");
  ICON_ReadDisplay(text_start_x, text_start_y+6*BYTE_HEIGHT, ICON_RB_WARNING);
  GUI_DispString(text_start_x+3*BYTE_WIDTH, text_start_y+6*BYTE_HEIGHT, (uint8_t *)"Attention");
  GUI_DispString(text_start_x, text_start_y+7*BYTE_HEIGHT, (uint8_t *)"Longueur du fil minimum : 150mm");
  GUI_DispString(text_start_x, text_start_y+8*BYTE_HEIGHT, (uint8_t *)"Ne pas insérer si LED éteinte");

  while(!isPress()) loopBackEnd();
  while(isPress())  loopBackEnd();

  GUI_RestoreColorDefault();
  infoMenu.cur--;
  infoMenu.cur--;
}

void removeWire()
{
  storeCmd(CUSTOM_1_GCODE);
  infoMenu.menu[++infoMenu.cur] = menuRemoveWire;
}

void menuRemoveWire(void)
{
  uint padding = 40;
  uint radius = 20;
  uint start_x = padding;
  uint start_y = padding;
  uint end_x = LCD_WIDTH - padding;
  uint end_y = LCD_HEIGHT - padding;

  GUI_Clear(infoSettings.bg_color);
  GUI_SetColor(WHITE);
  GUI_FillCircle(start_x, start_y, radius);
  GUI_FillCircle(start_x, end_y, radius);
  GUI_FillCircle(end_x, start_y, radius);
  GUI_FillCircle(end_x, end_y, radius);
  GUI_FillRect(start_x - radius, start_y, end_x + radius + 1, end_y);
  GUI_FillRect(start_x, start_y - radius, end_x, end_y + radius + 1);

  GUI_SetTextMode(GUI_TEXTMODE_TRANS);
  GUI_SetColor(BLACK);

  uint text_start_x = start_x;
  uint text_start_y = start_y - BYTE_HEIGHT/2;
  GUI_DispString(text_start_x, text_start_y+0*BYTE_HEIGHT, (uint8_t *)"LED ");
  GUI_SetColor(BLUE);
  GUI_DispString(text_start_x+4*BYTE_WIDTH, text_start_y+0*BYTE_HEIGHT, (uint8_t *)"bleue");
  GUI_SetColor(BLACK);
  GUI_DispString(text_start_x+9*BYTE_WIDTH, text_start_y+0*BYTE_HEIGHT, (uint8_t *)" clignotante : retrait en");
  GUI_DispString(text_start_x, text_start_y+1*BYTE_HEIGHT, (uint8_t *)"cours");
  GUI_DispString(text_start_x, text_start_y+3*BYTE_HEIGHT, (uint8_t *)"LED ");
  GUI_SetColor(GREEN);
  GUI_DispString(text_start_x+4*BYTE_WIDTH, text_start_y+3*BYTE_HEIGHT, (uint8_t *)"verte");
  GUI_SetColor(BLACK);
  GUI_DispString(text_start_x+9*BYTE_WIDTH, text_start_y+3*BYTE_HEIGHT, (uint8_t *)" : fil retiré");
  ICON_ReadDisplay(text_start_x, text_start_y+5*BYTE_HEIGHT, ICON_RB_WARNING);
  GUI_DispString(text_start_x+3*BYTE_WIDTH, text_start_y+5*BYTE_HEIGHT, (uint8_t *)"Attention");
  GUI_DispString(text_start_x, text_start_y+6*BYTE_HEIGHT, (uint8_t *)"Ne pas toucher le fil quand la LED");
  GUI_DispString(text_start_x, text_start_y+7*BYTE_HEIGHT, (uint8_t *)"clignote ou est éteinte");

  while(!isPress()) loopBackEnd();
  while(isPress())  loopBackEnd();

  GUI_RestoreColorDefault();
  infoMenu.cur--;
  infoMenu.cur--;
}

void menuHelp(void)
{
  uint padding = 40;
  uint radius = 20;
  uint start_x = padding;
  uint start_y = padding;
  uint end_x = LCD_WIDTH - padding;
  uint end_y = LCD_HEIGHT - padding;

  GUI_Clear(infoSettings.bg_color);
  GUI_SetColor(WHITE);
  GUI_FillCircle(start_x, start_y, radius);
  GUI_FillCircle(start_x, end_y, radius);
  GUI_FillCircle(end_x, start_y, radius);
  GUI_FillCircle(end_x, end_y, radius);
  GUI_FillRect(start_x - radius, start_y, end_x + radius + 1, end_y);
  GUI_FillRect(start_x, start_y - radius, end_x, end_y + radius + 1);

  GUI_SetTextMode(GUI_TEXTMODE_TRANS);
  GUI_SetColor(BLACK);

  uint text_start_x = start_x;
  uint text_start_y = start_y - BYTE_HEIGHT/2;

  while(!isPress()) loopBackEnd();
  while(isPress())  loopBackEnd();

  GUI_RestoreColorDefault();
  infoMenu.cur--;
  infoMenu.cur--;
}