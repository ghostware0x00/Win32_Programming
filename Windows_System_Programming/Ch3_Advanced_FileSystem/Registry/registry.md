## What is Registry

- a centrailized hierarchical database where windows low level configurations and other values are set.
- how the operating system will work, what values to work with, os kernel, and other user applcations related configurations and settings are present here
- access to this registry is through **registry keys**.
- these **registry keys** contain key value pairs of other values or files and directories.
- user or administrator can view the registry contents through the **registry editor** using the `regedit` command.


## Registry Structure

- The Registry is divided in a tree-like hirerarchy structure similary to files and folders in our computer.
- Its divided into the following stuff :-
    - Hives (Root keys)
    - Keys and Subkeys
    - Values 

## Registry Keys

- `HKEY_LOCAL_MACHINE`:
    - stores physical information about the machine, along with information about installed software.

- `HKEY_USERS`:
    - defines user configuration information.

- `HKEY_CURRENT_CONFIG`:
    - contains the current settings, such as display information, fonts, colors ... etc ...

- `HKEY_CLASSES_ROOT` :
    - contains file name extension associations i.e. which application should be used to open that software, contains info about how Windows should interact with other programs, files and user interface

- `HKEY_CUURENT_USER`:
    - contains user specific information, including environment variables, application preferences ... etc ...

## DATATYPES

### `HKEY`

- is like a pointer which identifies a currently open key or predefined reserved key handle for (e.g., `HKEY_LOCAL_MACHINE`, `HKEY_CURRENT_USER`)
