#include "home.h"
#include "ui_home.h"

Home::Home(QWidget *parent , const QString & username)
    : QDialog(parent) , ui(new Ui::Home) , m_username(username)
{
    ui->setupUi(this) ;

    QPixmap cursorPixmap(":/Images/curser icon.png");
    QCursor customCursor(cursorPixmap);
    setCursor(customCursor);

    m_db = QSqlDatabase::addDatabase("QSQLITE") ;
    m_db.setDatabaseName("bankDB.sqlite") ;
    m_db.open() ;
    if(m_db.isOpen()) loadBankAccounts() ;

}

void Home::loadBankAccounts() {
    QSqlQuery query ;

    std::vector<QString> columnNames ;
    query.exec("PRAGMA table_info(BankAccounts)") ;
    while (query.next()) columnNames.push_back(query.value(1).toString()) ;

    QString w = "wwevr" ;
    query.prepare("SELECT CardNumber FROM BankAccounts WHERE OwnerUsername = :username ") ;
    query.bindValue(":username" , w) ;
    query.exec() ;
    while(query.next()) {

        BankAccount bnkAccnt ;
        std::vector<QString> values ;
        QString crdNum = query.value(0).toString() ;

        for(auto i = columnNames.begin() ; i != columnNames.end() ; i++) {
            query.prepare("SELECT " + (*i) + " FROM BankAccounts WHERE CardNumber = :cardnumber ") ;
            query.bindValue(":cardnumber" , crdNum) ;
            query.exec() ;
            if(query.next())
                values.push_back(query.value(0).toString()) ;
        }

        bnkAccnt.setKind(values[0]) ; bnkAccnt.setCardNumber(values[1]) ; bnkAccnt.setShebaNumber(values[2]) ;
        bnkAccnt.setBankAccountNumber(values[3]) ; bnkAccnt.setCVV2(values[4].toInt()) ; bnkAccnt.setInventory(values[5].toLongLong()) ;
        bnkAccnt.set4digitCode(values[6].toInt()) ; bnkAccnt.setSecondFixedPassword(values[7]) ; bnkAccnt.setSecondDynamicPassword(values[8].toInt()) ;
        bnkAccnt.setOwnerUsername(values[9]) ; bnkAccnt.setExpirationDate(values[10].toInt()) ;

        m_bankAccounts.pushBack(bnkAccnt) ;

    }
}
const MList<BankAccount> & Home::getBankAccounts() const { return m_bankAccounts ; }

Home::~Home()
{
    delete ui ;
    m_db.close();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}
