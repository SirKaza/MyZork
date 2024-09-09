# Zork: A Text Adventure Game

## Overview

Zork is a classic text-based adventure game (first released in 1977) where players explore a mysterious world, solve puzzles, and interact with various characters. The game is designed to challenge your wits and immerse you in a captivating story.

## Author

- Marc Casanova Torrequebrada.

## GitHub Repository

[GitHub Repository](https://github.com/SirKaza/MyZork)

## License

This project is licensed under the [MIT License](LICENSE).

## Project structure

The development of this project had a duration of seven days and is divided in the following files:

```plaintext
zork-project-base/
├── .gitignore
├── .gitattributes
├── MyZork.sln
├── LICENSE
├── README.md
└── MyZork/
    ├── MyZork.vcxproj
    ├── MyZork.vcxproj.filters
    ├── actions.cpp
    ├── actions.h
    ├── creature.cpp
    ├── creature.h
    ├── entity.cpp
    ├── entity.h
    ├── exit.cpp
    ├── exit.h
    ├── item.cpp
    ├── item.h
    ├── lockable.cpp
    ├── lockable.h
    ├── main.cpp
    ├── main.h
    ├── player.cpp
    ├── player.h
    ├── room.cpp
    ├── room.h
    ├── world.cpp
    └── world.h
```

## Zork's World Map

![World map](https://github.com/SirKaza/MyZork/blob/master/WorldMap.png)

## Guide to play

1. Start Playing:
   - Download or clone the repository from GitHub.
   - Open the `MyZork.sln` solution file in Visual Studio.
   - Build the project and run the game.
2. Game Objectives:
   - Explore the world of Zork and uncover its mysteries.
   - Collect items that will help you in your adventure.
   - Solve puzzles to advance to new rooms.
   - Kill the Ogre.
3. How to Play:
   - The game uses text commands to interact with the world. Here are the available commands:
     
  ```
   ===== HELP MENU =====
   You can use the following commands:
   - look / l: Look around the current room or player.
     Example: 'look' to look room or 'look (me/myself/name of player)' to look player.
   - go [direction]: Move in a direction (north, south, east, west, up, down).
     Example: 'go north' or 'north' or 'n'.
   - take / get / pick / grab [item]: Pick up an item from the room. Also can take all items in room.
     Example: 'take keycard' or 'take all/everything'.
   - take / get / pick / grab [item] from/of [container]: Pick up an item from a container.
     Example: 'take keycard from leaves'.
   - drop [item]: Drop an item from your inventory. Also can drop all items in room.
     Example: 'drop keychain' or 'drop all/everything'.
   - examine [something]: Get a detailed description of something.
     Example: 'examine leaves'.
   - put [item] in [container]: Put an item into a container.
     Example: 'put keycard in box'.
   - open [something]: Open an exit or container.
     Example: 'open box'.
   - close [something]: Close an exit or container.
     Example: 'close box'.
   - lock [something] with [item]: Lock something using an item as a key.
     Example: 'lock box with keychain'.
   - unlock [something] with [item]: Unlock something using an item as a key.
     Example: 'unlock box with keychain'.
   - equip [item]: Equip an item, such as a weapon or shield.
     Example: 'equip sword'.
   - unequip [item]: Unequip a currently equipped item.
     Example: 'unequip sword'.
   - attack [someone]: Attack an enemy.
     Example: 'attack ogre'.
   - inventory / i: Check your inventory and equipment.
   - quit / q: Quit the game.
   - repeat: Repeats the last command you entered.
   - shout / yell / scream: Express your feelings.
   - jump / zork: Perform a fun, silly action.
   - help / h: Show this help menu.
   ======================
   ```

4. How to Win:
   - The game is won by defeating the `Ogre` which remains in the `Arena` room. To achieve this the player will need to equip either a weapon or a shield. If not, the `Ogre` will be stronger.
       - To get to the `Arena` room, player will need to do these certains actions:
           - Move from `Parking` to `Forest`.
           - Take the `Keycard` from `Leaves` (examine `Leaves`).
           - Open the `Hatch`  (examine `Hatch`).
           - Move from `Forest` to `Laboratory`.
           - Unlock `Door` with `Keycard` (examine `Door`).
           - Open `Door`.
           - Move from `Laboratory` to `Arena`.
       - To equip a weapon from start, player will need to do these certains actions:
           - Move from `Parking` to `Picnic`.
           - Take the `Keychain` from `Table` (examine `Table`).
           - Move from `Picnic` to `Parking`.
           - Unlock `Car` with `Keychain` (examine `Keychain`) (examine `Car`).
           - Open `Car`.
           - Take the `Sword` from `Car` (examine `Car`).
           - Equip the `Sword`.
       - To equip a shield from start, player will need to do these certains actions:
           - Move from `Parking` to `Picnic`.
           - Take the `Keychain` from `Table` (examine `Table`).
           - Move from `Picnic` to `Parking`.
           - Move from `Parking` to `Forest`.
           - Open the `Hatch`  (examine `Hatch`).
           - Move from `Forest` to `Laboratory`.
           - Unlock `Box` with `Keychain` (examine `Box`) (take `Box`).
           - Open `Box`.
           - Take the `Shield` from `Box` (examine `Box`).
           - Equip the `Shield`.

## Versions Used

- IDE: 
  - Visual Studio 2019 Community: 16.11.39
- Llenguatge:
  - C++: standard ISO C++14
