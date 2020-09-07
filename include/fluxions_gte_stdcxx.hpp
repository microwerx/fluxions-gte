#ifndef FLUXIONS_STDCXX_HPP
#define FLUXIONS_STDCXX_HPP

// C++ Libraries

#include <ostream>
#include <istream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <set>
#include <functional>
#include <regex>
#include <random>
#include <future>
#include <cctype>
#include <cfloat>

// C Libraries

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h> // for free()

#ifdef __unix__
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <libgen.h> // for dirname() and basename()
#include <unistd.h>
#endif

#endif
