#pragma once

#if defined(_WIN32)
# include <io.h>
#else
# include <unistd.h>
#endif

#if defined(_WIN32)
# define F_OK 0
#endif

#if defined(_WIN32)
# define access _access
#endif