#include "home.h"
#include "ui_home.h"

Home::Home(QWidget *parent , const QString & username)
    : QDialog(parent) , ui(new Ui::Home) , m_username(username) , animation(new QPropertyAnimation())
    , opacityEffect(new QGraphicsOpacityEffect(this))
{
    m_currentCardIndex = 0 ;

    QPixmap cursorPixmap(":/Images/curser icon.png");
    QCursor customCursor(cursorPixmap);
    setCursor(customCursor);

    m_db = QSqlDatabase::addDatabase("QSQLITE") ;
    m_db.setDatabaseName("bankDB.sqlite") ;
    m_db.open() ;
    if(m_db.isOpen())
        loadBankAccounts() ;

    ui->setupUi(this) ;

    setCardInfo() ;

    animation->setTargetObject(opacityEffect);
    animation->setPropertyName("opacity");
    animation->setDuration(1000);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);



}

void Home::loadBankAccounts() {
    QSqlQuery query ;

    std::vector<QString> columnNames ;
    query.exec("PRAGMA table_info(BankAccounts)") ;
    while (query.next()) columnNames.push_back(query.value(1).toString()) ;

    QString w = "swewerewdewjkhjwe" ;
    query.prepare("SELECT CardNumber FROM BankAccounts WHERE OwnerUsername = :username") ;
    query.bindValue(":username" , w) ;
    if(query.exec()) {
        while(query.next()) {

            BankAccount bnkAccnt ;
            std::vector<QString> values ;
            QString crdNum = query.value(0).toString() ;

            for(auto i = columnNames.begin() ; i != columnNames.end() ; i++) {
                QSqlQuery sqrv ;
                sqrv.prepare("SELECT " + (*i) + " FROM BankAccounts WHERE CardNumber = :cardnumber ") ;
                sqrv.bindValue(":cardnumber" , crdNum) ;
                sqrv.exec() ;
                if(sqrv.next()) values.push_back(sqrv.value(0).toString()) ;
            }

            bnkAccnt.setKind(values[0]) ; bnkAccnt.setCardNumber(values[1]) ; bnkAccnt.setShebaNumber(values[2]) ;
            bnkAccnt.setBankAccountNumber(values[3]) ; bnkAccnt.setCVV2(values[4].toInt()) ; bnkAccnt.setInventory(values[5].toLongLong()) ;
            bnkAccnt.set4digitCode(values[6].toInt()) ; bnkAccnt.setSecondFixedPassword(values[7]) ; bnkAccnt.setSecondDynamicPassword(values[8].toInt()) ;
            bnkAccnt.setOwnerUsername(values[9]) ; bnkAccnt.setExpirationDate(values[10].toInt()) ;

            m_bankAccounts.pushBack(bnkAccnt) ;
        }
    }

    if(m_bankAccounts.getSize()) m_currentCardIndex = 1 ;
}
const MList<BankAccount> & Home::getBankAccounts() const { return m_bankAccounts ; }

void Home::setCardInfo() {
    QString baseStyleSheet = "#btnCurrentCard {"
                             "border: none;"
                             "background: transparent;"
                             "text-align: left;"
                             "color: black;"
                             "font-family:Arial;"
                             "font-size:13px;"
                             "font-weight:bold;"
                             "padding-top: 30px;"
                             "padding-left: 30px;";
    if(m_bankAccounts.getSize()){
        QString cardKind = m_bankAccounts[m_currentCardIndex - 1]->getData().getKind() ;
        if(cardKind == QString("Current")) {
            baseStyleSheet += "background-image: url(:/Images/current card.png);"
                              "background-repeat: no-repeat;"
                              "background-position: center;"
                              "}"
                              "#btnCurrentCard:hover{"
                              "background-image: url(:/Images/current card hover.png);"
                              "}" ;
        }
        else if(cardKind == QString("Saving")) {
            baseStyleSheet += "background-image: url(:/Images/saving account.png);"
                              "background-repeat: no-repeat;"
                              "background-position: center;"
                              "}"
                              "#btnCurrentCard:hover{"
                              "background-image: url(:/Images/saving account hover.png);"
                              "}";

        }
        else if(cardKind == QString("Loan")){
            baseStyleSheet += "background-image: url(:/Images/loan account.png);"
                              "background-repeat: no-repeat;"
                              "background-position: center;"
                              "}"
                              "#btnCurrentCard:hover{"
                              "background-image: url(:/Images/loan account hover.png);"
                              "}" ;
        }
        QString bankAccountNumber = m_bankAccounts[m_currentCardIndex - 1]->getData().getBankAccountNumber() ,
            inventory = m_bankAccounts[m_currentCardIndex - 1]->getData().centToDollar() ,
            cardNumber = m_bankAccounts[m_currentCardIndex - 1]->getData().insertSpaceToCardNum() ,
            shebaNumber = m_bankAccounts[m_currentCardIndex - 1]->getData().getShebaNumber() ,
            cvv2 = QString::number(m_bankAccounts[m_currentCardIndex - 1]->getData().getCVV2()) ,
            date = m_bankAccounts[m_currentCardIndex - 1]->getData().insertSlashToExpirationDate() ;
        ui->btnCurrentCard->setText("\n IR"+ shebaNumber +"\n account number : "+ bankAccountNumber +"\n\n "+ cardNumber +"\n\n cvv2 : "+ cvv2 +"\n expiration date : "+ date +"\n\n inventory : "+ inventory +"$") ;
    }
    else {
        baseStyleSheet += "background-image: url(:/Images/no account.png);"
                          "background-repeat: no-repeat;"
                          "background-position: center;"
                          "}"
                          "#btnCurrentCard:hover{"
                          "background-image: url(:/Images/no account hover.png);"
                          "}";
    }
    ui->btnCurrentCard->setStyleSheet(baseStyleSheet) ;
}

Home::~Home()
{
    delete ui ;
    delete animation ;
    delete opacityEffect ;
    m_db.close();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}

void Home::on_btnRightPtr_clicked()
{
    int numOfCards = m_bankAccounts.getSize() ;
    if(m_currentCardIndex < numOfCards) m_currentCardIndex ++ ;
    else if(m_currentCardIndex == numOfCards && numOfCards != 0) m_currentCardIndex = 1 ;
    setCardInfo() ;
    ui->btnCurrentCard->setGraphicsEffect(opacityEffect);
    animation->start() ;
}


void Home::on_btnLeftPtr_clicked()
{
    int numOfCards = m_bankAccounts.getSize() ;
    if(numOfCards != 0 && m_currentCardIndex != 1) m_currentCardIndex -- ;
    else if(numOfCards != 0 && m_currentCardIndex == 1) m_currentCardIndex = numOfCards ;
    setCardInfo() ;
    ui->btnCurrentCard->setGraphicsEffect(opacityEffect);
    animation->start() ;
}

