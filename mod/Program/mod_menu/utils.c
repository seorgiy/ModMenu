// Находим моды с настройками и складываем имена в массив, возвращаем размер массива
int ModMenu_GetModsNames(ref result)
{
  int n = 1;
  string searchPath = "program\\mod_menu";
  object fileFinder;
  fileFinder.dir = searchPath;
  fileFinder.mask = "*";
  fileFinder.onlydirs = "1";
  fileFinder.onlyfiles = "0";
  CreateEntity(&fileFinder, "FINDFILESINTODIRECTORY");
  DeleteClass(&fileFinder);

  aref fileList;
  makearef(fileList, fileFinder.filelist);
  int filesNum = GetAttributesNum(fileList);

  for (int i = 0; i < filesNum; i++) {
    aref file = GetAttributeN(fileList, i);
    string fileName = GetAttributeValue(file);
    object fileFinderRes;
    fileFinderRes.dir = "program\\mod_menu\\" + fileName;
    fileFinderRes.mask = "menu.ini";
    fileFinderRes.onlydirs = "0";
    fileFinderRes.onlyfiles = "1";
    CreateEntity(&fileFinderRes, "FINDFILESINTODIRECTORY");
    DeleteClass(&fileFinderRes);
    aref fileResList;
    makearef(fileResList, fileFinderRes.filelist);
    if (fileName == "mod_options") continue;
    if (GetAttributesNum(&fileResList) < 1) continue;

    SetArraySize(&result, n);
    result[n-1] = fileName;
    n++;
  }

  return n-1;
}

// Просто обертка для путей к инишкам/скриптам менюшек
string ModMenu_GetPath(string fileName, string type)
{
  if (type == "ini") return "program\mod_menu\" + fileName + "\menu.ini";
  else return "mod_menu\" + fileName + "\menu.c";
}
  