#include "creature.h"

creatureData::creatureData()
{
    m_speedMove = 1;
    m_speedAttack = 1;
}
creatureData::~creatureData()
{

}
//////////////////////////////////////////////////////////////////////////
creatureSprite::creatureSprite()
{
    m_pData = new creatureData;
}
creatureSprite::~creatureSprite()
{
    if(m_pData)
    {
        delete m_pData;
        m_pData = NULL;
    }
}