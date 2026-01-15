## Character Builder (Logic-Only RPG System)

A logic-only RPG Character Builder written in C++, designed as a portfolio project to demonstrate gameplay systems design, clean data structures, and user-driven flow without engine or UI dependencies.

This project focuses on clarity, extensibility, and correctness, making it suitable as a foundation for future engine integration (e.g. Unreal Engine, Unity, or custom tools).

# Project Overview

The Character Builder allows a player to:

Create a named character

Choose a Race and Class

Apply class base stats

Apply race attribute modifiers

Allocate a limited pool of attribute points

View the final character sheet via console output

All logic is implemented in a single, self-contained C++ system with no engine-specific dependencies.

## Design Goals

Demonstrate gameplay system logic, not UI

Use clear data-driven structures for races and classes

Follow OOP-style separation of responsibilities

Be easy to expand with:

New races or classes

Different stat systems

Engine-level UI later

## System Architecture
Core Data Types

# Enums

ERace – Defines playable races

EClass – Defines playable classes

# Structs

FAttributes – Holds character stats (STR, DEX, CON, INT, WIS, CHA)

FRaceData – Race + attribute modifiers

FClassData – Class + base attributes

FCharacter – Final assembled character data

Main Controller

FCharacterCreator

Orchestrates the full character creation flow

# Handles:

Input validation

Stat calculation

Data application

Output formatting

## Character Creation Flow

Player enters a character name

Player selects a class

Player selects a race

Class base stats are applied

Race modifiers are applied

Character stats are displayed

Player allocates 10 attribute points

Final character sheet is displayed

## Attribute System

# Six core attributes:

Strength

Dexterity

Constitution

Intelligence

Wisdom

Charisma

Attribute points:

Player starts with 10 free points

Each point increases a chosen stat by +1

Input is validated to prevent invalid selections

## Input Validation

All player input uses:

std::cin.fail() checks

Stream clearing with std::cin.clear()

Input buffer flushing using std::cin.ignore()

This ensures the system remains stable even with invalid input.

## Example Use Case

This system can be reused as:

A prototype RPG ruleset

A backend logic layer for Unreal Engine UI

A foundation for:

Save/load systems

Character progression

Multiplayer stat syncing

## Possible Extensions

Separate files (.h / .cpp) for scalability

JSON or data-table driven races/classes

Stat caps and derived attributes

Ability scores influencing skills or combat

Serialization (save/load characters)

Engine integration (UE5 / Blueprint exposure)

## Build & Run

This is a standard C++ console application.

Compile with any modern C++ compiler:

``` bash
g++ CharacterBuilder.cpp -o CharacterBuilder
./CharacterBuilder
```
## Author

Kaden
Gameplay Systems & Game Development Portfolio Project
