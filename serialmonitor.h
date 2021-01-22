#ifndef SERIALMONITOR_H
#define SERIALMONITOR_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include <QTime>
#include <QSerialPort>

class SerialMonitor : public QWidget
{
    Q_OBJECT
    public:
        SerialMonitor();
        ~SerialMonitor();

    private slots:
        void configPanelSizeUpdate(int state);
        void terminalConfigSizeUpdate(int state);
        void portsList_itemClicked(QListWidgetItem* item);
        void baudrateUpdate(int index);
        void parityUpdate(int index);
        void dataBitsUpdate(int index);
        void stopBitsUpdate(int index);
        void receiveData();
        void readError(QSerialPort::SerialPortError error);
        void serialStatusCheck();
        void saveConfigButton_itemClicked();
        void loadConfigButton_itemClicked();
        void clearTerminalButton_itemClicked();
        void saveTerminalButton_itemClicked();
        void sendButton_itemClicked();
        void sendFileButton_itemClicked();

    private:
        QVBoxLayout* m_mainLayout;
            QHBoxLayout* m_panelCheckBoxesLayout;
                QCheckBox* m_SCconfigPanelCheckBox;
                QCheckBox* m_terminalConfigPanelCheckBox;
            QWidget* m_SCconfigPanelRestrictWidget;
                QHBoxLayout* m_SCconfigPanelLayout;
                    QVBoxLayout* m_config1Layout;
                        QLabel* m_portsListWidgetTitle;
                        QListWidget* m_portsListWidget;
                        QPushButton* m_portRefreshButton;
                        QLabel* m_connectionStatusLabel;
                    QGridLayout* m_config2Layout;
                        QLabel* m_baudrateLabel;
                        QLabel* m_parityLabel;
                        QLabel* m_dataBitsLabel;
                        QLabel* m_stopBitsLabel;
                        QLabel* m_dataFormatLabel;
                        QComboBox* m_baudrateBox;
                        QComboBox* m_parityBox;
                        QComboBox* m_dataBitsBox;
                        QComboBox* m_stopBitsBox;
                        QComboBox* m_dataFormatBox;
                        QSpacerItem* m_spacer1;
                        QSpacerItem* m_spacer2;
                        QSpacerItem* m_spacer3;
                    QGridLayout* m_config3Layout;
                        QPushButton* m_saveConfigButton;
                        QPushButton* m_loadConfigButton;
                    QGridLayout* m_config4Layout;
                        QLabel* m_fillerLabel;
            QWidget* m_terminalConfigPanelRestrictWidget;
                QVBoxLayout* m_terminalConfigPanelLayout;
                    QHBoxLayout* m_terminalConfig1Layout;
                        QPushButton* m_clearTerminalButton;
                        QCheckBox* m_autoscrollCheckBox;
                        QCheckBox* m_displayNewLine;
                        QCheckBox* m_addTimestamp;
                    QHBoxLayout* m_terminalConfig2Layout;
                        QPushButton* m_saveTerminalButton;
                        QPushButton* m_sendFileButton;
                        QCheckBox* m_sendNLCharCheckBox;
                        QCheckBox* m_clearAfterSendCheckBox;
            QTextEdit* m_terminal;
            QHBoxLayout* m_sendLayout;
                QLineEdit* m_sendLineEdit;
                QPushButton* m_sendButton;

        QSerialPort* m_port;
        QTimer* m_timer;
        QList<QSerialPortInfo>* m_portInfo;
        bool connectionState;
        QFile* saveTerminalFile;
        QString* saveTerminalFileName;
        bool saveTerminalFileExists;
};

#endif // SERIALMONITOR_H
