/**
 *
 */
#include "cEntityManager.hpp"

cEntityManager::cEntityManager()
{
    m_entities.reserve(400);
    mn_collisions = 0;
    has_played = false;
}

cEntityManager::~cEntityManager()
{
    // There's better way to clear it... but this will do?
    for (unsigned int i=0; i<m_entities.size(); ++i) {
        m_entities[i].reset();
        m_entities.erase(m_entities.begin()+i);
    }
}
