#ifdef LOG_EXPORTS
#define LOG_EXPORTS_API __declspec(dllexport)
#else
#define LOG_EXPORTS_API __declspec(dllimport)
#endif
