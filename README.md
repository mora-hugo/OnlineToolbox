# OnlineToolbox
A online toolbox which support Beacons, Sessions, achievements, Statistics, Friends, Presence and Identity (Work with Steam and EOS)

There is an exemple of DefaultEngine.ini to support this plugins with steam using SteamNetDriver and Spacewar
```
[/Script/Engine.Engine]
!NetDriverDefinitions=ClearArray
+NetDriverDefinitions=(DefName="GameNetDriver",DriverClassName="/Script/OnlineSubsystemSteam.SteamNetDriver",DriverClassNameFallback="/Script/OnlineSubsystemUtils.IpNetDriver")
+NetDriverDefinitions=(DefName="DemoNetDriver",DriverClassName="/Script/Engine.DemoNetDriver",DriverClassNameFallback="/Script/Engine.DemoNetDriver")
+NetDriverDefinitions=(DefName="BeaconNetDriver",DriverClassName="/Script/OnlineSubsystemSteam.SteamNetDriver",DriverClassNameFallback="/Script/OnlineSubsystemUtils.IpNetDriver")

[/Script/OnlineSubsystemUtils.OnlineBeaconHost]
ListenPort=7787
BeaconConnectionInitialTimeout=48.0
BeaconConnectionTimeout=49.0

[OnlineSubsystem]
DefaultPlatformService=Steam

[OnlineSubsystemSteam]
bEnabled=true
SteamDevAppId=480
GameServerQueryPort=27015

[/Script/OnlineSubsystemSteam.SteamNetDriver]
NetConnectionClassName="OnlineSubsystemSteam.SteamNetConnection"
```
Lobby example
![Capture d'écran 2023-11-27 230324](https://github.com/mora-hugo/OnlineToolbox/assets/100521440/f8dc6246-f007-498e-8780-c9309054cb84)

Ingame profile
![Capture d'écran 2023-11-27 230344](https://github.com/mora-hugo/OnlineToolbox/assets/100521440/a413052a-381e-41cf-b58a-e4864b009eb5)

Friend list to invite into our party
![Capture d'écran 2023-11-27 230420](https://github.com/mora-hugo/OnlineToolbox/assets/100521440/f6573608-0bde-47a3-ab83-7b910cd84876)




