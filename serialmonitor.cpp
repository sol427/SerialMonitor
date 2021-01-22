#include "serialmonitor.h"
#include <stdio.h>
#include <QSerialPortInfo>

SerialMonitor::SerialMonitor() : connectionState(false), saveTerminalFileExists(false) {
    // USER INTERFACE
    // Widgets config
    int buttonHeight = 23;

    // config panels check boxes
    m_SCconfigPanelCheckBox = new QCheckBox("Serial communication config panel", this);
        m_SCconfigPanelCheckBox->setLayoutDirection(Qt::RightToLeft);
        m_SCconfigPanelCheckBox->setChecked(true);
        m_SCconfigPanelCheckBox->setMaximumHeight(20);
    m_terminalConfigPanelCheckBox = new QCheckBox("Terminal config panel", this);
        m_terminalConfigPanelCheckBox->setLayoutDirection(Qt::RightToLeft);
        m_terminalConfigPanelCheckBox->setChecked(true);
        m_terminalConfigPanelCheckBox->setMaximumSize(180, 20);

    // portListLayout's widgets
    m_portsListWidgetTitle = new QLabel("Available serial ports", this);
        m_portsListWidgetTitle->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_portsListWidget = new QListWidget(this);
        m_portsListWidget->setMaximumSize(150, 90);
        m_portsListWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_connectionStatusLabel = new QLabel("Not connected", this);
    m_connectionStatusLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    //config2Layout's widgets
    m_baudrateLabel = new QLabel("Baudrate", this);
        m_baudrateLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_parityLabel = new QLabel("Parity Bit", this);
    m_dataBitsLabel = new QLabel("Data Bits", this);
    m_stopBitsLabel = new QLabel("Stop Bits", this);
    m_dataFormatLabel = new QLabel("Format", this);
    m_baudrateBox = new QComboBox(this);
        m_baudrateBox->setMaximumWidth(120);
        m_baudrateBox->setMaximumHeight(buttonHeight);
        m_baudrateBox->addItem("1200"); m_baudrateBox->addItem("2400");
        m_baudrateBox->addItem("4800"); m_baudrateBox->addItem("9600");
        m_baudrateBox->addItem("19200"); m_baudrateBox->addItem("38400");
        m_baudrateBox->addItem("57600"); m_baudrateBox->addItem("115200");
        m_baudrateBox->setCurrentIndex(3);
    m_parityBox = new QComboBox(this);
        m_parityBox->setMaximumWidth(120);
        m_parityBox->setMaximumHeight(buttonHeight);
        m_parityBox->addItem("none"); m_parityBox->addItem("odd");
        m_parityBox->addItem("even"); m_parityBox->addItem("0"); // 0 = SpaceParity
        m_parityBox->addItem("1"); // 1 = MarkParity
    m_dataBitsBox = new QComboBox(this);
        m_dataBitsBox->setMaximumWidth(120);
        m_dataBitsBox->setMaximumHeight(buttonHeight);
        m_dataBitsBox->addItem("5"); m_dataBitsBox->addItem("6");
        m_dataBitsBox->addItem("7"); m_dataBitsBox->addItem("8");
        m_dataBitsBox->setCurrentIndex(3);
    m_stopBitsBox = new QComboBox(this);
        m_stopBitsBox->setMaximumWidth(120);
        m_stopBitsBox->setMaximumHeight(buttonHeight);
        m_stopBitsBox->addItem("1"); m_stopBitsBox->addItem("1.5");
        m_stopBitsBox->addItem("2");
    m_dataFormatBox = new QComboBox(this);
        m_dataFormatBox->setMaximumWidth(120);
        m_dataFormatBox->setMaximumHeight(buttonHeight);
        m_dataFormatBox->addItem("ASCII"); m_dataFormatBox->addItem("hex");

    // config3layout's widgets
    m_saveConfigButton = new QPushButton("Save config", this);
        m_saveConfigButton->setMinimumWidth(100);
        m_saveConfigButton->setMaximumHeight(buttonHeight);
        m_saveConfigButton->setMaximumWidth(100);

    m_loadConfigButton = new QPushButton("Load config", this);
        m_loadConfigButton->setMinimumWidth(100);
        m_loadConfigButton->setMaximumHeight(buttonHeight);
        m_loadConfigButton->setMaximumWidth(100);

    // config4layout's widgets
    m_fillerLabel = new QLabel(" ", this);

    m_terminal = new QTextEdit(this);
        m_terminal->setReadOnly(true);
        m_terminal->setFontItalic(true);

    // sendLayout's widgets
    m_sendLineEdit = new QLineEdit(this);
    m_sendButton = new QPushButton("send", this);
        m_sendButton->setMaximumHeight(buttonHeight);
    m_sendNLCharCheckBox = new QCheckBox("append \\n to message", this);
    m_clearAfterSendCheckBox = new QCheckBox("clear message after sending", this);


    // terminal config panel
    m_clearTerminalButton = new QPushButton("Clear", this);
        m_clearTerminalButton->setMaximumWidth(120);
        m_clearTerminalButton->setMaximumHeight(buttonHeight);
    m_autoscrollCheckBox = new QCheckBox("auto scroll down", this);
        m_autoscrollCheckBox->setChecked(true);
    m_displayNewLine = new QCheckBox("display \\n", this);
    m_saveTerminalButton = new QPushButton("Save terminal", this);
        m_saveTerminalButton->setMaximumWidth(120);
        m_saveTerminalButton->setMaximumHeight(buttonHeight);
    m_sendFileButton = new QPushButton("Send File", this);
        m_sendFileButton->setMaximumWidth(120);
        m_sendFileButton->setMaximumHeight(buttonHeight);


    // Layouts config
    //  The user interface is designed as a succession of layouts, embedded in other layouts.
    //  Indentation represents the hierarchy. The widgets are inserted in the layouts
    //  The order of the commands determines the physical order of the widgets/layouts.
    //  m_configPanelLayout is embedded in a widget with fixed height so that it does not
    //  get too big.
    m_mainLayout = new QVBoxLayout(this);
        m_panelCheckBoxesLayout = new QHBoxLayout(this);
            m_panelCheckBoxesLayout->setAlignment(Qt::AlignRight);
        m_panelCheckBoxesLayout = new QHBoxLayout(this);
        m_SCconfigPanelRestrictWidget = new QWidget(this);
            m_SCconfigPanelLayout = new QHBoxLayout(this);
                m_SCconfigPanelRestrictWidget->setMaximumHeight(200);
                m_SCconfigPanelRestrictWidget->setLayout(m_SCconfigPanelLayout);
                m_SCconfigPanelRestrictWidget->setStyleSheet(".QWidget { border: 1px solid #B0B0B0; }");
                m_config1Layout = new QVBoxLayout(this);
                    m_config1Layout->setAlignment(Qt::AlignTop);
                    m_spacer1 = new QSpacerItem(15, 10);
                m_config2Layout = new QGridLayout(this);
                    m_config2Layout->setAlignment(Qt::AlignTop);
                    m_spacer2 = new QSpacerItem(15, 10);
                m_config3Layout = new QGridLayout(this);
                    m_config3Layout->setAlignment(Qt::AlignTop);
                    m_spacer3 = new QSpacerItem(15, 10);
                m_config4Layout = new QGridLayout(this);
        m_sendLayout = new QHBoxLayout(this);
        m_terminalConfigPanelRestrictWidget = new QWidget(this);
        m_terminalConfigPanelLayout = new QVBoxLayout(this);
            m_terminalConfigPanelLayout->setAlignment(Qt::AlignLeft);
            m_terminalConfigPanelRestrictWidget->setMaximumHeight(200);
            m_terminalConfigPanelRestrictWidget->setLayout(m_terminalConfigPanelLayout);
            m_terminalConfigPanelRestrictWidget->setStyleSheet(".QWidget { border: 1px solid #B0B0B0; }");
            m_terminalConfig1Layout = new QHBoxLayout(this);
                m_terminalConfig1Layout->setAlignment(Qt::AlignLeft);
            m_terminalConfig2Layout = new QHBoxLayout(this);
                m_terminalConfig2Layout->setAlignment(Qt::AlignLeft);

    m_mainLayout->addLayout(m_panelCheckBoxesLayout);
    m_mainLayout->addWidget(m_SCconfigPanelRestrictWidget);
    m_mainLayout->addWidget(m_terminal);
    m_mainLayout->addLayout(m_sendLayout);
    m_mainLayout->addWidget(m_terminalConfigPanelRestrictWidget);

        m_panelCheckBoxesLayout->addWidget(m_SCconfigPanelCheckBox);
        m_panelCheckBoxesLayout->addWidget(m_terminalConfigPanelCheckBox);

        m_SCconfigPanelLayout->addLayout(m_config1Layout);
        m_SCconfigPanelLayout->addItem(m_spacer1);
        m_SCconfigPanelLayout->addLayout(m_config2Layout);
        m_SCconfigPanelLayout->addItem(m_spacer2);
        m_SCconfigPanelLayout->addLayout(m_config3Layout);
        m_SCconfigPanelLayout->addItem(m_spacer3);
        m_SCconfigPanelLayout->addLayout(m_config4Layout);
            m_config1Layout->addWidget(m_portsListWidgetTitle);
            m_config1Layout->addWidget(m_portsListWidget);
            m_config1Layout->addWidget(m_connectionStatusLabel);
            m_config2Layout->addWidget(m_baudrateLabel, 0, 0);
            m_config2Layout->addWidget(m_baudrateBox, 0, 1);
            m_config2Layout->addWidget(m_parityLabel, 1, 0);
            m_config2Layout->addWidget(m_parityBox, 1, 1);
            m_config2Layout->addWidget(m_dataBitsLabel, 2, 0);
            m_config2Layout->addWidget(m_dataBitsBox, 2, 1);
            m_config2Layout->addWidget(m_stopBitsLabel, 3, 0);
            m_config2Layout->addWidget(m_stopBitsBox, 3, 1);
            m_config2Layout->addWidget(m_dataFormatLabel, 4, 0);
            m_config2Layout->addWidget(m_dataFormatBox, 4, 1);
            m_config3Layout->addWidget(m_saveConfigButton, 0, 0);
            m_config3Layout->addWidget(m_loadConfigButton, 1, 0);
            m_config4Layout->addWidget(m_fillerLabel, 0, 0);


        m_sendLayout->addWidget(m_sendLineEdit);
        m_sendLayout->addWidget(m_sendButton);

        m_terminalConfigPanelLayout->addLayout(m_terminalConfig1Layout);
        m_terminalConfigPanelLayout->addLayout(m_terminalConfig2Layout);
            m_terminalConfig1Layout->addWidget(m_autoscrollCheckBox);
            m_terminalConfig1Layout->addWidget(m_displayNewLine);
            m_terminalConfig1Layout->addWidget(m_clearAfterSendCheckBox);
            m_terminalConfig2Layout->addWidget(m_clearTerminalButton);
            m_terminalConfig2Layout->addWidget(m_saveTerminalButton);
            m_terminalConfig2Layout->addWidget(m_sendFileButton);
            m_terminalConfig2Layout->addWidget(m_sendNLCharCheckBox);

    setLayout(m_mainLayout);


    m_port = new QSerialPort(this);
        m_port->setBaudRate(9600);
        m_port->setParity(QSerialPort::NoParity);
        m_port->setDataBits(QSerialPort::Data8);
        m_port->setStopBits(QSerialPort::OneStop);

    m_portInfo = new QList<QSerialPortInfo>;
    m_portInfo->append(QSerialPortInfo::availablePorts());
    for (int i = 0; i < m_portInfo->count(); i++)
        m_portsListWidget->addItem(m_portInfo->value(i).portName());

    m_timer = new QTimer(this);
        m_timer->setInterval(500);
        m_timer->setTimerType(Qt::VeryCoarseTimer);
        m_timer->setSingleShot(false);
        m_timer->start();

    connect(m_SCconfigPanelCheckBox, SIGNAL(stateChanged(int)), this, SLOT(configPanelSizeUpdate(int)));
    connect(m_terminalConfigPanelCheckBox, SIGNAL(stateChanged(int)), this, SLOT(terminalConfigSizeUpdate(int)));
    connect(m_portsListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(portsList_itemClicked(QListWidgetItem*)));
    connect(m_port, SIGNAL(readyRead()), this, SLOT(receiveData()));
    connect(m_port, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(readError(QSerialPort::SerialPortError)));
    connect(m_timer, SIGNAL(timeout()), this, SLOT(serialStatusCheck()));
    connect(m_baudrateBox, SIGNAL(currentIndexChanged(int)), this, SLOT(baudrateUpdate(int)));
    connect(m_parityBox, SIGNAL(currentIndexChanged(int)), this, SLOT(parityUpdate(int)));
    connect(m_dataBitsBox, SIGNAL(currentIndexChanged(int)), this, SLOT(dataBitsUpdate(int)));
    connect(m_stopBitsBox, SIGNAL(currentIndexChanged(int)), this, SLOT(stopBitsUpdate(int)));
    connect(m_saveConfigButton, SIGNAL(clicked()), this, SLOT(saveConfigButton_itemClicked()));
    connect(m_loadConfigButton, SIGNAL(clicked()), this, SLOT(loadConfigButton_itemClicked()));
    connect(m_clearTerminalButton, SIGNAL(clicked()), this, SLOT(clearTerminalButton_itemClicked()));
    connect(m_saveTerminalButton, SIGNAL(clicked()), this, SLOT(saveTerminalButton_itemClicked()));
    connect(m_sendFileButton, SIGNAL(clicked()), this, SLOT(sendFileButton_itemClicked()));
    connect(m_sendButton, SIGNAL(clicked()), this, SLOT(sendButton_itemClicked()));
    connect(m_sendLineEdit, SIGNAL(returnPressed()), this, SLOT(sendButton_itemClicked()));
}

