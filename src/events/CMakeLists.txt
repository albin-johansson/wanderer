cmake_minimum_required(VERSION 3.15)

project(wanderer-events CXX)

set(WANDERER_EVENT_SOURCES

    ${PROJECT_SOURCE_DIR}/begin_attack_event.hpp
    ${PROJECT_SOURCE_DIR}/begin_humanoid_move_event.hpp
    ${PROJECT_SOURCE_DIR}/button_pressed_event.hpp
    ${PROJECT_SOURCE_DIR}/close_inventory_event.hpp
    ${PROJECT_SOURCE_DIR}/custom_animation_halfway_event.hpp
    ${PROJECT_SOURCE_DIR}/day_changed_event.hpp
    ${PROJECT_SOURCE_DIR}/end_attack_event.hpp
    ${PROJECT_SOURCE_DIR}/end_humanoid_move_event.hpp
    ${PROJECT_SOURCE_DIR}/fullscreen_toggled_event.hpp
    ${PROJECT_SOURCE_DIR}/integer_scaling_toggled_event.hpp
    ${PROJECT_SOURCE_DIR}/interact_event.hpp
    ${PROJECT_SOURCE_DIR}/level_fade_events_event.hpp
    ${PROJECT_SOURCE_DIR}/load_game_event.hpp
    ${PROJECT_SOURCE_DIR}/menu_switched_event.hpp
    ${PROJECT_SOURCE_DIR}/quit_event.hpp
    ${PROJECT_SOURCE_DIR}/show_inventory_event.hpp
    ${PROJECT_SOURCE_DIR}/sleep_event.hpp
    ${PROJECT_SOURCE_DIR}/spawn_particles_event.hpp
    ${PROJECT_SOURCE_DIR}/switch_map_event.hpp
    ${PROJECT_SOURCE_DIR}/switch_menu_event.hpp

    PARENT_SCOPE)