import sys
import numpy as np
from PyQt5.QtWidgets import (QWidget, QGridLayout, QApplication, QGroupBox, QVBoxLayout, QLabel, QHBoxLayout, QPushButton, QLineEdit, QFormLayout, QCheckBox)
from PyQt5.QtGui import QPixmap
from PyQt5 import QtCore
from pyqtgraph import PlotWidget, plot
import pyqtgraph as pg
import csv
import pandas as pd

WINDOW_TITLE = 'Ground Control System'
class MainWindow(QWidget):
	
	def __init__(self):
		super().__init__()
		self.data = pd.read_csv('a.csv')

		
		self.telemetryFields = ['<MISSION_TIME>','<PACKET_COUNT>',
							'<ALTITUDE>', '<TEMP>', '<VOLTAGE>', 
							'<GPS_LATITUDE>', '<GPS_LONGITUDE>', '<GPS_ALTITUDE>',
							'<SP1_ALTITUDE>', '<SP1_TEMP>', '<SP1_ROTATION_RATE>',
							'<SP2_ALTITUDE>', '<SP2_TEMP>', '<SP2_ROTATION_RATE>']
		
		self.widgetNames = ['GCS INFO', 'COMMANDS', 'ALTITUDE : 487.3 m', 'TEMPERATURE : 17.1 °C', 'VOLTAGE : 3.33 V', 'GPS LATITUDE : 28.7531 ', 'GPS LONGITUDE : 77.1178',
							'GPS ALTITUDE : 487.2 m', 'PAYLOAD1 ALTITUDE : 450.7 m', 'PAYLOAD1 TEMPERATURE : 23.4 °C', 'PAYLOAD1 ROTATION RATE : 273 RPM', 'PAYLOAD2 ALTITUDE : NULL m' , 'PAYLOAD2 TEMPERATURE : NULL °C', 'PAYLOAD2 ROTATION RATE : NULL RPM']
		
		self.labels = ['TEAM ID', 'MISSION TIME', 'TOTAL PACKET COUNT', 'PAYLOAD1 PACKET COUNT', 'PAYLOAD2 PACKET COUNT', 'PACKET TYPE', 'MODE', 'PAYLOAD1 RELEASED', 'PAYLOAD2 RELEASED', 'GPS TIME'    , 'GPS SATS', 'SOFTWARE STATE', 'LAST COMMAND']
		self.vals =   [1357     , '15:10:30 UTC', 1000                , 300                    , 0                    , 'C'          , 'S'   ,   'R'                 , 'N'               , '15:10:30 UTC', 4         , 'SP1_RELEASED'  , 'SIMP 100833' ]
		
		self.stages = ['Apogee Reached', 'Container Released', 'Parachute Deployed', 'Container Landed', 'Payload1 Released', 'Payload2 Released', 'Payload1 Landed', 'Payload2 Landed']
		self.states = [True            , True                , True                , False             , True                , False               , False             , False             ]
		
		self.imgPath = 'logo.png'
		
		self.buttons = ['START', 'ST', 'CX ON', 'CX OFF', 'PX1 ON', 'PX1 OFF', 'PX2 ON', 'PX2 OFF', 'SIM ENABLE', 'SIM ACTIVATE', 'SIM DISABLE', 'SIMP']

		self.widgetPosAndSizes = self.setWidgetPosAndSize()

		self.initUI()
		

	def initUI(self):
		self.grid = QGridLayout()
		self.setLayout(self.grid)
	
		for i in range(len(self.widgetNames)):
			self.widget = QGroupBox(self.widgetNames[i], self)

			if i == 0:
				self.addGCSInfo()
				
			elif i == 1:
				self.addCommands()

			else:
				self.addPlotter(i)												
			
			self.grid.addWidget(self.widget, *self.widgetPosAndSizes[i])	

		self.move(300, 150)
		self.show()
		self.setWindowTitle(WINDOW_TITLE)
	
	def setWidgetPosAndSize(self):
		widgetPosAndSizes = []
		
		for i in range(5):
			for j in range(12):
				if i == 0 and j == 0:
					widgetPosAndSizes.append((i, j, 1, 9))
				
				elif i == 0 and j < 9:
					continue

				elif i == 0 and j == 9:
					widgetPosAndSizes.append((i, j, 1, 3))

				elif j%4 == 0:
					widgetPosAndSizes.append((i, j, 1, 4))
		
		return widgetPosAndSizes

	def addGCSInfo(self):
		vbox = QVBoxLayout()
		fboxes = [QFormLayout(), QFormLayout(), QFormLayout()]
		hbox = QHBoxLayout()
		checkboxes = [QVBoxLayout(), QVBoxLayout()] 
		
		img = QPixmap(self.imgPath)
		imgLabel = QLabel(self)
		imgLabel.setPixmap(img)
		vbox.addWidget(imgLabel)
		hbox.addLayout(vbox)
	
		rows = [0, 5, 9, 13]
		for j in range(len(rows)-1):
			for k in range(rows[j], rows[j+1]):
				l = self.labels[k]
				labelWidget = QLabel(l, self)
				labelWidget.setAlignment(QtCore.Qt.AlignRight)
				val = QLineEdit(str(self.vals[k]))
				val.setAlignment(QtCore.Qt.AlignCenter)
				val.setReadOnly(True)
				fboxes[j].addRow(labelWidget, val)
			hbox.addLayout(fboxes[j])
		
		rows = [0, len(self.stages)//2, len(self.stages)]
		for j in range(len(rows)-1):
			for k in range(rows[j], rows[j+1]):
				if self.states[k]:
					checkboxes[j].addWidget(QLabel('✔️ ' + self.stages[k]))
				else:
					checkboxes[j].addWidget(QLabel('✗ ' + self.stages[k]))
			hbox.addLayout(checkboxes[j])

		self.widget.setLayout(hbox)
	
	def addCommands(self):
		vboxes = [QVBoxLayout(), QVBoxLayout(), QVBoxLayout()]
		hbox = QHBoxLayout()

		rows = [0, 4, 8, 12]
		for j in range(len(rows)-1):
			for b in self.buttons[rows[j]:rows[j+1]]:
				vboxes[j].addWidget(QPushButton(b, self))
			hbox.addLayout(vboxes[j])

		self.widget.setLayout(hbox)
	
	def addPlotter(self, ind):
			x = self.data['<PACKET_COUNT>']
			y = self.data[self.telemetryFields[ind]]
			vbox = QVBoxLayout()
			hbox = QHBoxLayout()
			self.widget.setLayout(vbox)
			graph = pg.PlotWidget()
			graph.plot(x,y)
			hbox.addWidget(graph)
			vbox.addLayout(hbox)
		
if __name__ == '__main__':
	
	app = QApplication(sys.argv)
	window = MainWindow()
	sys.exit(app.exec_())