void SerialMonitor::configPanelSizeUpdate(int state) {
    if(state == 0) {
        m_SCconfigPanelRestrictWidget->setMaximumSize(0, 0);


    } else {
        m_SCconfigPanelRestrictWidget->setMaximumSize(5000, 200);
    }
}

void SerialMonitor::terminalConfigSizeUpdate(int state) {
    if(state == 0) {
        m_terminalConfigPanelRestrictWidget->setMaximumSize(0, 0);
    } else {
        m_terminalConfigPanelRestrictWidget->setMaximumSize(5000, 200);
    }
}

void SerialMonitor::portsList_itemClicked(QListWidgetItem* item) {
    m_timer->stop(); // timer is stopped to prevent its timeout slot to mess with this slot

    // if a connection is open, we close it
    if(m_port->isOpen()) {
        if(m_port->portName() == item->text()) {
            m_timer->start();
            return;
        }
        qDebug() << "connection with "<< m_port->portName() << " closed";
        m_terminal->insertPlainText("Connection closed with port " + m_port->portName() + "\n");
        m_terminal->moveCursor(QTextCursor::End);
        m_port->close();
    }

    // connects the serial port
    m_port->setPortName(item->text());
    m_port->open(QIODevice::ReadWrite);
    m_port->clear();

    // if something went wrong :
    if(!m_port->isOpen()) {
        qDebug() << "connection with "<< item->text() << " failed";
        m_connectionStatusLabel->setText("Not connected");
        m_terminal->insertPlainText("Connection with port " + item->text() + " failed\n");
        m_terminal->moveCursor(QTextCursor::End);
        connectionState = false;
        m_timer->start();
        return;
    }

    // once connection is established :
    qDebug() << "connection with"<< item->text() << "succeeded";
    m_connectionStatusLabel->setText("Connected to "+ m_port->portName()) ;
    m_terminal->insertPlainText("Connection established with port " + m_port->portName() + "\n");
    m_terminal->moveCursor(QTextCursor::End);
    connectionState = true;

    m_timer->start();
}

