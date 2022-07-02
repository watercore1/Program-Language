#include "build.h"

int Build::city_num_ = 0;

Build::Build(int initial_elements) : elements_(initial_elements) {}

Build::~Build() {}

void Build::InitialCityNum(int city_num) { city_num_ = city_num; }

int Build::GetElements() { return elements_; }