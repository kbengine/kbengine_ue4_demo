 KBEngine_ue4_demo(UE4.22.3)
=============

## 本项目作为KBEngine服务端引擎的客户端演示而写

http://www.kbengine.org

## 官方论坛

	http://bbs.kbengine.org


## QQ交流群

	461368412


## Releases

	sources		: https://github.com/kbengine/kbengine_ue4_demo/releases/latest


## 客户端插件文档

	kbengine_ue4_demo\Plugins\kbengine_ue4_plugins\README.md


## 开始:

	1. 确保已经下载过KBEngine服务端引擎，如果没有下载请先下载
		下载服务端源码(KBEngine)：
			https://github.com/kbengine/kbengine/releases/latest

		编译(KBEngine)：
			http://kbengine.github.io/docs/build.html

		安装(KBEngine)：
			http://kbengine.github.io/docs/installation.html

	2. 下载服务端Demo资产库:

	    * 使用git命令行，进入到kbengine_ue4_demo目录执行：

	        git submodule update --init --remote
![submodule_update1](http://kbengine.github.io/assets/img/screenshots/gitbash_submodule.png)

		* 或者使用 TortoiseGit(选择菜单): TortoiseGit -> Submodule Update:
![submodule_update2](http://kbengine.github.io/assets/img/screenshots/unity3d_plugins_submodule_update.jpg)

                * 也可以手动下载kbengine服务端Demo资产库

		        服务端资产库下载：
		            https://github.com/kbengine/kbengine_demos_assets/releases/latest
		            下载后请将其解压缩,并将目录文件放置于服务端引擎根目录"kbengine/"之下，如下图：

	3. 拷贝服务端资产库"kbengine_demos_assets"到服务端引擎根目录"kbengine/"之下，如下图：
![demo_configure](http://kbengine.github.io/assets/img/screenshots/demo_copy_kbengine.jpg)


	4. 通过服务端资产库生成KBE客户端插件（可选，默认已经带有一份，除非服务器有相关改动才需要再次生成）
		1: 双击运行 kbengine/kbengine_demos_asset/gensdk.bat
		2: 拷贝kbengine_ue4_plugins到kbengine_ue4_demo\Plugins\


## 配置Demo(可选):

	改变登录IP地址与端口（注意：关于服务端端口部分参看http://kbengine.github.io/cn/docs/installation.html）:
![demo_configure](http://kbengine.github.io/assets/img/screenshots/demo_configure_ue4.jpg)

		kbengine_ue4_demo\Content\ClientApp-> ip
		kbengine_ue4_demo\Content\ClientApp-> port


## 启动服务器:

	确保“kbengine_ue4_demo\kbengine_demos_assets”已经拷贝到KBEngine根目录：
		参考上方章节：开始

	使用启动脚本启动服务端：
		Windows:
			kbengine\kbengine_demos_assets\start_server.bat

		Linux:
			kbengine\kbengine_demos_assets\start_server.sh

	检查启动状态：
			如果启动成功将会在日志中找到"Components::process(): Found all the components!"。
			任何其他情况请在日志中搜索"ERROR"关键字，根据错误描述尝试解决。
			(更多参考: http://kbengine.github.io/docs/startup_shutdown.html)


## 启动客户端:

	直接在ue4编辑器启动或者编译后启动


## 生成导航网格(可选):
	
	服务端使用Recastnavigation在3D世界寻路，recastnavigation生成的导航网格（Navmeshs）放置于：
		kbengine\kbengine_demos_assets\res\spaces\*

	在ue4中使用插件生成导航网格（Navmeshs）:
		待续

	工具：
		https://github.com/darkwere/ServerRecast


## 结构与释义：

	KBE插件与UE4和服务器之间的关系：
		插件与服务器：负责处理与服务端之间的网络消息包、账号登陆/登出流程、由服务端通知创建和销毁逻辑实体、维护同步的逻辑实体属性数据等等。
		插件与UE4：插件将某些事件触发给UE4图形层，图形层决定是否需要捕获某些事件获得数据进行渲染表现（例如：创建怪物、某个NPC的移动速度增加、HP变化）、
			UE4图形层将输入事件触发到插件层（例如：玩家移动了、点击了复活按钮UI），插件逻辑脚本层决定是否需要中转到服务器等等。

	clientapp：
		在KBE的体系中抽象出一个客户端APP，其中包含KBE客户端插件的初始化和销毁等等。

	Plugins\KBEnginePlugins\Source\KBEnginePlugins\Engine：
		KBE客户端插件的核心层代码。

	Plugins\KBEnginePlugins\Source\KBEnginePlugins\Scripts：
		KBE客户端的逻辑脚本（在此实现对应服务端的实体脚本、实体的背包数据结构、技能客户端判断等）。

		Scripts\Account：
			对应KBE服务端的账号实体的客户端部分。

		Scripts\Avatar：
			对应KBE服务端的账游戏中玩家实体的客户端部分。

		Scripts\Monster：
			对应KBE服务端的怪物实体的客户端部分。

		Scripts\interfaces\：
			对应KBE中entity_defs\interfaces中所声明的模块。

	Source\kbengine_ue4_demo：
		ue4图形层（包括场景渲染、UI、物体部件、人物模型、怪物模型、一切关于显示的东西等等）。

		kbengine_ue4_demo\PlayerCharacter：
			当前客户端玩家由此脚本负责模型动画等表现部分。

		kbengine_ue4_demo\GameEntity：
			无论是怪物还是其他玩家都由此脚本负责模型动画等表现部分。

		kbengine_ue4_demo\GameModeLogin:
			管理登陆场景，监听KBE插件相关事件同时向插件触发一些事件。

		kbengine_ue4_demo\GameModeSelectAvatar:
			管理角色选人场景，监听KBE插件相关事件同时向插件触发一些事件。

		kbengine_ue4_demo\GameModeWorld:
			监听KBE插件相关事件同时向插件触发一些事件，管理游戏中大地图或副本的渲染层脚本，例如：负责将具体的3D怪物创建到场景中。

	Content\LoginScene:
		起始场景，由此启动进入游戏。

	Content\SelectAvatarScene
		角色选取场景。

	Content\WorldScene
		游戏中大地图/副本场景。

## 演示截图:

![screenshots1](http://kbengine.github.io/assets/img/screenshots/ue4_demo1.jpg)
![screenshots2](http://kbengine.github.io/assets/img/screenshots/ue4_demo2.jpg)
![screenshots3](http://kbengine.github.io/assets/img/screenshots/ue4_demo3.jpg)
