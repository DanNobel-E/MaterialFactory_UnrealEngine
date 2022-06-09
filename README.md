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
* **Texture**: material with a selected **texture** (or default) **parameter**, multiplied by **base color**.
* **TextureModified**: material with **texture**, **base color** and **offset/scale texture modifiers**.
* **Animated**: material with **texture animated offsets**.
* **Glow**: material with **emissive** editable parameters, such as Glow **Color**, **Power** and **Speed**.
* **Pulse**: material with **Pixel Offsets dynamic modification** making the mesh pulsing at **Speed Parameter** rate.

**Patterns are independets and can be composed as you like.**

> *makematerial from + file path* takes a path to a .txt to create a material with the referenced features.

![alt text](https://github.com/[username]/[reponame]/blob/[branch]/image.jpg?raw=true)
