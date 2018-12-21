#ifndef SERRATEDBLADES_H
#define SERRATEDBLADES_H

#include "Talent.h"

class TalentTree;

class SerratedBlades: public Talent {
public:
    SerratedBlades(Character *pchar, TalentTree* tree);

private:
    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // SERRATEDBLADES_H
