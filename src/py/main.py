#!/bin/python

from main_window import main_window
from core import cardworld , game_object , game_object_type
from gui import cardworld_gui
from common import card_attribute as ca

from PyQt4 import QtGui , QtCore
import sys
import sip
from copy import deepcopy

app = QtGui.QApplication(sys.argv)
mw = main_window()

cards = []

card_type = game_object_type()

for i in range(50):
	c = game_object(card_type)
	c[ca.text] = 'card' + str(i)
	c[ca.check_size] = 0
	c[ca.time] = 0
	c[ca.effect] = '$effect'
	cards.append(c)

world = cardworld()

hand_location = ('hand',)
deck_location = ('deck',)

for card in cards:
	world[deck_location].cardstack().insert(card)

world[deck_location].cardstack().shuffle()

locations = [ hand_location , deck_location ]

guiworld = cardworld_gui()
guiworld [ hand_location ] = mw.hand
guiworld [ deck_location ] = mw.deck

for l in locations:
	guiworld [l].update_cards ( world[l].cardstack() )

def draw ():
	new_loc = world.move ( cardworld.card_location (deck_location , 0) , hand_location )
	card = world [ new_loc ]
	guiworld.move ( deck_location , hand_location , card )

mw.draw.clicked.connect (draw)

mw.show()

sys.exit(app.exec_())

