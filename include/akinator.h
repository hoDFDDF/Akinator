#ifndef  _AKINATOR_H_
#define _AKINATOR_H_

#include "tree.h"
#include "TreeRead.h"

const size_t ANSWER_SIZE = 3;

enum AkinatorMode{
    GUESSOBJECT    = 0,
    COMPAREOBJECT  = 1,
    SAVEDATABASE   = 2,
    EXIT           = 3,
    EXITTYPE       = 4,
    UNNOWNMODE     = 5,
    PLAYMODE       = 6,
    ADDINGMODE     = 7
};
#endif //_AKINATOR_H_