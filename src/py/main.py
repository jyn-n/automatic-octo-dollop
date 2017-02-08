#!/bin/python

from main_window import main_window
from core import cardworld , game_object , game_object_type , game
from gui import cardworld_gui
from common import card_attribute as ca , load_type_dir , directories as d , load_deck , logger , event_manager , player_location as pl , event , log

from PyQt4 import QtGui , QtCore
import sys
from functools import reduce

#l = logger(log.event)
l = logger()
e = event_manager(l)

g = game(1 , e)
p = list(g.players())[0]

card_types = load_type_dir ( d.card_types )
deck = load_deck ( d.decks / 'foo.deck' , card_types )
g.load_deck ( p , deck )
g.cardworld() [ g.location ( p , pl.deck ) ].cardstack().shuffle()

app = QtGui.QApplication(sys.argv)
mw = main_window()

mw.stack_reveal.highlighting ( False )

guiworld = cardworld_gui()
guiworld [ g.location ( p , pl.hand ) ] = mw.stack_hand
guiworld [ g.location ( p , pl.reveal ) ] = mw.stack_reveal
guiworld.update ( g.cardworld() )

def draw ():
	g.draw (p)

def move ( origin , destination ):
	guiworld.move ( origin , destination , g.cardworld()[destination] )

def play ( card_location ):
	e ( event.play , p , card_location )

def show_successes (*args):
	text = list()
	reveal = g.cardworld() [ g.location ( p , pl.reveal ) ].cardstack()
	for key in reveal:
		text += [ reveal [ key ] [ ca.successes ] ]

	text.sort()

	mw.value_successes.setText ( reduce ( lambda x,y: x+y , text , '' ) )

def update_deck_size (*args):
	mw.value_deck_size.setText ( str ( len ( g.cardworld() [ g.location ( p , pl.deck) ].cardstack() ) ) )

def cleanup ():
	e ( event.cleanup_cardplay , p )

def reveal ():
	e ( event.reveal , p )

def discard ():
	card_location = mw.stack_hand.current_card_location ()
	if card_location is None: return
	e ( event.discard , p , card_location )

update_deck_size ()
show_successes ()

mw.button_draw.clicked.connect ( draw )
e.register_event ( event.post_card_move, move )
e.register_event ( event.post_card_move, update_deck_size )
mw.stack_hand.double_clicked.connect ( play )
e.register_event ( event.post_card_move, show_successes )
mw.button_cleanup.clicked.connect ( cleanup )
mw.button_reveal.clicked.connect ( reveal )
mw.button_discard.clicked.connect ( discard )

mw.show()
sys.exit(app.exec_())

