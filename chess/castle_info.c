#include "_private.h"

typedef enum CI_BIT CI_BIT;

enum CI_BIT
{
    CI_BIT_RA = 1,
    CI_BIT_KING = 2,
    CI_BIT_RH = 4,
};

byte castle_info_default(void)
{
    return 0;
}

bool castle_info_king_moved(byte ci)
{
    return ci & CI_BIT_KING;
}

bool castle_info_rooka_moved(byte ci)
{
    return ci & CI_BIT_RA;
}

bool castle_info_rookh_moved(byte ci)
{
    return ci & CI_BIT_RH;
}

void castle_info_move_king(byte * ci)
{
    * ci |= CI_BIT_KING;
}

void castle_info_move_rooka(byte * ci)
{
    * ci |= CI_BIT_RA;
}

void castle_info_move_rookh(byte * ci)
{
    * ci |= CI_BIT_RH;
}

bool castle_info_can_castle_short(byte ci)
{
    return ! (castle_info_king_moved(ci) || castle_info_rookh_moved(ci));
}

bool castle_info_can_castle_long(byte ci)
{
    return ! (castle_info_king_moved(ci) || castle_info_rooka_moved(ci));
}