void SerialMonitor::baudrateUpdate(int index) {
    // set baudrate
    m_port->setBaudRate(m_baudrateBox->itemText(index).toInt());
    qDebug() << m_port->baudRate();
}

void SerialMonitor::parityUpdate(int index) {
    // set parity bit
    if(m_parityBox->itemText(index) == "none") m_port->setParity(QSerialPort::NoParity);
    else if(m_parityBox->itemText(index) == "odd") m_port->setParity(QSerialPort::OddParity);
    else if(m_parityBox->itemText(index) == "even") m_port->setParity(QSerialPort::EvenParity);
    else if(m_parityBox->itemText(index) == "0") m_port->setParity(QSerialPort::SpaceParity);
    else if(m_parityBox->itemText(index) == "1") m_port->setParity(QSerialPort::MarkParity);
    qDebug() << m_port->parity();
}

void SerialMonitor::dataBitsUpdate(int index) {
    // set number of data bits
    if(m_dataBitsBox->itemText(index) == "5") m_port->setDataBits(QSerialPort::Data5);
    else if(m_dataBitsBox->itemText(index) == "6") m_port->setDataBits(QSerialPort::Data6);
    else if(m_dataBitsBox->itemText(index) == "7") m_port->setDataBits(QSerialPort::Data7);
    else if(m_dataBitsBox->itemText(index) == "8") m_port->setDataBits(QSerialPort::Data8);
    qDebug() << m_port->dataBits();
}

