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
https://user-images.githubusercontent.com/60443583/172909183-dde7f670-0e24-4f7c-9bd1-38ab46f82655.mp4
* **Glow**: material with **emissive** editable parameters, such as Glow **Color**, **Power** and **Speed**.
https://user-images.githubusercontent.com/60443583/172909468-9149fe3b-7941-475f-b94d-6004749e5c2a.mp4
* **Pulse**: material with **Pixel Offsets dynamic modification** making the mesh pulsing at **Speed Parameter** rate.
https://user-images.githubusercontent.com/60443583/172909512-52603d39-117b-48e9-8a8c-4a4ff70a5ed1.mp4

**Patterns are independets and can be composed as you like.**

> *makematerial from + file path* takes a path to a .txt to create a material with the referenced features.














