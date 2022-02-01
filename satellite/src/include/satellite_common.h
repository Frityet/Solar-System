//
// Created by Frityet on 2022-02-01.
//

#ifndef SOLARSYSTEM_SATELLITE_COMMON_
#define SOLARSYSTEM_SATELLITE_COMMON_

#define ENUMERATE_ADDRINFO(_name, _addrinfo) for (struct addrinfo *(_name) = (_addrinfo); (_name) != NULL; (_name) = (_addrinfo)->ai_next)

#endif //SOLARSYSTEM_SATELLITE_COMMON_
