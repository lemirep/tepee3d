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
            component.addOperation("CreateShortcut", "@TargetDir@/Tepee3DEngine.bat","@StartMenuDir@/Tepee3D.lnk", "workingDirectory=@TargetDir@", "IconLocation=@TargetDir@/qml/Resources/Pictures/tepee3d_icon.ico");
            component.addOperation("CreateShortcut", "@TargetDir@/Tepee3DEngine.bat","@DesktopDir@/Tepee3D.lnk", "workingDirectory=@TargetDir@", "IconLocation=@TargetDir@/qml/Resources/Pictures/tepee3d_icon.ico");
	 }
	 if (installer.value("os") ==  "x11") {
            component.addOperation("CreateDesktopEntry", "Tepee3D.desktop", "Type=Application Name=Tepee3D GeneralName=Tepee3D Exec=@TargetDir@/Tepee3DEngine.sh Terminal=true Icon=@TargetDir@/qml/Resources/Pictures/tepee3d_icon.png");
	    component.addOperation("Execute", "chmod", "u+x","@TargetDir@/Tepee3DEngine.sh", "UNDOEXECUTE", "chmod", "u-x", "@TargetDir@/Tepee3DEngine.sh");
	 }
     } catch (e) {
         print(e);
     }
 }
