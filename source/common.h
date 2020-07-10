/* Author: Kevin Farley
*
* Name: COMMON.H
* Description: definitions and constants for use throughout app
*  Used by main Game class and Player class for now
*
*/
#pragma once

#include <string>

// resource definition should be passed from cmake
//  if not, assume repo root is parent directory...
#ifndef RESOURCES
#if _MSC_VER > 0
#define RESOURCES "..\\resources\\"
#else
#define RESOURCES "../resources/"
#endif
#endif

// TODO: make game namespace?

const std::string RESOURCE_PATH(RESOURCES);
