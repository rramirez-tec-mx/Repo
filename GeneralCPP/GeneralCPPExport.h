#ifdef GENERALCPP_EXPORTS
#define GENERALCPP_EXPORTS_API __declspec(dllexport)
#else
#define GENERALCPP_EXPORTS_API __declspec(dllimport)
#endif