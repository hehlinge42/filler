# Filler @42

The filler project consists in coding an AI to win at the "filler" game, which rules are available in the subject, inside the repository

## Installation

To download the repository, open a UNIX terminal and write `gcl https://github.com/hehlinge42/filler.git`

You can read the subject by typing `open resources/filler.fr.pdf`

To compile the project, type "make" at the root of the repository. This will:
- compile the library "libft.a" in the folder ./libft
- compile the program hehlinge.filler at the root of the repository and in the folder ./resources/players 
- compile the visualizer "color" in the folder ./color

## Battle

To start a battle, type the following command line in the folder "./resources" (access with `cd resources`): 
`./filler_vm -f maps/maps00 -p1 players/hehlinge.filler -p2 players/hehlinge.filler | ./color`
This command line:
- launches the virtual machine provided in the resources
- set a map through the option -f. A set of maps is provided in the sub-folder "maps"
- set two players with the options -p1 and -p2. A set of players is provided in the sub-folder "players"
- pipes the output in the program color

## Visualizer

The program color has the following options:
 - anim, displays an animation before the battle
 - color, color_new: color the whole board (color_new for new pieces only);
 - slow, medium, fast, speed: [your speed (microseconds)]: set game speed;
 - board, degree, diamond set: board symbol (turns on color);
 These options must be launched as follows: ex: -anim
