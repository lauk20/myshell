# myshell

## Introduction
This is a simple shell program that can be run inside another shell. It contains the core features that many shells have.

## Features
- Command(s) execution (ex. ```ls -a -l; echo hello```)
- Piping multiple commands (ex. ```ls -a -l | grep README | grep READ```)
- Input/Output redirection (ex. ```ls -a -l > files.txt", "echo < files.txt```);
- Changing directories (ex. ```cd ..```)

## Prospective Features
- Appending to files (ex. ```ls -a -l >> files.txt```)
- Wildcard character (ex. ```ls -a -l | grep *EADME```)

## How to Run
To run this shell, clone the repository and run ```make``` in a terminal of your choice and then run ```make run```.
