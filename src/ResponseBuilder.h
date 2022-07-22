//
// Created by javier on 22/07/22.
//

#ifndef TEST_RESPONSEBUILDER_H
#define TEST_RESPONSEBUILDER_H


#include <map>
#include <WString.h>

class ResponseBuilder {
public:
    static String buildJSONResponse(const std::map<String, int>& fields);
};


#endif //TEST_RESPONSEBUILDER_H
