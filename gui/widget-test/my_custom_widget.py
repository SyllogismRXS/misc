#!/usr/bin/python3
# -*- coding: utf-8 -*-

"""
ZetCode PyQt5 tutorial 

In this example, a QCheckBox widget
is used to toggle the title of a window.

author: Jan Bodnar
website: zetcode.com 
last edited: January 2015
"""

import sys
from PyQt5.QtWidgets import QWidget, QCheckBox, QComboBox, QApplication
from PyQt5.uic import loadUi
from PyQt5.QtCore import Qt
import xml.etree.ElementTree as ET

class MyCustomWidget(QWidget):
    
    def __init__(self, parent = None):
        super(MyCustomWidget, self).__init__(parent)
            
        self.behaviors = dict()         
        self.initUI()        
            
    def initUI(self):                      
        tree = ET.parse('list.xml')
        root = tree.getroot()
            
        for child in root:
            self.behaviors[child.attrib['name']] = child.attrib['id']            
                
        self.cb = QComboBox(self)
        self.cb.addItems(self.behaviors.keys())
        self.cb.currentIndexChanged.connect(self.selectionchange)

        self.setGeometry(300, 300, 250, 150)
        self.setWindowTitle('QCheckBox')        
            
    def selectionchange(self,i):
        print('Selected: %s, value: %s' % (self.cb.currentText(), self.behaviors[self.cb.currentText()]))
              
if __name__ == '__main__':
    
    app = QApplication(sys.argv)
    ex = MyCustomWidget()
    sys.exit(app.exec_())
