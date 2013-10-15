 function Component()
 {
     // constructor
 }

 Component.prototype.isDefault = function()
 {
     // select the component by default
     return true;
 }

 Component.prototype.createOperations = function()
 {
     try {
         // call the base create operations function
         component.createOperations();
	 if (installer.value("os") == "win") {
            component.addOperation("CreateShortcut", "@TargetDir@/Tepee3DEngine.bat","@StartMenuDir@/Tepee3D.lnk", "workingDirectory=@TargetDir@");
            component.addOperation("CreateShortcut", "@TargetDir@/Tepee3DEngine.bat","@DesktopDir@/Tepee3D.lnk", "workingDirectory=@TargetDir@");
	 }
	 if (installer.value("os") ==  "x11") {
            component.addOperation("CreateDesktopEntry", "Tepee3D.desktop", "Type=Application Name=Tepee3D Exec=@TargetDir@/Tepee3DEngine.sh Terminal=true");
	    component.addOperation("Execute", "chmod", "u+x","@TargetDir@/Tepee3DEngine.sh", "UNDOEXECUTE", "chmod", "u-x", "@TargetDir@/Tepee3DEngine.sh");
	 }
     } catch (e) {
         print(e);
     }
 }
