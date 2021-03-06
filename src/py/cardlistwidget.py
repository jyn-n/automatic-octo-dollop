from PyQt4 import QtGui , QtCore

from overlap_layout import OverlapLayout , FactorWidth

from core import cardstack , game_object , cardworld
from cardwidget import CardWidget

import sip

class CardlistWidget (QtGui.QWidget):

	double_clicked = QtCore.pyqtSignal ( cardworld.card_location )

	def __init__ ( self , parent = None ):
		super().__init__( parent )

		self._current_top = None
		self.setLayout ( OverlapLayout ( self, FactorWidth(.8) ) )
		self._widgets = dict()
		self._locations = dict()
		self._location = None

		#TODO set this value in designer
		self._highlighting = True

	def highlighting ( self , highlighting = None ):
		if not highlighting is None:
			self._highlighting = highlighting
		return self._highlighting

	def rearrange ( self , new_top ):
		if not self._current_top is None:
			sign = lambda i: (i>0) - (i<0)
			direction = sign (new_top - self._current_top)
			if direction != 0:
				for i in range( self._current_top , new_top , direction ):
					self.layout().itemAt(i + direction).widget().raise_()
		self.currentTop ( new_top )

	def currentTop ( self , i ):
		if not self._current_top is None:
			self.currentItem().widget().highlight ( False )
		self._current_top = i
		if not self._current_top is None:
			if self.highlighting():
				self.currentItem().widget().highlight ( True )

	def addWidget ( self , widget ):
		widget.highlight ( False )
		self.layout().addWidget ( widget )
		widget.lower()
		if self._current_top is None:
			self.currentTop (0)

	def removeWidget ( self , widget ):
		switch_top = False
		if self.layout().indexOf( widget ) == self._current_top:
			if self._current_top > 0:
				self.rearrange ( self._current_top - 1 )
			elif len(self._widgets) > 0:
				self.rearrange(1)
				switch_top = True
			else:
				self.currentTop ( None )

		self.layout().removeWidget ( widget )
		if switch_top:
			self._current_top = None
			self.currentTop (0)


	def currentItem ( self ):
		return self.layout().itemAt ( self._current_top )

	def mousePressEvent ( self , event ):
		super().mousePressEvent ( event )
		def directChildAt ( pos ):
			child = self.childAt (pos)
			if child is None: return None
			while child.parent() != self:
				child = child.parent()
			return child

		child = directChildAt ( event.pos() )
		if child is None: return
		clicked_index = self.layout().indexOf (child)
		emit_later = (clicked_index == self._current_top)
		self.rearrange ( clicked_index )
		if emit_later:
			self.double_clicked.emit( cardworld.card_location ( self._location , self.location(child.card())  ) )

	def insert ( self , card_location , card ):
		widget = CardWidget ( card , self )
		self._widgets [ card.id() ] = widget
		self._locations [ card.id() ] = card_location
		self.addWidget ( widget )

	def erase ( self , location ):
		card = self._widgets [ location ].card()
		widget = self._widgets.pop ( card.id() )
		self._locations.pop ( card.id() )
		self.removeWidget ( widget )
		sip.delete ( widget )

	def location ( self , card ):
		return self._locations [ card.id() ]

	def update_cards ( self , cardstack , location ):
		self._location = location
		for key in cardstack:
			card = cardstack[key]
			if self._widgets.keys().isdisjoint ( [card.id()] ):
				self.insert ( cardworld.card_location ( location , key ) , card )

		for card in list(self._widgets.values()):
			cards = [ cardstack [ key ] for key in cardstack ]
			if not card.card() in cards:
				self.erase ( self.location(card.card()) )

	def current_card_location ( self ):
		item = self.currentItem ()
		if item is None: return None
		return cardworld.card_location ( self._location , self.location ( item.widget().card() ) )

