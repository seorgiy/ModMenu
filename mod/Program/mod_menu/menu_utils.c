string menuIni = "";
string menuScript = "";

// Инициализируем менюшку мода
void ModMenu_InitInterface(string iniName, string scriptName)
{
  StartAboveForm(true);
  menuIni = iniName;
  menuScript = scriptName;
  SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT, iniName);
  CurrentInterface = 99999;
  SetEventHandler("ModMenu_CloseMenu","ModMenu_CloseMenu",0);
  OnMenuOpen(); // хук для действий из менюшки
}

// Выгружаем менюшку мода
void ModMenu_CloseMenu()
{
  EndAboveForm(true);
  DelEventHandler("ModMenu_CloseMenu","ModMenu_CloseMenu");
  if(bSeaActive){RefreshBattleInterface();}
  KillMessageBox();
  KillIconSelector();
  bGamePadChangeEnable = false;
  InterfaceStates.doUnFreeze = true;
  IDeleteSoundEvents();
  UnloadSegment(menuIni);

  if(IsPerkIntoList("TimeSpeed")) {SetTimeScale(GetSeaTimeScale());}

  SetEventHandler("frame", "ModMenu_CloseMenuRelease", 1);
  OnMenuClose(); // хук для действий из менюшки
}

// Чистим остатки менюшки
void ModMenu_CloseMenuRelease()
{
  CurrentInterface = INTERFACE_GAMEMENU;
  interfaceResultCommand = RC_INTERFACE_ANY_EXIT;
  DelEventHandler("frame","ModMenu_CloseMenuRelease");
  InterfaceStates.Launched = false;
  UnloadSegment(menuScript);
  SendMessage(&GameInterface,"l",MSG_INTERFACE_RELEASE);
}
