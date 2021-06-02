# Enigma
C++ app made for a project at University. It takes machine parameters as an input and after setting the machine up it is able to encode each character accordingly to the famous historic machine used during WW2.

Input:
Defintions of parts of the machine:
n- number of letters (numbers) in the alphabet
m - number of rotors, followed by their definitions W0,...,Wm-1
definition of rotor Wi - permutation of the alphabet
number of letters which cause turnover, followed by these letters as in "Position of turnover notches" table
l - number of reflectors
definitions of reflectors R0,...,Rl-1 - permutation of the alphabet

A set of p tasks to perform:
each task consists of 2 parts: machine setup and a message to encrypt.

p number of tasks
k - number of rotors in the machine
k pairs K0,...,Kk-1 - where Ki=(j, t), where j is an index of a copy of rotor Wj and t is its initial position
rotors are given in order from fastest to slowest
initial position of a rotor - it is set as if it was rotated (no actual rotations occur) prior to encoding, e.g. 1 - rotor is set as stated in permutation, 2 - it is shifted by one letter, etc.
r index of a reflector Rr
a sequence of numbers separated by whitespaces to encrypt, ending with the 0 character
