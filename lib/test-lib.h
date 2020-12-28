#ifndef TEST_LIB

#define TEST_LIB

/**
 * extern "C" 使用C函数命名规则
 *  __declspec(dllexport) 导出函数
 * Linux不需要声明导出函数
 *
 * Windows编译为DLL 编译test-lib-shared
 * Linux编译为SO g++ test-lib.cpp -fPIC -shared -o liblibtest-lib-shared.so
 */
#ifdef Win32
extern "C" __declspec(dllexport) int test_add(int a, int b);
#else
extern "C" int test_add(int a, int b);
#endif

#endif