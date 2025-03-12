#include <jni.h>
#include <string>
#include <thread>
#include <cstdint>
#include <vector>
#include "Engine/Includes.hpp"


ProcMap map;

void (*Quit1)(void *) = nullptr;
void new_Quit1(void* self) {
    LOGI("Bypass Quit 1");
}

void (*Quit2)(void *, int *) = nullptr;
void new_Quit2(void* self, int* exitCode) {
    LOGI("Bypass Quit 2");
}
void (*Destroy1)(void *, void* object, float* t) = nullptr;
void new_Destroy1(void* self, void* object, float* t) {
    LOGI("Bypass Destroy 1");
}
void (*Destroy2)(void *, void *) = nullptr;
void new_Destroy2(void* self, void* object) {
    LOGI("Bypass Destroy 2");
}

bool (*FileExists)(void *, void *) = nullptr;
bool new_FileExists(void* self, void* stringV) {
    LOGI("Bypass File.Exists");
    return false;
}

bool (*DirectoryExists)(void *, void *) = nullptr;
bool new_DirectoryExists(void* self, void* path) {
    LOGI("Bypass Directory.Exists");
    return false;
}

bool (*isEditor)(void *) = nullptr;
bool new_isEditor(void* self) {
    LOGI("Bypass isEditor");
    return true;
}

bool (*get_IsCheatDetected)(void *) = nullptr;
bool new_get_IsCheatDetected(void* self) {
    LOGI("Bypass get_IsCheatDetected");
    return false;
}

void (*OnCheatingDetected)(void *) = nullptr;
void new_OnCheatingDetected(void* self) {
    LOGI("Bypass OnCheatingDetected");
}
void (*LoadScene1)(void *, int*) = nullptr;
void new_LoadScene1(void* self, int* sceneBuildIndex) {
    LOGI("LoadScene Called: %p", sceneBuildIndex);
    LoadScene1(self, sceneBuildIndex);
}

void (*LoadScene2)(void *, int*, void*) = nullptr;
void new_LoadScene2(void* self, int* sceneBuildIndex, void* parameters) {
    LOGI("LoadScene2 Called: %p, Params: %p", sceneBuildIndex, parameters);
    LoadScene2(self, sceneBuildIndex, parameters);
}

void (*SetActive)(void *, bool*) = nullptr;
void new_SetActive(void* self, bool*) {
    LOGI("Bypass SetActive");
}

bool (*Equals1)(void *, int*) = nullptr;
bool new_Equals1(void* self, int* obj) {
    return true;
}

void (*LoadScene)(int sceneBuildIndex);

__attribute__ ((constructor))
void lib_main() {
    std::thread([]() {
        do {
            map = KittyMemory::getElfBaseMap("libil2cpp.so");
            sleep(1);
        } while (!map.isValid() && !map.isValidELF());

        if (Il2Cpp::Init("libil2cpp.so") == -1) {
            LOGE("Il2Cpp::Init Failed!");
            return;
        }
        setPointer(Quit1, "UnityEngine.CoreModule.dll", "UnityEngine", "Application", "Quit", 0);
        setPointer(Quit2, "UnityEngine.CoreModule.dll", "UnityEngine", "Application", "Quit", 1);
        setPointer(SetActive, "UnityEngine.CoreModule.dll", "UnityEngine", "GameObject", "SetActive", 1);
        setPointer(DirectoryExists, "mscorlib.dll", "System.IO", "Directory", "Exists", 1);
        setPointer(FileExists, "mscorlib.dll", "System.IO", "File", "Exists", 1);
        setPointer(Destroy1, "UnityEngine.CoreModule.dll", "UnityEngine", "Object", "Destroy", 2);
        setPointer(Destroy2, "UnityEngine.CoreModule.dll", "UnityEngine", "Object", "Destroy", 1);
        setPointer(isEditor, "UnityEngine.CoreModule.dll", "UnityEngine", "Application", "get_isEditor", 0);
        setPointer(LoadScene1, "UnityEngine.CoreModule.dll", "UnityEngine.SceneManagement", "SceneManager", "LoadScene", 1);
        setPointer(LoadScene2, "UnityEngine.CoreModule.dll", "UnityEngine.SceneManagement", "SceneManager", "LoadScene", 2);
        //setPointer(get_IsCheatDetected, "ACTk.Runtime.dll", "CodeStage.AntiCheat.Detectors", "ACTkDetectorBase`1", "get_IsCheatDetected", 0);
        //setPointer(OnCheatingDetected, "ACTk.Runtime.dll", "CodeStage.AntiCheat.Detectors", "ACTkDetectorBase`1", "OnCheatingDetected", 0);
        //setPointer(Equals1, "mscorlib.dll", "System", "Int32", "Equals", 1);

        //LoadScene = (void (*)(int))(reinterpret_cast<uint8_t*>(map.startAddress) + 0x4D3FA28);

        //setHook(Equals1, "Equals1");
        setHook(SetActive, "SetActive");
        setHook(DirectoryExists, "DirectoryExists");
        setHook(FileExists, "FileExists");
        setHook(Quit1, "Quit1");
        setHook(Quit2, "Quit2");
        setHook(Destroy1, "Destroy1");
        setHook(Destroy2, "Destroy2");
        setHook(isEditor, "isEditor");
        setHook(LoadScene1,"LoadScene1");
        setHook(LoadScene2,"LoadScene2");
        //setHook(get_IsCheatDetected,"get_IsCheatDetected");
        //setHook(OnCheatingDetected,"OnCheatingDetected");

        //sleep(5);

        //LoadScene(1);

    }).detach();
}
