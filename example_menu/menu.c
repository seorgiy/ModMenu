#include "mod_menu\menu_utils.c" // НЕ УДАЛЯТЬ. DO NOT REMOVE THAT

void OnMenuOpen()
{
  // Set title
  // Ставим заголовок
  SetFormatedText("MOD_TITLE", "EXAMPLE MENU");

  // Set checkboxes states
  // Меняем состояние чекбоксов
  SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "EXAMPLE_CHECKBOX1", 2, 1, 1);
  SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "EXAMPLE_CHECKBOX2", 2, 1, 0);

  SetEventHandler("ievnt_command","ProcCommand",0);
}

// Delete all your event handlers
// Не забываем чистить обработчики событий
void OnMenuClose()
{
  DelEventHandler("ievnt_command","ProcCommand");
}

// Here define your interact actions
// Обрабатываем взаимодействие с элементами меню
void ProcCommand()
{
  string comName = GetEventData();
  string nodName = GetEventData();

  switch(nodName)
  {
    Log_Info("nodNm: " + nodName + " comName " + comName);
  }
}
