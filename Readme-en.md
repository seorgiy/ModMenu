[На русском](https://github.com/seorgiy/ModMenu/blob/main/README.md) :point_left:

This is a dev mod repository for the Caribbean Legend game.<br>
[Workshop link](https://steamcommunity.com/sharedfiles/filedetails/?id=3501393265)

Allows you to add settings for your mod to the game menu.

### How to use
1. Subscribe to the mod in the workshop.
2. Add it to the list of required products for the mod where you want to use it, so that players also subscribe to it.
3. In the folder of your mod, create the folder Program/mod_menu/YOUR_MOD, copy two files from the [sample folder](https://github.com/seorgiy/ModMenu/tree/main/example_menu), this is the menu template.

Now you can edit these two files for your mod by adding any buttons, checkboxes and everything else that the interface of the mod can offer you. See how other game menus are made and do the same.

PS To make your mod appear beautifully in the user's list, add a localization key with the name of your mod. That is, in the Resource/texts/LANGUAGE/mods/YOUR_MOD/common.ini file, add something like
```
string = daivy_cool_ships, "Daivy's Cool ships`
```
Where daivy_cool_ships is the name of your mod's folder in Program/mod_menu.

### Nuances

If the player deletes the mod menu, it simply won't be shown. The mod will not replace any original files.
You are free to redo your menu as you like, but it is advisable to adhere to the general style of the game so that the player does not get confused.

For all questions, please join [Discord](https://discord.gg/7Wmy4rzywC).
