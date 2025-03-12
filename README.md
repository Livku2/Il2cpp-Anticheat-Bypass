### How to use
You have to decompile the apk

then go to the libs/arm64-8va folder and add this file

then go to smali/com/unity3d/player and open UnityPlayerActivity.smali

then go to OnCreate and add this

```java
const-string v0, "AntiCheatBypass"

invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V
```


![image](https://github.com/user-attachments/assets/cecc47d5-5905-4da5-aad4-1a4b285bb363)

