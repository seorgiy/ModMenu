#include "mod_menu\utils.c"

#event_handler("Interface_Started", "ModMenu_InjectModMenu");

extern void ModMenu_InitInterface(string iniFile, string scriptFile);

// Если открылось главное меню, в следующий кадр наводим суету
void ModMenu_InjectModMenu()
{
  SetEventHandler("frame", "ModMenu_InjectModMenuDelayed", 1);
}

// Наводим суету
void ModMenu_InjectModMenuDelayed()
{
  DelEventHandler("frame", "ModMenu_InjectModMenuDelayed");
  if (CurrentInterface != INTERFACE_GAMEMENU) return;

  SetEventHandler("frame", "ModMenu_CreateOptionsButton", 1);
  SetEventHandler("ModMenu_ShowModList", "ModMenu_ShowModList", 1);
  SetEventHandler("OnTableClick","ModMenu_ClickOnMod",0);
  SetEventHandler("ModMenu_IDoExit","ModMenu_IDoExit",0);
  SetEventHandler("ievnt_command","ModMenu_ProcessCommandExecute",0);
}

// Кликнули на мод в табличке, убиваем текущий интерфейс, открываем новый с задержкой
void ModMenu_ClickOnMod()
{
  string sControl = GetEventData();
  if (sControl != "MODS_LIST") return;

  string rowName = "tr" + (GetEventData() + 1);
  string modId = GameInterface.MODS_LIST.(rowName).modId;

  SetEventHandler("ModMenu_ShowModMenu", "ModMenu_ShowModMenu", 1);
  PostEvent("ModMenu_ShowModMenu", 200, "s", modId);
  ModMenu_IDoExit();
}

// Открываем интерфейс мода
void ModMenu_ShowModMenu()
{
  DelEventHandler("ModMenu_ShowModMenu", "ModMenu_ShowModMenu");
  string modId = GetEventData();
  string sIni = ModMenu_GetPath(modId, "ini"); 
  string sScript = ModMenu_GetPath(modId, "script");

  if (ModMenu_procInterfacePrepare(sScript)) ModMenu_InitInterface(sIni, sScript);
  else ModMenu_IDoExit();
}

// Засовываем кнопку настроек модов в менюшку
void ModMenu_CreateOptionsButton()
{
  XI_MakeNode("resource\ini\interfaces\mods\mod_menu\mod_menu.ini", "TEXTBUTTON", "MOD_MENU_BUTTON", 60002);
  DelEventHandler("frame", "ModMenu_CreateOptionsButton");
}

// Показываем список модов
void ModMenu_ShowModList()
{
  string sIni = "resource\ini\interfaces\mods\mod_menu\mod_menu.ini";
  string row;
  XI_MakeNode(sIni, "PICTURE", "PAPER", 60002);
  XI_MakeNode(sIni, "STRINGCOLLECTION", "TITLES", 60002);
  XI_MakeNode(sIni, "IMAGECOLLECTION", "TITLE_DIVIDER", 60002);
  XI_MakeNode(sIni, "TABLE", "MODS_LIST", 60002);
  XI_MakeNode(sIni, "SCROLLER", "SCROLL_MODS", 60002);

  aref table;
  makearef(table, GameInterface.MODS_LIST);
  table.select = 0;
  table.top = 0;

  string modNames[2];
  int modsCount = ModMenu_GetModsNames(&modNames);

  if (ModMenu_ShowNoMods(sIni, modsCount)) return; // а есть ли вообще моды с настройками?

  for(int i=0; i < modsCount; i++)
  {
    row = "tr" + (i+1);
    string modName = xiStr(modNames[i]);
    if (modName != "") table.(row).td1.str = modName;
    else table.(row).td1.str = modNames[i];
    table.(row).modId = modNames[i];
  }

  Table_UpdateWindow("MODS_LIST");
}

// Если не нашли модов, показываем ошибку
bool ModMenu_ShowNoMods(string sIni, int modsCount)
{
  if (modsCount > 0) return false;

  XI_DeleteNode("MODS_LIST");
  XI_DeleteNode("SCROLL_MODS");
  XI_MakeNode(sIni, "FORMATEDTEXT", "NO_MODS", 60002);
  return true;
}

// Здесь какая-то родная проверка интерфейсных файлов, дублируем логику
bool ModMenu_procInterfacePrepare(string interfaceName)
{
  if(!ModMenu_procEnableInterfaceLaunch()) return false;
  if(g_ibVideoExecuting) return false;

  if(LoadSegment(interfaceName) )
  {
    Telescope_Off();
    Event("Interface_Started");
    InterfaceStates.Launched = true;
    InterfaceStates.doUnFreeze = false;
    EngineLayersOffOn(false);
    ISetSoundEvents();
    DeleteAttribute(&GameInterface,"");
    DeleteAttribute(&InterfaceStates,"tooltip");
    TimeScale_Info("");
    LayerFreeze(INTERFACE_REALIZE,false);
    LayerFreeze(INTERFACE_EXECUTE,false);
    return true;
  }
  else
  {
    interfaceResultCommand = RC_INTERFACE_ERROR;
    Start_InterfaceDoExit();
    return false;
  }
}

// Здесь какая-то родная проверка интерфейсных файлов, дублируем логику
bool ModMenu_procEnableInterfaceLaunch()
{
  if(sti(InterfaceStates.Launched)==true) return false;
  if(IsEntity(reload_fader)) return false;
  if(DialogRun!=0) return false;
  return true;
}

// Чистим все следы и закрываемся с невинным видом
void ModMenu_IDoExit()
{
  DelEventHandler("ModMenu_ShowModList", "ModMenu_ShowModList");
  DelEventHandler("ModMenu_IDoExit","ModMenu_IDoExit");
  DelEventHandler("OnTableClick","ModMenu_ClickOnMod");
  DelEventHandler("ievnt_command","ModMenu_ProcessCommandExecute");
  CurrentInterface = INTERFACE_GAMEMENU;
  Event("ExitCancel");
}

void ModMenu_ProcessCommandExecute()
{
  string comName = GetEventData();
  string nodName = GetEventData();

  switch(nodName)
  {
    case "MB_EXITGAME":
      if (comName == "click" || comName == "activate")
      {
        XI_DeleteNode("MODS_LIST");
        XI_DeleteNode("SCROLL_MODS");
        XI_DeleteNode("PAPER");
        XI_DeleteNode("TITLES");
        XI_DeleteNode("TITLE_DIVIDER");
        XI_DeleteNode("SCROLL_MODS");
        XI_DeleteNode("NO_MODS");
      }
    break;
  }
}
