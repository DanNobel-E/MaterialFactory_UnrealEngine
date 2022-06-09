## MaterialFactory_UnrealEngine

UE 4.27 material factory plugin. 
Insert command "makematerial" to UE command line plus one of the following keywords:
```
makematerial random
makematerial from + file path
```
> *makematerial random* creates a random material selecting one of the implemented material graph patterns.

# Current implemented patterns are:

* **Base**: material with **base color** parameter.
![GeoFactory - Unreal Editor 10_05_2022 11_13_05](https://user-images.githubusercontent.com/60443583/172908850-2a459890-f239-46fd-8500-e8bc54220020.png)
* **Texture**: material with a selected **texture** (or default) **parameter**, multiplied by **base color**.
![GeoFactory - Unreal Editor 10_05_2022 11_13_22](https://user-images.githubusercontent.com/60443583/172909013-d91fa4ad-194a-4adb-96dc-ca6bd45a4f6b.png)
* **TextureModified**: material with **texture**, **base color** and **offset/scale texture modifiers**.
![GeoFactory - Unreal Editor 10_05_2022 11_13_53](https://user-images.githubusercontent.com/60443583/172909133-9fe36a37-202b-4e63-82ae-5311701df571.png)
* **Animated**: material with **texture animated offsets**.

https://user-images.githubusercontent.com/60443583/172913141-8e1f5366-98c1-4d9f-b859-bd9c6c176d6c.mov

* **Glow**: material with **emissive** editable parameters, such as Glow **Color**, **Power** and **Speed**.

https://user-images.githubusercontent.com/60443583/172913163-8a376e47-fd02-418f-984b-da0550aeefa1.mov

* **Pulse**: material with **Pixel Offsets dynamic modification** making the mesh pulsing at **Speed Parameter** rate.

https://user-images.githubusercontent.com/60443583/172913154-cc7ece5b-8236-4f68-ac9d-01b1a5fe69cd.mov


**Patterns are independets and can be composed as you like.**

> *makematerial from + file path* takes a path to a .txt to create a material with the referenced features.

![Screenshot 10_05_2022 11_20_09](https://user-images.githubusercontent.com/60443583/172909976-7ce05fe8-9fc4-4be8-bc1a-3678ed588492.png)

**You can access material .txt templates on the MaterialTemplates directory.**



















