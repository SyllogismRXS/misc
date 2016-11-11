# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'main_dialog.ui'
#
# Created: Mon Nov  7 15:33:30 2016
#      by: PyQt5 UI code generator 5.2.1
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_mainDialog(object):
    def setupUi(self, mainDialog):
        mainDialog.setObjectName("mainDialog")
        mainDialog.resize(770, 730)
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(mainDialog)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.verticalLayout = QtWidgets.QVBoxLayout()
        self.verticalLayout.setObjectName("verticalLayout")
        self.pushButton = QtWidgets.QPushButton(mainDialog)
        self.pushButton.setObjectName("pushButton")
        self.verticalLayout.addWidget(self.pushButton)
        self.widget = MyCustomWidget(mainDialog)
        self.widget.setObjectName("widget")
        self.verticalLayout.addWidget(self.widget)
        self.verticalLayout_2.addLayout(self.verticalLayout)

        self.retranslateUi(mainDialog)
        QtCore.QMetaObject.connectSlotsByName(mainDialog)

    def retranslateUi(self, mainDialog):
        _translate = QtCore.QCoreApplication.translate
        mainDialog.setWindowTitle(_translate("mainDialog", "Dashboard"))
        self.pushButton.setText(_translate("mainDialog", "PushButton"))

from my_custom_widget import MyCustomWidget

if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    mainDialog = QtWidgets.QDialog()
    ui = Ui_mainDialog()
    ui.setupUi(mainDialog)
    mainDialog.show()
    sys.exit(app.exec_())

