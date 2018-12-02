#include "SinisterStrike.h"
#include "CharacterStats.h"
#include "Rogue.h"
#include "Equipment.h"
#include "Weapon.h"

SinisterStrike::SinisterStrike(Character* pchar) :
    Spell("Sinister Strike", "Assets/spell/Spell_shadow_ritualofsacrifice.png", pchar, RestrictedByGcd::Yes, 0.0, ResourceType::Energy, 45),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Improved Sinister Strike", 2, DisabledAtZero::No)}),
    rogue(dynamic_cast<Rogue*>(pchar)),
    aggression_modifier(1.0)
{
    imp_ss_ranks = {45, 42, 40};
    aggression_ranks = {1.0, 1.02, 1.04, 1.06};
}

void SinisterStrike::spell_effect() {
    rogue->exit_stealth();

    const int result = roll->get_melee_ability_result(rogue->get_mh_wpn_skill(), pchar->get_stats()->get_mh_crit_chance());

    add_gcd_event();

    if (result == AttackResult::MISS) {
        increment_miss();
        rogue->lose_energy(static_cast<unsigned>(resource_cost));
        return;
    }
    if (result == AttackResult::DODGE) {
        increment_dodge();
        rogue->lose_energy(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }
    if (result == AttackResult::PARRY) {
        increment_parry();
        rogue->lose_energy(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }

    double base_dmg = rogue->get_random_normalized_mh_dmg() + 68.0;
    double damage_dealt = damage_after_modifiers(base_dmg * aggression_modifier);

    if (result == AttackResult::CRITICAL) {
        damage_dealt = round(damage_dealt * rogue->get_ability_crit_dmg_mod());
        rogue->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());
    }
    else if (result == AttackResult::HIT) {
        rogue->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());
    }

    rogue->lose_energy(static_cast<unsigned>(resource_cost));
    rogue->gain_combo_points(1);
}

void SinisterStrike::increase_talent_rank_effect(const int curr, const QString& talent_name) {
    if (talent_name == "Improved Sinister Strike")
        resource_cost = imp_ss_ranks[curr];
    else if (talent_name == "Aggression")
        aggression_modifier = aggression_ranks[curr];
}

void SinisterStrike::decrease_talent_rank_effect(const int curr, const QString& talent_name) {
    if (talent_name == "Improved Sinister Strike")
        resource_cost = imp_ss_ranks[curr];
    else if (talent_name == "Aggression")
        aggression_modifier = aggression_ranks[curr];
}