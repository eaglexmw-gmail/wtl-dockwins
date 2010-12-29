WTL Docking windows Version 0.9.3
---------------------------------

Major changes in 0.9.3 release:

* bugs ;)
* A Storing/Restoring application setting implementation improved.
* Docked windows scaling slightly changed.

Major changes in 0.9.241 release:

* A Storing/Restoring application setting implementation changed.
  Instead of CRegKey an IStorge general class is used. So now it's possible to 
  implement own storage. For example you can store application setting in the XML 
  file, please take a look CStgRegistry and CStgXML classes for sample implementation.
  To store application setting as in previous version use CStgRegistry class as 
  parameter for CWindowStateMgr template. CWindowStateMgr is template now and it 
  use IStorge derived class as parameter. Take a look MDIExSample to get a clue
  how to use it.
  Also you can use CStgXML class to store setting in xml file. 
  But CStgXML is not finished yet and provided just for sample, you can use it
  but better to write you own.

Major changes in 0.9.24 release:

* Some bugs fixed, and lot of new added:).

Major changes in 0.9.1 release:

* Added auto-hiding features support. To add auto-hiding features to your
  project just include the DWAutoHide.h header before any other docking
  windows headers.
* Added DockImpl.cpp so please add DockImpl.cpp to the project.
  Probably the best way to do it is to add #include<DockImpl.cpp> to the
  stdafx.cpp.
* Now default constructor of the CDockWndMgrEx required HWND of the Window
  which host the Docking windows.

Major changes in 0.8.8 release:

* The size of the DFDOCKPOS structure has changed so please remove registry
entry of your existing applications if you decide to upgrade to the current
version.
* The classes CStateKeeper and CTitleExDockingWindowImpl are obsolete.
They are currently kept for backward compatibility, You will not need to
use these classes because the CTitleDockingWindowImpl class provide their
functionality.
* Added tabbed docking window support. Take a look at SDITabbedSample,
The tabs depend on CoolTabCtrls.h and DotNetTabCtrl.h written by
Bjarke Viksoe, Daniel Bowen and Pascal Binggeli.
Please take a look at The Codeproject article "Custom Tab Controls,
Tabbed Frame and Tabbed MDI" by Daniel Bowen (dbowen@es.com)
http://www.codeproject.com/wtl/TabbingFramework.asp for description of these
files and their classes.

A lot of thanks to Daniel Bowen who help me much with tabbed stuff.
Numerous people (Hydra,Igor Artemov,Robert Edward Caldecott,Maxim Litvinov,
Leonid Chernov,I've missed many, apologies) have sent me great
feedback and have helped me catch and fix bugs. I really appreciate
the bug reports, all suggestions and feedback I have received.
Thanks to all of you!

Please submit bug reports and comments to kidd@ukr.net.

You can download latest working snapshot of the WTL Docking Windows from www.fewbits.com
