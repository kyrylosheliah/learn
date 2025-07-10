#include "pch.h"
#include <utility>
#include <limits.h>
#include "MYFUNLibrary.h"

double MYFUN(const double X)
{
	return sin(1 + exp(-X)) / pow(1 / (pow(X, 2) - 2 * X), 3);
}