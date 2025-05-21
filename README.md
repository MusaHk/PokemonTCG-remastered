# ⚡PokémonTCG-remastered
A turn-based strategy game where Pokémon have ambiguous abilities, conditional triggers and deceptive move sets, designed so that smart plays can snatch victory from defeat. Players must think not just about what their opponent can do, but what they might be hiding. 

# 🧠 Game Design Core Philosophy
This is **not** a reskinned version of the tradtional TCG, it's a strategic turn-based Pokémon-style battle simulator where **deduction, adaptation, and clever resource use** are the keys to victory.

Inspired by the classic Pokémon format, the game introduces a fresh twist: **comeback mechanics**, **hidden information**, and the ability to turn the tides through offerings to the mythical Arceus. There are no one-sided beatdowns, unless you've a skill issue. As you fall closer to defeat, more paths to victory open up. Every move and ability have purpose, no more plain old damaging moves with a cool name. 

You'll always find yourself being on the edge of your seat until a victor has been decided, or find yourself perhaps tied on a noose, who knows. Just 10-12 Pokemon, yet enough permutations to make the game never feel stale. No advantage comes forth without sacrifice.

---

## 🎮 Game Overview

Each match pits two players against each other, each with a **randomly assigned team of 3 unique Pokémon**. Players have to make their choice between gathering intel via the **Pokédex** and/or offer a sacrifice to **Arceus' Altar**, all while looking for the best move on the board. The match ends when either side runs out of Pokémon.
---

## ⚔️ Core Gameplay Loop

On each turn, a player may:

- **Switch Pokémon** 
- **Use Pokédex Scan** *(once per game)* to reveal an opponent’s Pokémon passive
- **Use Arceus’ Altar** *(if charges available)* to sacrifice something for a powerful buff
- **Attack** with a move from their current Pokémon *(Main action)*

> [!IMPORTANT]
> You only attack once per turn, but you can freely scan, switch, or invoke the altar beforehand, this decision was made to make the games fast-paced, and to allow *devastating* comebacks within a **single** turn.

---

## 🔱 Arceus’ Altar

Players gain **1 Altar charge** each time one of their Pokémon faints. Charges can be spent on powerful effects such as reviving a Pokémon, disabling enemy passives, or empowering your next move. These sacrifices give losing players the chance to deal a *destructive* blow to their opponents, all while the "winning players" *think* they've got the match in the bag.

> [!TIP]
> Take current passives on the field into account when deciding on a sacrifice.

---

## 📦 Features

- **10–12 Unique Pokémon**, each with purpose-built passive abilities and moves that create rich strategic choices.
- **EX Pokémon** that are seriously powerful, at the cost of restricting the team size down to two.
- **Passive Abilities** that react to game events like fainting, switching, or move usage.
- **Turn-based combat** focused on skill, not randomness (apologies, dear gambling addicts).
- **Comeback mechanics** via Arceus’ Altar.
- **Hidden Information Layer** through a limited Pokédex scan.
- **Comprehensive Logging** of every action and event in the game.
- **Save/Load System** using binary files to preserve match progress.
**Example log:**
`→ [TURN 3] P1 uses "Shadow Pulse" on Dialga
→ Dialga takes 30 damage
→ Dialga fainted
→ P1 gains 1 Altar charge
→ Dialga triggers passive: Time Loop (next turn skipped for enemy) 
→ P1 uses Arceus' Altar: sacrifices 25% HP to revive Gengar at 10 HP`

> [!NOTE]
> Only **one** EX Pokémon may be drafted per team at maximum. Example log not indicative of moves/passives actually used in the implementation, purely there for reference.

---

## 🧠 OOP Design & Requirement Coverage

| Requirement               | Implementation Example                                      |
|--------------------------|-------------------------------------------------------------|
| **Inheritance**          | `PokémonEX` inheriting attributes and methods from `Pokémon` class.|
| **Polymorphism**         | `apply()` methods on moves and passives                     |
| **Composition**          | `Pokemon` composed of `Move[]`, `PassiveAbility`, etc.      |
| **Aggregation**          | `Player` owns a `vector<Pokemon>` team                      |
| **Association**          | `Game` interacts with `Player`, `Logger`, and `GameContext` |
| **Exception Handling**   | Custom exceptions for invalid actions, file I/O, etc.       |
| **Templates**            | Generic logging function `logEvent<T>()` and possible generic team container |
| **Logging**              | All moves, passives, altar effects, and game results|
| **Binary Save/Load**     | Save and restore game state mid-match using binary files    |

---

## 🧪 Technologies Used

- C++  
- OOP Design Patterns  
- File I/O (Binary)  
- STL Containers (mainly `<vector> `)
- Git for Version Control

---

## 🛠️ Building and Running (In the works, I'm new to this)
