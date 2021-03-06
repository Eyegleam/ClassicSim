#pragma once

#include "ItemModificationRequirer.h"
#include "SetBonusRequirer.h"
#include "Spell.h"
#include "TalentRequirer.h"

class Hunter;
class StatisticsResource;

class MultiShot: public Spell, public TalentRequirer, public SetBonusRequirer, public ItemModificationRequirer {
public:
    MultiShot(Hunter *pchar, CooldownControl* cooldown_control);

private:
    Hunter* hunter;
    StatisticsResource* statistics_resource {nullptr};
    double resource_base;
    unsigned adrenaline_rush {0};
    double giantstalker_bonus {1.0};
    double mortal_shots_bonus {0.0};
    double barrage_mod {1.0};
    double pvp_gloves_bonus {1.0};
    const QVector<double> efficiency_ranks;
    const QVector<double> mortal_shots_ranks;
    const QVector<double> barrage_ranks;

    void spell_effect() override;
    void prepare_set_of_combat_iterations_spell_specific() override;

    void add_adrenaline_rush_statistics();

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
    void activate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
    void deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
    void activate_item_effect(const int item_id) override;
    void deactivate_item_effect(const int item_id) override;
};