void SerialMonitor::stopBitsUpdate(int index) {
    // set number of stop bits
    if(m_stopBitsBox->itemText(index) == "1") m_port->setStopBits(QSerialPort::OneStop);
    else if(m_stopBitsBox->itemText(index) == "1.5") m_port->setStopBits(QSerialPort::OneAndHalfStop);
    else if(m_stopBitsBox->itemText(index) == "2") m_port->setStopBits(QSerialPort::TwoStop);
    qDebug() << m_port->stopBits();
}

void SerialMonitor::receiveData() {
    // read incoming data and displays it in the terminal
    m_terminal->setFontItalic(false);
    QByteArray data = m_port->readAll();
    if(m_dataFormatBox->currentText() == "ASCII") {

        // print each byte
        for(int i = 0; i < data.count(); i++) {
            // if current byte = \n, process it as required by the user
            if(data.at(i) == '\n' && m_displayNewLine->checkState()) {
                m_terminal->insertPlainText("\\n");
            } else {
                m_terminal->insertPlainText(QString(data.at(i)));
            }
        }
    }

    if(m_dataFormatBox->currentText() == "hex") {
        QByteArray dataHex = data.toHex(); // convert QByte Array to another with data stylized as hexa values
        for(int i = 0; i < dataHex.count(); i+=2) {
            if((QString(dataHex.at(i)) == "0") && (QString(dataHex.at(i + 1)) == "a") && (!m_displayNewLine->checkState())) {
                m_terminal->insertPlainText("\n");
            } else {
                m_terminal->insertPlainText(QString(dataHex.at(i)).toUpper());
                m_terminal->insertPlainText(QString(dataHex.at(i + 1)).toUpper());
                m_terminal->insertPlainText("  ");
            }
        }
    }


    if(m_autoscrollCheckBox->checkState()) m_terminal->moveCursor(QTextCursor::End);
    m_terminal->setFontItalic(true);
}

