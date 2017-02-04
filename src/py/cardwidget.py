from PyQt4 import uic
from PyQt4 import QtGui , QtCore

from common import card_attribute as ca

ui_card_widget , base_class = uic.loadUiType("cardwidget.ui")

class CardWidget (ui_card_widget , base_class):

	clicked = QtCore.pyqtSignal ()

	def __init__ ( self , parent = None ):
		ui_card_widget.__init__(self)
		base_class.__init__(self , parent)
		self.setupUi(self)

		self._card = None

	def set_card ( self , card ):
		self._card = card
		self.show_card()

	def card ( self ):
		return self._card

	def show_card ( self ):
		for label , text in (
			  (self.title , self._card[ ca.title ])
			, (self.effect , self._card[ ca.effect ])
			, (self.check_size , str(self._card[ ca.check_size ]))
			, (self.time , str(self._card[ ca.time ]))
			):
			label.setText ( text )

