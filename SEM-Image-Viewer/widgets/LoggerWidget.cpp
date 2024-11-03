#include "LoggerWidget.h"

LoggerWidget::LoggerWidget(QWidget *parent)
    : QWidget(parent)
{
    QString buttonsStyle = "QPushButton {"
                           "border: none;"
                           "font-family: 'Roboto';"
                           "padding:5px;"
                           "padding-right: 20px;"
                           "font:  14px;"
                           "text-align: center;"

                           "}"
                           "QPushButton:hover {"
                           "background-color: #d3d3d3;" // Change background color on hover
                           "}";
    QWidget *line = new QWidget(this);
    line->setStyleSheet("background-color: #aaaaaa;"); // Set the color of the line
    line->setFixedHeight(2);                           // Set the height of the line
    line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    // Buttons for filtering logs by type
    allShowButton = new QPushButton("All", this);

    allShowButton->setStyleSheet(
        buttonsStyle);

    infoShowButton = new QPushButton("Info", this);
    infoShowButton->setIcon(QIcon(":/assets/information_icon.png"));
    infoShowButton->setIconSize(QSize(16, 16));
    infoShowButton->setStyleSheet(buttonsStyle);

    errorsShowButton = new QPushButton("Errors", this);
    errorsShowButton->setIcon(QIcon(":/assets/errors_icon.png"));
    errorsShowButton->setIconSize(QSize(16, 16));
    errorsShowButton->setStyleSheet(buttonsStyle);

    warningsShowButton = new QPushButton("Warnings", this);
    warningsShowButton->setIcon(QIcon(":/assets/warnings_icon.png"));
    warningsShowButton->setIconSize(QSize(16, 16));
    warningsShowButton->setStyleSheet(buttonsStyle);

    switchLayoutButtonFull = new QPushButton("   ▼", this);
    switchLayoutButtonFull->setStyleSheet(buttonsStyle);

    switchLayoutButtonCompact = new QPushButton("   ▲", this);
    switchLayoutButtonCompact->setStyleSheet(buttonsStyle);
    switchLayoutButtonCompact->setFixedWidth(50);
    // Search line edit for filtering logs by text
    searchLineEdit = new QLineEdit(this);
    searchLineEdit->setPlaceholderText("Search log message");
    // Set a fixed width (e.g., 200 pixels)
    searchLineEdit->setFixedWidth(300);

    // Set the style sheet for rounded borders and other properties
    searchLineEdit->setStyleSheet(
        "QLineEdit {"
        "border: 2px solid #aaaaaa;" // Set border color and width
        "border-radius: 10px;"       // Set border radius for rounded corners
        "padding: 5px;"              // Add some padding
        "}"
        "QLineEdit:focus {"          // Change style when focused
        "border: 2px solid #0078d7;" // Change border color on focus
        "}");

    // Log list widget for displaying messages
    logListWidget = new QListWidget(this);
    logListWidget->setStyleSheet(
        "QListWidget {"
        "border: none;"            // Remove border
        "background: transparent;" // Remove background
        "}");
    // Layout setup
    // Create the top horizontal layout for compact layout
    QHBoxLayout *topLayoutCompact = new QHBoxLayout;

    topLayoutCompact->addWidget(new QLabel("Error : 1 Warnings : 2 Info : 3", this));
    topLayoutCompact->addWidget(switchLayoutButtonCompact);

    QHBoxLayout *topLayoutFull = new QHBoxLayout;
    topLayoutFull->addWidget(allShowButton);
    topLayoutFull->addWidget(infoShowButton);
    topLayoutFull->addWidget(warningsShowButton);
    topLayoutFull->addWidget(errorsShowButton);
    topLayoutFull->addSpacing(50);
    topLayoutFull->addWidget(searchLineEdit);
    topLayoutFull->addWidget(switchLayoutButtonFull);

    // Why i canot use the same topLayout

    // Create the compact vertical layout without logListWidget
    compactLayout = new QVBoxLayout();

    compactLayout->addLayout(topLayoutCompact);
    // Create the full vertical layout
    fullLayout = new QVBoxLayout();
    fullLayout->addLayout(topLayoutFull);
    fullLayout->addWidget(line);
    fullLayout->addWidget(logListWidget);

    // Set the initial layout
    stackedWidget = new QStackedWidget(this);

    QWidget *fullViewWidget = new QWidget();
    fullViewWidget->setLayout(fullLayout);

    QWidget *compactViewWidget = new QWidget();
    compactViewWidget->setLayout(compactLayout);

    stackedWidget->addWidget(fullViewWidget);
    stackedWidget->addWidget(compactViewWidget);

    // Set stackedWidget as the main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stackedWidget);
    setLayout(mainLayout);

    connect(allShowButton, &QPushButton::clicked, this, &LoggerWidget::filterLogs);
    connect(infoShowButton, &QPushButton::clicked, this, &LoggerWidget::filterLogs);
    connect(errorsShowButton, &QPushButton::clicked, this, &LoggerWidget::filterLogs);
    connect(warningsShowButton, &QPushButton::clicked, this, &LoggerWidget::filterLogs);
    connect(searchLineEdit, &QLineEdit::textChanged, this, &LoggerWidget::filterLogs);
    connect(switchLayoutButtonFull, &QPushButton::clicked, this, &LoggerWidget::switchLayout);
    connect(switchLayoutButtonCompact, &QPushButton::clicked, this, &LoggerWidget::switchLayout);
    // Set initial state
    isExpanded = true;
    stackedWidget->setCurrentIndex(0);
}

void LoggerWidget::addLogMessage(const QString &type, const QString &message)
{
    // Need to Change
    QString logText = QString("[%1] %2").arg(type, message);
    QListWidgetItem *item = new QListWidgetItem(logText);

    if (type == "Info")
    {
        item->setIcon(QIcon(":/icons/info.png")); // Placeholder icon
    }
    else if (type == "Warning")
    {
        item->setIcon(QIcon(":/icons/warning.png")); // Placeholder icon
    }
    else if (type == "Error")
    {
        item->setIcon(QIcon(":/icons/error.png")); // Placeholder icon
    }

    logListWidget->addItem(item);
    filterLogs();
}

void LoggerWidget::filterLogs()
{
    QString filterText = searchLineEdit->text().toLower();
    QString selectedType;
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());

    if (clickedButton == infoShowButton)
    {
        selectedType = "Info";
    }
    else if (clickedButton == warningsShowButton)
    {
        selectedType = "Warning";
    }
    else if (clickedButton == errorsShowButton)
    {
        selectedType = "Error";
    }
    else
    {
        selectedType = "All";
    }

    for (int i = 0; i < logListWidget->count(); ++i)
    {
        QListWidgetItem *item = logListWidget->item(i);
        bool matchesType = (selectedType == "All" || item->text().startsWith("[" + selectedType + "]"));
        bool matchesText = item->text().toLower().contains(filterText);
        item->setHidden(!(matchesType && matchesText));
    }
}
void LoggerWidget::switchLayout()
{
    if (isExpanded)
    {
        stackedWidget->setCurrentIndex(1); // Show compact view
                                           // Change to up arrow icon
    }
    else
    {
        stackedWidget->setCurrentIndex(0); // Show full view
    }

    isExpanded = !isExpanded; // Toggle state
}
