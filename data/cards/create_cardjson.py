import os
import json
import glob


def parse_special(bn):
    return "cloister" if bn[0] == "K" else ("emblem" if bn[0] in ["X", "Y", "Z"] else "none")


def parse_side(c):
    return "city" if c == "S" else ("road" if c == "W" else "meadow")


def parse_sides(bn):
    return {
        "top": parse_side(bn[1]),
        "left": parse_side(bn[2]),
        "bottom": parse_side(bn[3]),
        "right": parse_side(bn[4])
    }


def parse_connections(sides):
    connections = {}
    for k, v in sides.items():
        connections[k] = [k2 for k2, v2 in sides.items() if (v2 == v and k2 != k and v != "meadow")]
    return connections


fns = sorted(glob.glob("/media/ts/Data/Programmieren/Spiele/Kacassonne/data/cards/*.jpg"))
data = {}
for fn in fns:
    bn = os.path.basename(fn)
    c = {"special": parse_special(bn),
         "sides": parse_sides(bn)}
    c["connections"] = parse_connections(c["sides"])

    data[bn] = c
json.dump(data, open("/media/ts/Data/Programmieren/Spiele/Kacassonne/data/cards/card_data.json", 'w'))
