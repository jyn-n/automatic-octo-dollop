#!/bin/python

from main_window import main_window
from core import cardworld , game_object , game_object_type , game
from gui import cardworld_gui
from common import card_attribute as ca , load_type_dir , directories as d , load_deck , logger , event_manager , player_location as pl , event , log

from PyQt4 import QtGui , QtCore
import sys

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

guiworld = cardworld_gui()
guiworld [ g.location ( p , pl.hand ) ] = mw.hand
guiworld [ g.location ( p , pl.deck ) ] = mw.deck
guiworld [ g.location ( p , pl.reveal ) ] = mw.reveal
guiworld [ g.location ( p , pl.discard ) ] = mw.discard
guiworld [ g.location ( p , pl.play ) ] = mw.play
guiworld.update ( g.cardworld() )

def draw ():
	g.draw (p)

def move ( origin , destination ):
	guiworld.move ( origin , destination , g.cardworld()[destination] )

def play ( card_location ):
	e ( event.play , p , card_location )

def show_successes ():
	text = ''
	reveal = g.cardworld() [ g.location ( p , pl.reveal ) ].cardstack()
	for key in reveal:
		text += reveal [ key ] [ ca.successes ]

	mw.successes.setText ( text )

def update_deck_size (*args):
	mw.deck_size.setText ( str ( len ( g.cardworld() [ g.location ( p , pl.deck) ].cardstack() ) ) )

def cleanup ():
	e ( event.cleanup_cardplay , p )

update_deck_size ()
show_successes ()

mw.draw.clicked.connect ( draw )
e.register_event ( event.post_card_move, move )
e.register_event ( event.post_card_move, update_deck_size )
mw.hand.double_clicked.connect ( play )
e.register_event ( event.post_play, show_successes )
mw.cleanup.clicked.connect ( cleanup )

mw.show()
sys.exit(app.exec_())

