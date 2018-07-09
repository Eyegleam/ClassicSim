
#include "Human.h"

int Human::get_race_int() const {
    return Races::Human;
}

QString Human::get_name(void) const {
    return "Human";
}

int Human::get_base_strength(void) const {
    return 20;
}

int Human::get_base_agility(void) const {
    return 20;
}

int Human::get_base_stamina(void) const {
    return 20;
}

int Human::get_base_intellect(void) const {
    return 20;
}

int Human::get_base_spirit(void) const {
    return 20;
}

float Human::get_int_multiplier() const {
    return 1.0;
}

float Human::get_spirit_multiplier() const {
    return 1.05;
}

int Human::get_axe_bonus() const {
    return 0;
}

int Human::get_sword_bonus() const {
    return 5;
}

int Human::get_mace_bonus() const {
    return 5;
}

int Human::get_bow_bonus() const {
    return 0;
}

int Human::get_gun_bonus() const {
    return 0;
}

int Human::get_thrown_bonus() const {
    return 0;
}
