### Il2cpp-AntiCheat-Bypass

Includes bypass for lemonloader check

# WILL NOT PREVENT BANS

### How to use

Download the library from https://github.com/Livku2/Il2cpp-Anticheat-Bypass/releases/download/V1.1/libAntiCheatBypass.so

You have to decompile the apk

then go to the libs/arm64-8va folder and add the anti-cheat bypass

then go to smali/com/unity3d/player and open UnityPlayerActivity.smali

then go to OnCreate and add this

```java
const-string v0, "AntiCheatBypass"

invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V
```


![image](https://github.com/user-attachments/assets/cecc47d5-5905-4da5-aad4-1a4b285bb363)

