#ifdef CNG_EXPORTS
#define CNG_EXPORTS_API __declspec(dllexport)
#else
#define CNG_EXPORTS_API __declspec(dllimport)
#endif

