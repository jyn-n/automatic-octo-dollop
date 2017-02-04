#!/bin/python

from main_window import main_window
from core import cardworld , game_object , game_object_type
from gui import cardworld_gui
from common import card_attribute as ca , load_type_dir , directories as d , load_deck

from PyQt4 import QtGui , QtCore
import sys

app = QtGui.QApplication(sys.argv)
mw = main_window()

card_types = load_type_dir ( d.card_types )

deck = load_deck ( d.decks / 'foo.deck' , card_types )

world = cardworld()

hand_location = ('hand',)
deck_location = ('deck',)

for k , v in deck.items():
	print(k,type(v),list(v))
	world[[k]].stack(v)

world[deck_location].cardstack().shuffle()

locations = [ hand_location , deck_location ]

guiworld = cardworld_gui()
guiworld [ hand_location ] = mw.hand
guiworld [ deck_location ] = mw.deck

for l in locations:
	guiworld [l].update_cards ( world[l].cardstack() )

def move ( origin , card_identifier , destination ):
	guiworld.move ( origin , destination , world [
		world.move ( cardworld.card_location ( origin , card_identifier ) , destination ) 
	])

def draw ():
	move ( deck_location , 0 , hand_location )

def put_back ( card ):
	move ( hand_location , world[ hand_location ].cardstack().find( card ) , deck_location )

mw.draw.clicked.connect (draw)
mw.hand.double_clicked.connect ( put_back )

mw.show()

sys.exit(app.exec_())

