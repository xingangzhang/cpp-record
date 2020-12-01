#ifndef TEST_LIB

#define TEST_LIB

/**
 * extern "C" 使用C函数命名规则
 *  __declspec(dllexport) 导出函数
 */
extern "C" __declspec(dllexport)  int test_add(int a, int b);

#endif