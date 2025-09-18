#ifdef DEBUG
#define DBG(...) log_info(__VA_ARGS__)
#else
#define DBG(...) ((void)0)
#endif