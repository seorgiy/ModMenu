#include "mod_menu\menu_utils.c" // НЕ УДАЛЯТЬ. DO NOT REMOVE THAT

void OnMenuOpen()
{
  // Set title
  // Ставим заголовок
  SetFormatedText("MOD_TITLE", "EXAMPLE MENU");

  // Set checkboxes states
  // Меняем состояние чекбоксов
  SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "EXAMPLE_CHECKBOX1", 2, 1, Example_OptionEnabled("exampleOption1"));
  SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "EXAMPLE_CHECKBOX2", 2, 1, Example_OptionEnabled("exampleOption2"));

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

  if (comName != "click") return;

  switch(nodName)
  {
    Log_Info("nodName: " + nodName + " comName: " + comName);
    case "EXAMPLE_CHECKBOX1": Example_OptionSwitch("exampleOption1"); break;
    case "EXAMPLE_CHECKBOX2": Example_OptionSwitch("exampleOption2"); break;
  }
}

void Example_OptionSwitch(string option)
{
  bool state = Example_OptionEnabled(option);
  InterfaceStates.ExampleOptions.(option) = !state;  //switch
  Log_Info(option + ": " + InterfaceStates.ExampleOptions.(option))
}

bool Example_OptionEnabled(string option)
{
  if (CheckAttribute(&InterfaceStates, "ExampleOptions." + option)) return sti(InterfaceStates.ExampleOptions.(option)) != 0;  //return current value
  if (option == "exampleOption2") return false;  //default false
  return true;  //rest default true
}
