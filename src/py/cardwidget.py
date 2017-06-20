from PyQt4 import uic
from PyQt4 import QtGui , QtCore

from common import card_attribute as ca

ui_card_widget , base_class = uic.loadUiType("cardwidget.ui")

class CardWidget (ui_card_widget , base_class):

	clicked = QtCore.pyqtSignal ()

	def __init__ ( self , card , card_location , parent = None ):
		ui_card_widget.__init__(self)
		base_class.__init__(self , parent)
		self.setupUi(self)

		self._card = card
		self.show_card()

	def card ( self ):
		return self._card

	def show_card ( self ):
		for label , text in (
			  (self.label_title , self._card[ ca.title ])
			, (self.label_title2 , self._card[ ca.title ])
			, (self.label_effect , self._card[ ca.effect ])
			, (self.label_check_size , str(self._card[ ca.check_size ]))
			, (self.label_time , str(self._card[ ca.time ]))
			, (self.label_successes , self._card[ ca.successes ])
			):
			label.setText ( text )
		palette = self.area_image.palette()
		palette.setColor ( self.area_image.backgroundRole() , QtGui.QColor(self._card[ ca.color ]) )
		self.area_image.setPalette ( palette )

	def _rim_color ( self , color ):
		palette = self.palette()
		palette.setColor ( self.backgroundRole() , color )
		self.setPalette ( palette )

	def highlight ( self , do):
		self._rim_color ( { True : QtGui.QColor ( 'red' ) , False : QtGui.QColor ( 'black' ) } [do] )

