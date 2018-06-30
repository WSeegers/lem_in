#!/usr/bin/env python

import sys

def move_err(i, txt):
    print "["+str(i)+"] " + txt
    exit(1)

output = sys.stdin.readlines()

while output[0][0] == '#':
    output.pop(0)

ant_no = int(output.pop(0))
nodes = []
links = {}
inst = []
lems = {}

while len(output) > 0:
    line = output.pop(0)
    if line == "\n":
        break
    if line[0] == '#':
        if line == "##start\n":
            start = output.pop(0)[:-1].split(' ')[0]
            nodes.append(start)
        if line == "##end\n":
            target = output.pop(0)[:-1].split(' ')[0]
            nodes.append(target)
        continue
    if '-' in line:
        link = line[:-1].split('-')
        if link[1] in links:
            links[link[1]].append(link[0])
        else:
            links[link[1]] = [link[0]]
        if link[0] in links:
            links[link[0]].append(link[1])
        else:
            links[link[0]] = [link[1]]
        continue
    nodes.append(line[:-1].split(' ')[0])

for line in output:
    line = line[:-1].strip().split(' ')
    line[:] = [move.split('-') for move in line]
    inst.append(line)

for i, moves in enumerate(inst):
    for move in moves:
        if 'L' not in move[0]:
            move_err(i, "Invalid lem-in name! [ " + move[0] + " ]")
        if move[1] not in nodes:
            move_err(i, "Lem-in moved to non existant node! [ " + move[1] + " ]")
        if move[1] == start:
            move_err(i, "A Lem-in walked back into the start!")
        if move[0] in lems:
            if not lems[move[0]] in links[move[1]]:
                move_err(i, move[0] + " is digging a new shaft to " + move[1] + " from " + lems[move[0]])
        else:
            if not start in links[move[1]]:
                move_err(i, move[0] + " is digging a new shaft to " + move[1] + " from " + start)
        lems[move[0]] = move[1]
        if move[1] == target:
            del lems[move[0]]
            ant_no -= 1
    if not len(set(lems.values())) == len(lems):
        move_err(i, "Seems some ants are having sexy time in the same room!")

if len(lems):
    print "You have failed your lem-ins and " +\
        "have left some of the poor bastards lost and alone " +\
        "you should commit Hara-kiri"
    print "The Honorable:"
    print lems
    exit (1)
else:
    print "Congratulations you have managed to save all your lem-ins and shall now" +\
        " receive cake"
    print "Moves: " + str(len(inst))
