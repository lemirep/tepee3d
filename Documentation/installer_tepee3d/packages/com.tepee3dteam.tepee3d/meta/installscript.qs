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
	 if (installer.value("os") === "win") {
            component.addOperation("CreateShortcut", "@TargetDir@/Tepee3DEngine.bat","@StartMenuDir@/Tepee3D.lnk");
            component.addOperation("CreateShortcut", "@TargetDir@/Tepee3DEngine.bat","@DesktopDir@/Tepee3D.lnk");
	 }
	 if (installer.value("os") === "x11") {
            component.addOperation("CreateDesktopEntry", "Tepee3D","Type=1", "Name=Tepee3D", "Exec=@TargetDir@/Tepee3DEngine.sh");
	 }

     } catch (e) {
         print(e);
     }
 }
