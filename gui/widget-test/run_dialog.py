# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'main_dialog.ui'
#
# Created: Mon Nov  7 12:32:11 2016
#      by: PyQt5 UI code generator 5.2.1
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets
import sys
import main_dialog
import my_custom_widget

#sys.modules[''] = my_custom_widget.MyCustomClasses

app = QtWidgets.QApplication(sys.argv)
mainDialog = QtWidgets.QDialog()
ui = main_dialog.Ui_mainDialog()
ui.setupUi(mainDialog)

#my_widget = my_custom_widget.MyCustomWidget()
#my_widget.setObjectName("My Widget")
#ui.verticalLayout.addWidget(my_widget)


mainDialog.show()
sys.exit(app.exec_())