void SerialMonitor::readError(QSerialPort::SerialPortError error) {
    QString data = QString::number(error);
    qDebug() << "error : " << data;
//    m_terminal->insertPlainText(data);
//    m_terminal->moveCursor(QTextCursor::End);
}

void SerialMonitor::serialStatusCheck() {
    // qDebug() << "timer running";
    m_portInfo->clear();
    m_portInfo->append(QSerialPortInfo::availablePorts());

    if(connectionState == true) {
		// if the port is connected, check if the connection is still active
		// by comparing the name of the ports with the available ports list
		// if the port is still available, the connection is supposedly still active
        bool stillConnected = false;
        for(int i = 0 ; i < m_portInfo->count(); i++)
            if(m_portInfo->value(i).portName() == m_port->portName())
                stillConnected = true;
        // qDebug() << stillConnected;
        if(stillConnected) return;
        m_connectionStatusLabel->setText("Not connected");
        m_terminal->insertPlainText("Connection lost\n");
        m_terminal->moveCursor(QTextCursor::End);
        m_port->close();
        connectionState = false;
    } else { 
		// if the port isn't connected, refresh the available ports list
        m_portsListWidget->clear();
        for (int i = 0; i < m_portInfo->count(); i++)
            m_portsListWidget->addItem(m_portInfo->value(i).portName());
    }

}

