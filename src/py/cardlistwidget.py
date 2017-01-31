from PyQt4 import QtGui , QtCore

from overlap_layout import OverlapLayout

from core import cardstack , game_object
from cardwidget import CardWidget

import sip

class CardlistWidget (QtGui.QWidget):

	double_click = QtCore.pyqtSignal ( game_object )

	def __init__ ( self , parent = None ):
		super().__init__( parent )

		self._current_top = None
		self.setLayout ( OverlapLayout (self) )
		self._widgets = dict()

	def rearrange ( self , new_top ):

		if self._current_top is None: return

		sign = lambda i: (i>0) - (i<0)
		direction = sign (new_top - self._current_top)

		if direction == 0: return

		for i in range( self._current_top , new_top , direction ):
			self.layout().itemAt(i + direction).widget().raise_()

		self._current_top = new_top

	def addWidget ( self , widget ):
		if self._current_top is None: self._current_top = 0
		self.layout().addWidget ( widget )
		widget.lower()

	def removeWidget ( self , widget ):
		if len(self._widgets) == 0:
			self._current_top = None
		elif self.layout().indexOf( widget ) <= self._current_top:
			self._current_top -= 1
			if self._current_top < 0:
				self.rearrange(0)
				self._current_top = 0

		self.layout().removeWidget ( widget )

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
		if clicked_index == self._current_top:
			self.double_click.emit( child.card() )
		self.rearrange ( self.layout().indexOf( child ) )

	def insert ( self , card ):
		widget = CardWidget ( self )
		widget.set_card ( card )
		self._widgets [card]  = widget
		self.addWidget ( widget )

	def erase ( self , card ):
		widget = self._widgets.pop ( card )
		self.removeWidget ( widget )
		sip.delete ( widget )

	def clear ( self ):
		for key in list(self._widgets.keys()):
			self.erase ( key )

	def update_cards ( self , cardstack ):
		for card in cardstack:
			if self._widgets.keys().isdisjoint ( [card] ):
				self.insert ( card )

		for card in list(self._widgets.keys()):
			if not card in cardstack:
				self.erase ( card )

