#pragma once
#include "CrimeRecord.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

// Function to read a limited number of records from CSV
vector<CrimeRecord> readCSV(const string& filename, int numRecords);
string normalizeString(const string& str);
string normalizeCountyName(const string& county);
string normalizeFinalLevel(const string& level);

