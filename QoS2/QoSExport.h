#ifdef QOS2_EXPORTS
#define QOS2_EXPORTS_API __declspec(dllexport)
#else
#define QOS2_EXPORTS_API __declspec(dllimport)
#endif