void SerialMonitor::saveConfigButton_itemClicked() {
    // Opens a dialog box to get a file name and path
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save configuration"), "", tr("Config file (*.smc)"));
    if(fileName.right(4) != ".smc") fileName += ".smc"; // add the extension
    if(fileName.size() <= 5) return; // prevents from creating a file named ".smc" if the user cancels the dialog

    // creates the file and write
    QFile file(fileName, this);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) return;
    QTextStream out (&file);
    out << QString::number(m_baudrateBox->currentIndex()).toUtf8() << "\n";
    out << QString::number(m_parityBox->currentIndex()).toUtf8() << "\n";
    out << QString::number(m_dataBitsBox->currentIndex()).toUtf8() << "\n";
    out << QString::number(m_stopBitsBox->currentIndex()).toUtf8() << "\n";
    out << QString::number(m_dataFormatBox->currentIndex()).toUtf8() << "\n";
    file.close();
}

void SerialMonitor::loadConfigButton_itemClicked() {
    // load a config file and get values from each lines in a QList<QString>
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load configuration"), "", tr("Config file (*.smc)"));
    QList<QString> config;
    QString line;
    QFile file(fileName);
    QTextStream in (&file);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    while(!in.atEnd()) { // parse the file, add each line to the "config" list
        line = in.readLine();
        config.append(line);
    }
    file.close();

    // load config by changing the current index of the combo boxes (it triggers the associated slot)
    m_baudrateBox->setCurrentIndex(config.value(0).toInt());
    m_parityBox->setCurrentIndex(config.value(1).toInt());
    m_dataBitsBox->setCurrentIndex(config.value(2).toInt());
    m_stopBitsBox->setCurrentIndex(config.value(3).toInt());
    m_dataFormatBox->setCurrentIndex(config.value(4).toInt());


    qDebug() << m_port->baudRate() << endl << m_port->parity() << endl << m_port->dataBits() << endl << m_port->stopBits();

}

void SerialMonitor::clearTerminalButton_itemClicked() {
    m_terminal->clear();
}

void SerialMonitor::saveTerminalButton_itemClicked() {

    // IMPORTANT : check if saveTerminalFile exists (check if the name string is empty?)
    if (saveTerminalFileExists) {
        saveTerminalFile->close();
        delete saveTerminalFile;
        delete saveTerminalFileName;
    }
    // Opens a dialog box to get a file name and path
    saveTerminalFileName = new QString();
    *saveTerminalFileName = QFileDialog::getSaveFileName(this, tr("Save terminal"), "", tr("Text file (*.txt)"));
    if(saveTerminalFileName->right(4) != ".txt") *saveTerminalFileName += ".txt"; // add the extension

    // creates the file and write
    saveTerminalFile = new QFile(*saveTerminalFileName, this);
    if(!saveTerminalFile->open(QIODevice::WriteOnly)) return;
    QTextStream out (saveTerminalFile);
    out << m_terminal->toPlainText();
    saveTerminalFile->close();

    saveTerminalFileExists = true;

    // re-open the file in case of auto save. It will be closed in the destructor
//    saveTerminalFile->open(QIODevice::WriteOnly | QIODevice::Append);
}

void SerialMonitor::sendButton_itemClicked() {

    if (m_sendLineEdit->text().isEmpty() | !m_port->isOpen()) return;

    QByteArray data = m_sendLineEdit->text().toUtf8();
    if(m_sendNLCharCheckBox->isChecked()) data.append('\n');
    qDebug() << data;

    m_port->write(data);
    if(m_clearAfterSendCheckBox->isChecked()) m_sendLineEdit->clear();
}


void SerialMonitor::sendFileButton_itemClicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load a file to transmit"), "", tr("Text file (*.txt)"));
    QFile file(fileName);
    QDataStream in (&file);
    if(!file.open(QIODevice::ReadOnly)) return;

    QByteArray data = file.readAll();
    file.close();
    qDebug() << data;
    m_port->write(data);
}

SerialMonitor::~SerialMonitor() {
    if(m_port->isOpen()) m_port->close();
}
