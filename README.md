KBEngine_ue4_demo
=============

##This client-project is written for KBEngine(a MMOG engine of server)
http://www.kbengine.org

##中文
[Demo搭建文档](https://github.com/kbengine/kbengine_ue4_demo/blob/master/README_CN.md)，QQ交流群：461368412，[论坛](http://bbs.kbengine.org)

##Releases

	sources		: https://github.com/kbengine/kbengine_ue4_demo/releases/latest
	binarys		: https://sourceforge.net/projects/kbengine/files/


##KBE-Plugins docs

	https://github.com/kbengine/kbengine_ue4_plugins/blob/master/README.md


##Start:
	1. Download KBEngine(a MMOG engine of server):
		Download(KBEngine):
			https://github.com/kbengine/kbengine/releases/latest

		Build(KBEngine):
			http://www.kbengine.org/docs/build.html

		Installation(KBEngine):
			http://www.kbengine.org/docs/installation.html

	2. Use git to get the plugin(client) and demo-assets(server):

		In the kbengine_ue4_demo directory:

		* Git command: git submodule update --init --remote
![submodule_update1](http://www.kbengine.org/assets/img/screenshots/gitbash_submodule.png)

		* Or use TortoiseGit(menu): TortoiseGit -> Submodule Update:
![submodule_update2](http://www.kbengine.org/assets/img/screenshots/unity3d_plugins_submodule_update.jpg)

		* Or manually get the plugin(client) and demo-assets(server)

			Download plugin(client):
				https://github.com/kbengine/kbengine_ue4_plugins/releases/latest
				unzip and copy to "Assets/plugins/kbengine/kbengine_ue4_plugins"

			Download demo-assets(server):
				https://github.com/kbengine/kbengine_demos_assets/releases/latest
				unzip and copy to "kbengine/"  (The root directory server engine, such as $KBE_ROOT)

	3. Copy "kbengine_ue4_demo\kbengine_demos_assets" to "kbengine\" root directory
![demo_configure](http://www.kbengine.org/assets/img/screenshots/demo_copy_kbengine.jpg)


##Configure Demo(Optional):

	Change the login address:
![demo_configure](http://www.kbengine.org/assets/img/screenshots/demo_configure.jpg)

		kbengine_ue4_demo\Content\ClientApp-> ip
		kbengine_ue4_demo\Content\ClientApp-> port


##Start the Servers:

	Ensure that the "kbengine_ue4_demo\kbengine_demos_assets" has been copied to the "kbengine\" directory
		Reference：Start

	Check the startup status:
		If successful will find log "Components::process(): Found all the components!".
		Otherwise, please search the "ERROR" keyword in logs, according to the error description to try to solve.
		(More: http://www.kbengine.org/docs/startup_shutdown.html)

	Start server:
		Windows:
			kbengine\kbengine_demos_assets\start_server.bat

		Linux:
			kbengine\kbengine_demos_assets\start_server.sh

		(More: http://www.kbengine.org/docs/startup_shutdown.html)


##Start the Client:

	Directly start(U3DEditor or Executable file).
	(Build Client：Unity Editor -> File -> Build Settings -> PC, MAC & Linux Standalone.)


##Navmesh-navigation(Optional):
	
	The server to use recastnavigation navigation.
	Recastnavigation generated navigation mesh (Navmeshs) placed on the:
		kbengine\kbengine_demos_assets\res\spaces\*

	Generation Navmeshs:
		...


##Structure and interpretation:
			
	The relationship between plug-ins(KBE) and U3D and servers:
		Plug-in and servers: Responsible for processing and server network packet. account login/logout process. 
				     By server notification logic entities are created and destroyed. Processing synchronous logical entity attribute data. etc.
		Plug-in and U3D: The plug-in will trigger some events to the U3D graphics layer, the graphics layer determines whether to capture some events, 
				get data to render performance (for example: create a monster, a NPC move-speed increase, HP changes).
				U3D graphics layer will input the event trigger to the plug-in layer (for example: the player moved, hit the relive button UI), 
				the plug-in logic script layer determines whether the need to transfer to the server. etc.
				
	clientapp：
		In the system of KBE abstraction of a client APP, which contains the KBE client plug-in initialization and destruction, etc.

	Plugins\KBEnginePlugins
		Client plug-in core codes.

	Source\kbe_scripts:
		KBE client logic scripts(in this implementation of the server side of the entity script, the entity's bag data structure, skills in client condition checks, etc.).

		kbe_scripts\Account：
			Corresponds to the client side of the KBE server account entity.

		kbe_scripts\Avatar：
			Corresponds to the client side of the KBE server avatar entity.

		kbe_scripts\Monster：
			Corresponds to the client side of the KBE server monster entity.

		kbe_scripts\interfaces\：
			Corresponding to the module defined in KBE(entity_defs\interfaces).

	Source\ue4_scripts:
		ue4_scripts\PlayerCharacter：
			Current client player, the script processing model and animation and other parts.

		ue4_scripts\GameEntity：
			Whether the monster or other players, by the script responsible for the model and animation and other parts.

		ue4_scripts\GameModeLogin:
			Manage landing scenes, listen for events related to the KBE plug-in, and trigger events to the plug-in.

		ue4_scripts\GameModeSelectAvatar:
			Manage role selection scenarios, listen for events related to the KBE plug-in, and trigger events on the plug-in.

		ue4_scripts\GameModeWorld:
			Listen to events related to the KBE plug-in, trigger events to the plug-in, and manage scripts for in-game maps, such as creating a specific 3D monster in the scene.

	Content\LoginScene:
		Start the scene, which starts to enter the game.

	Content\SelectAvatarScene
		Game character selection map.

	Content\WorldScene
		A map of the scene in the game.

##Screenshots:
![screenshots1](http://www.kbengine.org/assets/img/screenshots/unity3d_demo9.jpg)
![screenshots2](http://www.kbengine.org/assets/img/screenshots/unity3d_demo10.jpg)
![screenshots3](http://www.kbengine.org/assets/img/screenshots/unity3d_demo11.jpg)
